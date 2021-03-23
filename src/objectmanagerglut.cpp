#include "objectmanagerglut.h"

#include <GL/glut.h>

static ObjectManagerGLUT *_singleton = nullptr;

ObjectManagerGLUT *ObjectManagerGLUT::get() {
  if (_singleton == nullptr) {
    _singleton = new ObjectManagerGLUT();
  }
  return _singleton;
}

ObjectManagerGLUT::ObjectManagerGLUT() {
  glutIdleFunc(&ObjectManagerGLUT::idle);
}

ObjectManagerGLUT::~ObjectManagerGLUT() {
  // dtor
}

void ObjectManagerGLUT::idle() {
  int msTime = glutGet(GLUT_ELAPSED_TIME);
  for (shared_ptr<GameObject> obj : _singleton->_objects) {
    obj->update(msTime);
  }
}

void ObjectManagerGLUT::registerObject(shared_ptr<GameObject> object) {
  _objects.push_back(object);
}

void ObjectManagerGLUT::unregisterObject(shared_ptr<GameObject> object) {
  _objects.remove(object);
}
