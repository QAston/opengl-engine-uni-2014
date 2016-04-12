#include "scenepos.h"

#include "glm/gtc/matrix_transform.hpp"

void ScenePos::translate(float x, float y, float z)
{
    _posX += x;
    _posY += y;
    _posZ += z;
}

void ScenePos::rotate(float val)
{
    _rotX -=  val;
}

void ScenePos::moveForward(float val)
{
    glm::mat4 world = getWorldMatrix();

    _posX -= world[2][0] * val;
    _posZ -= world[2][2] * val;
}

glm::mat4 ScenePos::getWorldMatrix()
{
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(getPosX(), getPosY(), getPosZ()));
    glm::mat4 rotZ = glm::rotate(trans, getRotZ(), glm::vec3(0.0f, 0.0f,  1.0f));
    glm::mat4 rotX = glm::rotate(rotZ, getRotX(), glm::vec3(1.0f, 0.0f,  0.0f));
    glm::mat4 rotZ1 = glm::rotate(rotX, getRotZP(), glm::vec3(0.0f, 0.0f,  1.0f));
    return rotZ1;
}
