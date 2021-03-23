#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
using namespace std;
#include "gameobject.h"

class ObjectManager {
public:
  ObjectManager() {}
  virtual ~ObjectManager(){};
  virtual void registerObject(shared_ptr<GameObject> o) = 0;
  virtual void unregisterObject(shared_ptr<GameObject> o) = 0;

protected:
private:
};

#endif // OBJECTMANAGER_H
