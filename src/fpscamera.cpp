#include "fpscamera.h"
#include <cmath>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

glm::mat4 FPSCamera::getWorldMatrix()
{
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(_posX, _posY, _posZ));
    glm::mat4 rotX = glm::rotate(trans, _rotX, glm::vec3(1.0f, 0.0f,  0.0f));
    glm::mat4 rotY = glm::rotate(rotX, _rotY, glm::vec3(0.0f, 1.0f,  0.0f));
    return rotY;
}

// checks ascii input
void FPSCamera::Input::keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
    default:
        return;
  }
  glutPostRedisplay();
}

FPSCamera::Input::Input(shared_ptr<FPSCamera> camera)
{
    _camera = camera;
    init = false;
}

// checks raw keyboard input
void FPSCamera::Input::specialInput(int key, int /*x*/, int /*y*/)
{
  const float deltaPos = 0.1;

  glm::mat4 world = _camera->getWorldMatrix();
  switch(key)
  {
    case GLUT_KEY_UP:
        _camera->_posX -= world[2][0] * deltaPos;
        _camera->_posZ -= world[2][2] * deltaPos;
      break;
    case GLUT_KEY_DOWN:
        _camera->_posX += world[2][0] * deltaPos;
        _camera->_posZ += world[2][2] * deltaPos;
      break;
    case GLUT_KEY_LEFT:
        _camera->_posX -= world[0][0] * deltaPos;
        _camera->_posZ -= world[0][2] * deltaPos;
      break;
    case GLUT_KEY_RIGHT:
        _camera->_posX += world[0][0] * deltaPos;
        _camera->_posZ += world[0][2] * deltaPos;
      break;
    default:
        return;
  }

    positionChanged();
}

void FPSCamera::Input::mousePassive(int y, int x)
{
    if (!init)
    {
        init = true;
        _mouseX = x;
        _mouseY = y;
        return;
    }
    const float SPEED = 2;
    _camera->_rotX += (_mouseX-x)/SPEED;
    _camera->_rotY += (_mouseY-y)/SPEED;

    _mouseX = x;
    _mouseY = y;
    positionChanged();
}

void FPSCamera::Input::mouseMotion(int x, int y)
{

    mousePassive(x, y);

}

void FPSCamera::Input::positionChanged()
{
      glm::mat4 world = _camera->getWorldMatrix();
      alListener3f(AL_POSITION, _camera->_posX,  _camera->_posY,  _camera->_posZ);

      _listenerOrientation[0] = world[2][0];
      _listenerOrientation[1] = world[2][1];
      _listenerOrientation[2] = world[2][2];
      _listenerOrientation[3] = world[1][0];
      _listenerOrientation[4] = world[1][1];
      _listenerOrientation[5] = world[1][2];
     alListenerfv(AL_ORIENTATION, _listenerOrientation);
     glutPostRedisplay();
}
