#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
  virtual ~GameObject() {}
  virtual void update(int timeElapsed) = 0;

protected:
private:
};

#endif // GAMEOBJECT_H
