#ifndef MOVER_H
#define MOVER_H

#include "inputlistener.h"
#include "movable.h"

class Mover : public InputListener {
public:
  Mover(Movable *object, char up, char down, char left, char right) {
    _object = object;
    _up = up;
    _down = down;
    _left = left;
    _right = right;
  }
  virtual ~Mover();
  void specialInput(int key, int /*x*/, int /*y*/) override {}
  void keyboard(unsigned char key, int /*x*/, int /*y*/) override;
  void mousePassive(int x, int y) override {}
  void mouseMotion(int x, int y) override {}

private:
  void positionChanged();
  Movable *_object;
  char _up;
  char _down;
  char _left;
  char _right;
};

#endif // MOVER_H
