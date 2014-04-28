#ifndef LOADEDOBJECT_H
#define LOADEDOBJECT_H

#include "drawable.h"
#include <GL/glut.h>
#include <vector>
#include <array>

using namespace std;

/**
 * Class used for drawing objects loaded from .obj file.
 */
class LoadedObject : public Drawable
{
    public:
        LoadedObject(vector<array<double,3>> vertizzi);
        LoadedObject(float x, float y, float z, float rX, float rY);
        virtual ~LoadedObject();
        void draw();
    protected:
    private:
        vector<GLdouble> vertici;
};

#endif // LOADEDOBJECT_H
