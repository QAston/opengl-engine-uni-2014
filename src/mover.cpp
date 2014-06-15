#include "mover.h"

#include <GL/glut.h>

Mover::~Mover()
{
    //dtor
}

void Mover::positionChanged()
{
     glutPostRedisplay();
}

void Mover::keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  const float deltaPos = 0.1;
  const float deltaRot = 1;

  ScenePos pos = _object->getMovementTransposition();

    switch(key)
    {
    case 'w':
        pos.moveForward(deltaPos);
        break;
    case 's':
        pos.moveForward(-deltaPos);
        break;
    case 'a':
        pos.rotate(-deltaRot);
        break;
    case 'd':
        pos.rotate(deltaRot);
        break;
    }

    _object->moveTo(pos);

    positionChanged();
}
