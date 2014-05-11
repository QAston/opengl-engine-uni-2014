#ifndef LOADEDOBJECT_H
#define LOADEDOBJECT_H

#include "drawable.h"
#include <GL/glut.h>
#include <vector>
#include <array>
#include "tiny_obj_loader.h"

using namespace std;

/**
 * Class used for drawing objects loaded from .obj file.
 */
class LoadedObject : public Drawable
{
    public:
        LoadedObject(
            const vector<array<double,3>> &vertizzi,
            const vector<array<int,4>> &facess,
            const vector<array<double,3>> &normals
        );
        LoadedObject(float x, float y, float z, float rX, float rY);
        virtual ~LoadedObject();
        void draw();
    protected:
    private:
        vector<GLdouble> vertici;
        vector<array<GLubyte,4>> faces;
        vector<array<GLdouble,3>> normals;
        vector<GLfloat> colors;
        tinyobj::material_t material;
};

#endif // LOADEDOBJECT_H
