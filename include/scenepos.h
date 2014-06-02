#ifndef SCENEPOS_H
#define SCENEPOS_H

#include "glm/mat4x4.hpp"

class ScenePos
{
    public:
        ScenePos(float x = 0, float y = 0, float z = 0, float rz = 0, float rx = 0, float rzp = 0)
        {
            _posX = x;
            _posY = y;
            _posZ = z;
            _rotZ = rz;
            _rotX = rx;
            _rotZP = rzp;
        }
        float getPosX() { return _posX; }
        float getPosY() { return _posY; }
        float getPosZ() { return _posZ; }
        float getRotZ() { return _rotZ; }
        float getRotX() { return _rotX; }
        float getRotZP() { return _rotZP; }
        glm::mat4 calcMatrix();

        void translate(float x, float y, float z);
        void rotateX(float x);
        void rotateY(float y);
    protected:
    private:
        float _posX;
        float _posY;
        float _posZ;
        float _rotZ;
        float _rotX;
        float _rotZP;
};

#endif // SCENEPOS_H
