#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "camera.h"
#include "glm/mat4x4.hpp"
#include "inputlistener.h"
#include <AL/alut.h>
#include <GL/glut.h>
#include <memory>

using namespace std;

class FPSCamera : public Camera {
public:
  FPSCamera(float x, float y, float z, float rX, float rY);
  ~FPSCamera() override;
  void glLoadRevWorldMatrix() override;
  glm::mat4 getWorldMatrix();

  class Input : public InputListener {
  public:
    explicit Input(shared_ptr<FPSCamera> camera);
    void specialInput(int key, int /*x*/, int /*y*/) override;
    void keyboard(unsigned char key, int /*x*/, int /*y*/) override;
    void mousePassive(int y, int x) override;
    void mouseMotion(int x, int y) override;

  private:
    void positionChanged();

    shared_ptr<FPSCamera> _camera;
    ALfloat _listenerOrientation[6];

    int _mouseX;
    int _mouseY;
    bool init;
  };

protected:
private:
  GLfloat _posX;
  GLfloat _posY;
  GLfloat _posZ;
  GLfloat _rotX;
  GLfloat _rotY;
};

#endif // FPSCAMERA_H
