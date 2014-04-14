#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "camera.h"
#include <GL/glut.h>


class FPSCamera : public Camera
{
    public:
        FPSCamera();
        ~FPSCamera() override;
    protected:
    private:
        GLfloat _posX;
        GLfloat _posY;
        GLfloat _posZ;
};

#endif // FPSCAMERA_H
