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

// checks ascii input
void FPSCamera::Input::keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
    case '\x1B':
	  //alutExit();
      exit(EXIT_SUCCESS);
      break;
    case ' ':
      //alSource3f(alsource, AL_POSITION, posX, posY, posZ);
      //alSourcePlay (alsource);
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
  const float deltaPosX = 0.1;
  const float deltaPosZ = 0.1;
  switch(key)
  {
    case GLUT_KEY_UP:
        _camera->_posZ += deltaPosZ;
      break;
    case GLUT_KEY_DOWN:
        _camera->_posZ -= deltaPosZ;
      break;
    case GLUT_KEY_LEFT:
        _camera->_posX -= deltaPosX;
      break;
    case GLUT_KEY_RIGHT:
        _camera->_posX += deltaPosX;
      break;
    default:
        return;
  }

  glutPostRedisplay();
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
    glutPostRedisplay();
}

void FPSCamera::Input::mouseMotion(int x, int y)
{

    mousePassive(x, y);

}
