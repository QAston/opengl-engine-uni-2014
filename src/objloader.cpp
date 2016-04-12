#include "objloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include "tiny_obj_loader.h"
#include "rwconfig.h"

using namespace std;

vector<shared_ptr<LoadedObject>> loadObjFile(const char* path)
{
    fstream objFile;
    objFile.open(path, ios::in);

    /// Structure containing all loaded objects.
    vector<shared_ptr<LoadedObject>> objects;

    if (!objFile.is_open())
    {
        cerr << "Error: failed to open obj file: " << path << endl;
        return objects;
    }
    string line;

    /// Vertices of a single object.
    vector<array<double,3>> verts;

    /// Faces of a single object.
    vector<array<int, 4>> faces;

    /// All normals in a file.
    vector<array<double,3>> normals;
    /// Normals to be put into an object.
    vector<array<double,3>> objnormals;

    /// All texture coordinates.
    vector<array<double,2>> texCoords;
    /// Texture coordinates to be put into an object.
    vector<array<double,2>> objtexCoords;

    /// Obj files do not reset vertex index when new object is being described, so this
    /// value will be subtracted.
    int vertexIndexDiff = 0;

    bool isSmooth = true;

    std::map<std::string, tinyobj::material_t> material_map;
    fstream mtlFile;

    tinyobj::material_t material;

    while (getline(objFile, line))
    {
        switch(line[0])
        {
        case '#':
            // komentarz zaczynaj¹cy siê na '#'
            continue;
        case 'm':
        {
            // "mtllib path"
            string mtlFileName = line.substr(7);
            mtlFile.open(resourcePath("objFiles/" + mtlFileName), ios::in);
            string err = tinyobj::LoadMtl(material_map, mtlFile);
            if (err != "")
                cerr << "Error with loading mtl file" + err << endl;
            mtlFile.close();
        }
        break;
        case 'o':
            // "o [nazwa_obiektu]", po tej linijce opisywane s¹ wierzcho³ki
            // Do nothing on first occurence of 'o'.
            if (!verts.empty())
            {
                shared_ptr<LoadedObject> obj = make_shared<LoadedObject>(verts, faces, objnormals,
                                               material, objtexCoords, isSmooth);
                objects.push_back(obj);
                vertexIndexDiff += verts.size();
                verts.clear();
                faces.clear();
                objnormals.clear();
                objtexCoords.clear();
            }
            break;
        case 'v':
            if (line[1] == ' ')
            {
                // wierzcho³ki
                // "v 1.000000 -1.000000 -1.000000"
                string v, v1, v2, v3;
                stringstream sstr(line);
                sstr >> v >> v1 >> v2 >> v3;
                array<double,3> coords;
                coords[0] = stod(v1);
                coords[1] = stod(v2);
                coords[2] = stod(v3);
                verts.push_back(coords);
            }
            else if (line[1] == 'n')
            {
                // normal vectors
                // "vn "
                normals.push_back(extractNormal(line));
            }
            else
            {
                // texture coordinates
                texCoords.push_back(extractTextureCoords(line));
            }
            break;
        case 'u':
        {
            // "usemtl [material]"
            string namebuf = line.substr(7);
            if (material_map.find(namebuf) != material_map.end())
            {
                material = material_map[namebuf];
            }
            else
            {
                cerr << "Error: material " + namebuf + " not found" << endl;
                tinyobj::InitMaterial(material);
            }
        }
        break;
        case 's':
            // smooth shade model
            // "s [off]"
            if (line == "s off")
                isSmooth = false;
            break;
        case 'f':
        {

            // faces: Gdy nie ma vt i vn
            // cztery int z numerem wierzcho³ka.
            // "f 5 6 2 1"
            // W przeciwnym wypadku "f vertexIndex/texcoordindex/normalindex ..."
            array<string,5> f;
            stringstream sstr(line);
            sstr >> f[0] >> f[1] >> f[2] >> f[3] >> f[4];
            array<int, 4> face;
            int normalIndex = -1;
            for (int i=0; i<4; ++i)
            {
                if (f[i+1] != "")
                {
                    array<int,3> vals = stripFaceIndex(f[i+1]);
                    face[i] = vals[0] - vertexIndexDiff - 1;
                    if (vals[1] > 0)
                        objtexCoords.push_back(texCoords[vals[1]-1]);
                    normalIndex = vals[2];
                }
                else
                    face[i] = face[i-1];
            }
            faces.push_back(face);
            if (normalIndex > 0)
                objnormals.push_back(normals[normalIndex-1]);
        }
        break;
        default:
            assert(false && "INVALID CASE VALUE");
            break;
        }
        cout << line << endl;
    }
    // Adding one final object.
    if (!verts.empty())
    {
        objects.push_back(make_shared<LoadedObject>(verts, faces, objnormals, material, objtexCoords, isSmooth));
    }
    //cout << "Iloœæ wczytanych obiektów: " << objects.size() << endl;
    objFile.close();
    return objects;
}

array<int,3> stripFaceIndex(string input)
{
    int slashPos = input.find('/');
    array<int,3> values{{-1, -1, -1}};
    /// vertexIndex
    values[0] = stoi(input.substr(0, slashPos));
    // no more values found
    if (slashPos == -1)
        return values;

    input = input.substr(slashPos+1);
    int nextslashPos = input.find('/');
    /// textureCoordIndex
    if (input.substr(0, nextslashPos) != "")
        values[1] = stoi(input.substr(0, nextslashPos));

    // no more values found
    if (nextslashPos == -1)
        return values;
    /// normalIndex
    if (input.substr(nextslashPos+1) != "")
        values[2] = stoi(input.substr(nextslashPos+1));
    return values;
}

array<double,3> extractNormal(string input)
{
    string v, v1, v2, v3;
    stringstream sstr(input);
    sstr >> v >> v1 >> v2 >> v3;
    array<double,3> normal;
    normal[0] = stod(v1);
    normal[1] = stod(v2);
    normal[2] = stod(v3);
    return normal;
}

array<double,2> extractTextureCoords(string input)
{
    stringstream sstr(input);
    array<double,2> extracted;
    string v;
    sstr >> v;
    for (int i=0; i<2; ++i)
    {
        sstr >> v;
        extracted[i] = stod(v);
    }
    return extracted;
}

GLubyte* loadPngImage(const char *name, int &outWidth, int &outHeight)
{
    GLubyte *outData = NULL;
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL)
        return NULL;

    /* Create and initialize the png_struct with the desired error handler
     * functions.  If you want to use the default stderr and longjump method,
     * you can supply NULL for the last three parameters.  We also supply the
     * the compiler header file version, so that we know if the application
     * was compiled with a compatible version of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL)
    {
        fclose(fp);
        return NULL;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return NULL;
    }

    /* Set error handling if you are using the setjmp/longjmp method
     * (this is the normal method of doing things with libpng).
     * REQUIRED unless you  set up your own error handlers in
     * the png_create_read_struct() earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return NULL;
    }

    /* Set up the output control if you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read in the entire image at once, and
     * you need to specify only transforms that can be controlled
     * with one of the PNG_TRANSFORM_* bits (this presently excludes
     * dithering, filling, setting background, and doing gamma
     * adjustment), then you can read the entire image (including pixels)
     * into the info structure with this call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    outWidth = width;
    outHeight = height;

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    //outData = (GLubyte*) malloc(row_bytes * outHeight);
    outData = new GLubyte[row_bytes * outHeight];

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++)
    {
        /* note that png is ordered top to bottom, but OpenGL expect it bottom to top
        so the order or swapped */
        memcpy(outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read, and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    /* Close the file */
    fclose(fp);

    /* That's it */
    return outData;
}


GLubyte* initTexture(const char* filename)
{
    // The following two lines enable semi transparent
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    GLubyte *textureImage;
    textureImage = loadPngImage(filename, width, height);
    if (textureImage == NULL)
    {
        cerr << "Unable to load png file :" << filename << endl;
        return NULL;
    }
    cout << "Image loaded. Width: " << width << " Height: " << height << endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width,
                 height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 textureImage);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    return textureImage;
}
