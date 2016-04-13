#ifndef AABBCOLLISIONMGR_H
#define AABBCOLLISIONMGR_H

#include "collidingobject.h"
#include <list>
#include <memory>

class AABBCollisionMgr {
public:
  AABBCollisionMgr();
  virtual ~AABBCollisionMgr();

  bool isColliding(CollidingObject *what);

  void registerObject(shared_ptr<CollidingObject>);
  void unregisterObject(shared_ptr<CollidingObject>);
  static AABBCollisionMgr *get();

protected:
private:
  list<shared_ptr<CollidingObject>> _objects;
};

#endif // AABBCOLLISIONMGR_H
