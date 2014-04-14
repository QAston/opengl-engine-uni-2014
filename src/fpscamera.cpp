#include "fpscamera.h"

FPSCamera::FPSCamera(float x, float y, float z, float rX, float rY)
{
    _posX = x;
    _posY = y;
    _posZ = z;
    _rotX = rX;
    _rotY = rY;
}

FPSCamera::~FPSCamera()
{
    //dtor
}

void FPSCamera::glLoadRevWorldMatrix()
{
    glLoadIdentity();
    glRotatef(-_rotX, 1,0,0);
    glRotatef(-_rotY, 0,1,0);
    glTranslatef(-_posX, -_posY, -_posZ);
}
