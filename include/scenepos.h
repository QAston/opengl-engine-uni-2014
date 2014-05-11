#ifndef SCENEPOS_H
#define SCENEPOS_H

#include "glm/mat4x4.hpp"

class ScenePos
{
    public:
        ScenePos(float x, float y, float z, float rx, float ry)
        {
            _posX = x;
            _posY = y;
            _posZ = z;
            _rotX = rx;
            _rotY = ry;
        }
        float getPosX() { return _posX; }
        float getPosY() { return _posY; }
        float getPosZ() { return _posZ; }
        float getRotX() { return _rotX; }
        float getRotY() { return _rotY; }
        glm::mat4 calcMatrix();

        void translate(float x, float y, float z);
        void rotateX(float x);
        void rotateY(float y);
    protected:
    private:
        float _posX;
        float _posY;
        float _posZ;
        float _rotX;
        float _rotY;
};

#endif // SCENEPOS_H
