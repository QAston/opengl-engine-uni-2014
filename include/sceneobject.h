#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "animator.h"
#include "boundedobject.h"
#include "collidingobject.h"
#include "drawable.h"
#include "gameobject.h"
#include "glm/mat4x4.hpp"
#include "inputlistener.h"
#include "loadedobject.h"
#include "movable.h"
#include "scenepos.h"
#include <GL/glut.h>
#include <array>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class SceneObject : public Drawable, public GameObject, public BoundedObject {
public:
  explicit SceneObject(string name, ScenePos pos, array<GLdouble, 3> scale,
                       vector<shared_ptr<LoadedObject>> models,
                       vector<shared_ptr<SceneObject>> subObjects,
                       unique_ptr<Animator> animator) {
    this->_name = name;
    this->pos = pos;
    this->scale = scale;
    this->models = models;
    this->subObjects = subObjects;
    this->_animator = std::move(animator);
  }
  virtual ~SceneObject();
  void draw() override;
  void update(int) override;
  BoundInfo getBounds(glm::mat4 trans) override;

protected:
private:
  string _name = string("<noname>");
  ScenePos pos = ScenePos(0, 0, 0, 0, 0, 0);
  array<GLdouble, 3> scale;
  vector<shared_ptr<LoadedObject>> models;
  vector<shared_ptr<SceneObject>> subObjects;
  unique_ptr<Animator> _animator;
};

#endif // SCENEOBJECT_H
