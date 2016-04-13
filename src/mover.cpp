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

    if(key == _up) {
        pos.moveForward(deltaPos);
    } else if(key == _down) {
        pos.moveForward(-deltaPos);
    } else if(key == _left) {
        pos.rotate(-deltaRot);
    } else if(key==_right) {
        pos.rotate(deltaRot);
    } else {
        return;
}

    _object->moveTo(pos);

    positionChanged();
}
