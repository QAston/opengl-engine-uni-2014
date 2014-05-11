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
    fstream file;
    file.open(path, ios::in);

    /// Structure containing all loaded objects.
    vector<shared_ptr<Drawable>> objects;

    if (!file.is_open())
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

    tinyobj::MaterialFileReader r("objFiles/graniastoslupy-normal.mtl");
    std::map<std::string, tinyobj::material_t> material_map;
    tinyobj::material_t material;
    bool is_material_seted = false;

    while (getline(file, line))
    {
        switch(line[0])
        {
            case '#':
            // komentarz zaczynający się na '#'
                continue;
                break;
            case 'm':
            // "mtllib path"
            case 'o':
            // "o [nazwa_obiektu]", po tej linijce opisywane są wierzchołki
                // Do nothing on first occurence of 'o'.
                if (!verts.empty())
                {
                    shared_ptr<LoadedObject> obj = make_shared<LoadedObject>(verts, faces, normals);
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
                    is_material_seted = true;
                } else {
                    // { error!! material not found }
                    //InitMaterial(material);
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
        objects.push_back(make_shared<LoadedObject>(verts, faces, normals));
    }
    //cout << "Ilość wczytanych obiektów: " << objects.size() << endl;
    file.close();
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
