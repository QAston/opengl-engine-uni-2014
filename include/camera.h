#ifndef CAMERA_H
#define CAMERA_H

// interface
class Camera {
public:
  virtual ~Camera(){};
  virtual void glLoadRevWorldMatrix() = 0;

protected:
private:
};

#endif // CAMERA_H
