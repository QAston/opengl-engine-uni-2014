#include "objloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

void loadObjFile(const char* path)
{
    fstream file;
    file.open(path, ios::in);
    if (!file.is_open())
    {
        cerr << "Error: failed to open obj file: " << path << endl;
        return;
    }
    string line;

    vector<array<double,3>> verts;
    vector<vector<array<double,3>>> objects;
    while (getline(file, line))
    {
        switch(line[0])
        {
            case '#':
            // komentarz zaczynający się na '#'
                continue;
                break;
            case 'o':
            // "o [nazwa_obiektu]", po tej linijce opisywane są wierzczhołki
                break;
            case 'v': {
            // wierzchołki
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
                objects.push_back(verts);
                break;
            case 's':
            // "s [off]"
                break;
        }
        cout << line << endl;
    }
    cout << "Ilość wczytanych obiektów: " << objects.size() << endl;
    file.close();
}
