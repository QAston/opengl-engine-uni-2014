#include "displaymanagerglut.h"

#include <GL/glut.h>

static DisplayManagerGLUT *_singleton = nullptr;

DisplayManagerGLUT *DisplayManagerGLUT::get() {
  if (_singleton == nullptr) {
    _singleton = new DisplayManagerGLUT();
  }
  return _singleton;
}

DisplayManagerGLUT::DisplayManagerGLUT() {
  glutDisplayFunc(&DisplayManagerGLUT::display);
}

void DisplayManagerGLUT::display() { _singleton->render(); }

void DisplayManagerGLUT::init(shared_ptr<Camera> camera) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  this->camera = camera;
}

void DisplayManagerGLUT::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (shared_ptr<Drawable> obj : objects) {
    camera->glLoadRevWorldMatrix();
    obj->draw();
  }
  glutSwapBuffers();
}

void DisplayManagerGLUT::registerObject(shared_ptr<Drawable> drawable) {
  objects.push_back(drawable);
}

void DisplayManagerGLUT::unregisterObject(shared_ptr<Drawable> drawable) {
  objects.remove(drawable);
}

DisplayManagerGLUT::~DisplayManagerGLUT() {
  // dtor
}
