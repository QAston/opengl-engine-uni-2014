#ifndef DISPLAYMANAGERGLUT_H
#define DISPLAYMANAGERGLUT_H

#include <list>
#include <memory>
using namespace std;

#include "displaymanager.h"
#include "keyframe.h"

class DisplayManagerGLUT : public DisplayManager {
public:
  static DisplayManagerGLUT *get();
  void init(shared_ptr<Camera>) override;
  void registerObject(shared_ptr<Drawable>) override;
  void unregisterObject(shared_ptr<Drawable>) override;
  void render() override;

  ~DisplayManagerGLUT();

protected:
private:
  DisplayManagerGLUT();
  static void display();
  shared_ptr<Camera> camera;
  list<shared_ptr<Drawable>> objects;
};

#endif // DISPLAYMANAGERGLUT_H
