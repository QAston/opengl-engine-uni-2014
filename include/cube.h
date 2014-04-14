#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>
#include "drawable.h"


class Cube : public Drawable
{
    public:
        Cube(float x, float y, float z, float rX, float rY);
        virtual ~Cube();
        void draw();
    protected:
    private:
        float _posX;
        float _posY;
        float _posZ;
        float rotateX;
        float rotateY;

        GLint cubeVerticles[24] = {0, 0, 0,
                                  1, 0, 0,
                                  1, 1, 0,
                                  0, 1, 0,
                                  0, 0, 1,
                                  1, 0, 1,
                                  1, 1, 1,
                                  0, 1, 1};

        GLfloat cubeColors[24];

        GLubyte frontIndices[4] = {4, 5, 6, 7};
        GLubyte rightIndices[4] = {1, 2, 6, 5};
        GLubyte bottomIndices[4] = {0, 1, 5, 4};
        GLubyte backIndices[4] = {0, 3, 2, 1};
        GLubyte leftIndices[4] = {0, 4, 7, 3};
        GLubyte topIndices[4] = {2, 3, 7, 6};
};

#endif // CUBE_H
