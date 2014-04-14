#include "inputmanagerglut.h"

#include <functional>
#include <GL/glut.h>

InputManagerGLUT* _singleton = nullptr;

InputManagerGLUT::InputManagerGLUT()
{
  glutKeyboardFunc(InputManagerGLUT::_keyboard);
  glutSpecialFunc(InputManagerGLUT::_specialInput);
  glutMotionFunc(InputManagerGLUT::_mouseMotion);
  glutPassiveMotionFunc(InputManagerGLUT::_mousePassive);
  _singleton = this;
}

InputManagerGLUT::~InputManagerGLUT()
{
    //dtor
}

void InputManagerGLUT::registerObject(shared_ptr<InputListener> object)
{
    _objects.push_back(object);
}

void InputManagerGLUT::unregisterObject(shared_ptr<InputListener>object)
{
    _objects.remove(object);
}



void InputManagerGLUT::_keyboard(unsigned char key, int x, int y)
{
    for(auto lis : _singleton->_objects)
    {
        lis->keyboard(key, x, y);
    }
}

void InputManagerGLUT::_specialInput(int key, int x, int y)
{
    for(auto lis : _singleton->_objects)
    {
        lis->specialInput(key, x, y);
    }
}

void InputManagerGLUT::_mousePassive(int x, int y)
{
    for(auto lis : _singleton->_objects)
    {
        lis->mousePassive(x, y);
    }
}

void InputManagerGLUT::_mouseMotion(int x, int y)
{
    for(auto lis : _singleton->_objects)
    {
        lis->mouseMotion(x, y);
    }
}
