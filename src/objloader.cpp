#include "objloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

vector<LoadedObject> loadObjFile(const char* path)
{
    fstream file;
    file.open(path, ios::in);

    /// Structure containing all loaded objects.
    vector<LoadedObject> objects;

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

    while (getline(file, line))
    {
        switch(line[0])
        {
            case '#':
            // komentarz zaczynający się na '#'
                continue;
                break;
            case 'o':
            // "o [nazwa_obiektu]", po tej linijce opisywane są wierzchołki
                // Do nothing on first occurence of 'o'.
                if (!verts.empty())
                {
                    objects.push_back(LoadedObject(verts, faces));
                    verts.clear();
                    faces.clear();
                }
                break;
            case 'v': {
            // wierzchołki
            // "v 1.000000 -1.000000 -1.000000"
                string v, v1, v2, v3;
                stringstream sstr(line);
                sstr >> v >> v1 >> v2 >> v3;
                array<double, 3> coords;
                coords[0] = stod(v1);
                coords[1] = stod(v2);
                coords[2] = stod(v3);
                verts.push_back(coords);
                }
                break;
            case 'u':
            // "usemtl [material]"
                // "usemtl" zawsze następuje po "v ..."
                //objects.push_back(LoadedObject);
                break;
            case 's':
            // "s [off]"
                break;
            case 'f':
            // faces - cztery int z numerem wierzchołka.
            // "f 5 6 2 1"
                string f, f1, f2, f3, f4;
                stringstream sstr(line);
                sstr >> f >> f1 >> f2 >> f3 >> f4;
                array<int, 4> face;
                face[0] = stoi(f1);
                face[1] = stoi(f2);
                face[2] = stoi(f3);
                face[3] = stoi(f4);
                faces.push_back(face);
        }
        cout << line << endl;
    }
    cout << "Ilość wczytanych obiektów: " << objects.size() << endl;
    file.close();
    return objects;
}
