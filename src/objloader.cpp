#include "objloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include "tiny_obj_loader.cpp"

using namespace std;

vector<shared_ptr<Drawable>> loadObjFile(const char* path)
{
    fstream objFile;
    objFile.open(path, ios::in);

    /// Structure containing all loaded objects.
    vector<shared_ptr<Drawable>> objects;

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

    /// Normal vectors.
    vector<array<double,3>> normals;

    /// Obj files do not reset vertex index when new object is being described, so this
    /// value will be subtracted.
    int vertexIndexDiff = 0;

    std::map<std::string, tinyobj::material_t> material_map;
    fstream mtlFile;

    tinyobj::material_t material;
    bool isMaterialSet = false;

    while (getline(objFile, line))
    {
        switch(line[0])
        {
            case '#':
            // komentarz zaczynający się na '#'
                continue;
                break;
            case 'm': {
            // "mtllib path"
                    string mtlFileName = line.substr(7);
                    mtlFile.open("objFiles/" + mtlFileName, ios::in);
                    string err = tinyobj::LoadMtl(material_map, mtlFile);
                    if (err != "")
                        cerr << "Error with loading mtl file" + err << endl;
                    mtlFile.close();
                }
                break;
            case 'o':
            // "o [nazwa_obiektu]", po tej linijce opisywane są wierzchołki
                // Do nothing on first occurence of 'o'.
                if (!verts.empty())
                {
                    shared_ptr<LoadedObject> obj = make_shared<LoadedObject>(verts, faces, normals, material);
                    objects.push_back(obj);
                    vertexIndexDiff += verts.size();
                    verts.clear();
                    faces.clear();
                    normals.clear();
                }
                break;
            case 'v':
                if (line[1] == ' ')
                {
                    // wierzchołki
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
                else
                {
                    // normal vectors
                    // "vn "
                    normals.push_back(extractNormal(line));
                }
                break;
            case 'u': {
            // "usemtl [material]"
                string namebuf = line.substr(7);
                if (material_map.find(namebuf) != material_map.end()) {
                    material = material_map[namebuf];
                    isMaterialSet = true;
                } else {
                    cerr << "Error: material " + namebuf + "not found" << endl;
                    tinyobj::InitMaterial(material);
                }}
                break;
            case 's':
            // "s [off]"
                break;
            case 'f':
            // faces - cztery int z numerem wierzchołka.
            // "f 5 6 2 1"
                array<string,5> f;
                stringstream sstr(line);
                sstr >> f[0] >> f[1] >> f[2] >> f[3] >> f[4];
                array<int, 4> face;
                for (int i=0; i<4; ++i)
                    face[i] = stoi(stripFaceIndex(f[i+1])) - vertexIndexDiff - 1;
                faces.push_back(face);
        }
        //cout << line << endl;
    }
    // Adding one final object.
    if (!verts.empty())
    {
        objects.push_back(make_shared<LoadedObject>(verts, faces, normals, material));
    }
    //cout << "Ilość wczytanych obiektów: " << objects.size() << endl;
    objFile.close();
    return objects;
}

string stripFaceIndex(string input)
{
    int slashPos = input.find('/');
    return input.substr(0, slashPos);
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
