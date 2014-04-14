#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "camera.h"
#include "inputlistener.h"
#include <GL/glut.h>


class FPSCamera : public Camera
{
    public:
        FPSCamera(float x, float y, float z, float rX, float rY);
        ~FPSCamera() override;
        void glLoadRevWorldMatrix() override;
    protected:
    private:
        GLfloat _posX;
        GLfloat _posY;
        GLfloat _posZ;
        GLfloat _rotX;
        GLfloat _rotY;
};

#endif // FPSCAMERA_H
