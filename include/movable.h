#ifndef MOVABLE_H
#define MOVABLE_H

#include "scenepos.h"

// interface
class Movable {
public:
  virtual ~Movable() {}
  virtual ScenePos getMovementTransposition() = 0;
  virtual void moveTo(ScenePos pos) = 0;

protected:
private:
};

#endif // MOVABLE_H
