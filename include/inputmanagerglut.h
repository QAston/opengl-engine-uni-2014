#ifndef INPUTMANAGERGLUT_H
#define INPUTMANAGERGLUT_H

#include "inputmanager.h"
#include <list>

using namespace std;

class InputManagerGLUT : public InputManager {
public:
  ~InputManagerGLUT() override;

  void registerObject(shared_ptr<InputListener>) override;
  void unregisterObject(shared_ptr<InputListener>) override;

  static InputManagerGLUT *get();

protected:
private:
  InputManagerGLUT();
  static void _specialInput(int key, int /*x*/, int /*y*/);
  static void _keyboard(unsigned char key, int /*x*/, int /*y*/);
  static void _mousePassive(int x, int y);
  static void _mouseMotion(int x, int y);

  list<shared_ptr<InputListener>> _objects;
};

#endif // INPUTMANAGERGLUT_H
