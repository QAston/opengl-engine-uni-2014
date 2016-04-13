#include "sceneobject.h"
#include <GL/gl.h>

#include "glm/gtc/matrix_transform.hpp"

SceneObject::~SceneObject() {
  // dtor
}

void SceneObject::update(int msElapsed) {
  ObjectDesc desc = _animator->getStateFor(msElapsed);
  this->pos = desc.pos;
  this->scale = desc.scale;
  for (auto &subObject : subObjects) {
    subObject->update(msElapsed);
  }
  glutPostRedisplay();
}

void SceneObject::draw() {
  // calculate base matrix for all subobjects
  glTranslatef(pos.getPosX(), pos.getPosY(), pos.getPosZ());
  glRotatef(pos.getRotZ(), 0, 0, 1);
  glRotatef(pos.getRotX(), 1, 0, 0);
  glRotatef(pos.getRotZP(), 0, 0, 1);
  glScalef(scale[0], scale[1], scale[2]);

  glPushMatrix();
  for (auto &model : models) {
    // restore calculated matrix
    glPopMatrix();
    glPushMatrix();
    model->draw();
  }

  for (auto &subObject : subObjects) {
    // restore calculated matrix
    glPopMatrix();
    glPushMatrix();
    subObject->draw();
  }
  glPopMatrix();
}

BoundInfo mergeBounds(BoundInfo a, BoundInfo b) {
  if (!a.hasBounds && !b.hasBounds) {
    return a;
  }
  if (!b.hasBounds) {
    return a;
  }
  if (!a.hasBounds) {
    return b;
  }

  BoundInfo ret;
  ret.hasBounds = true;
  for (int i = 0; i < 3; ++i) {
    ret.bounds[i] = std::min(a.bounds[i], b.bounds[i]);
  }
  for (int i = 3; i < 6; ++i) {
    ret.bounds[i] = std::max(a.bounds[i], b.bounds[i]);
  }
  return ret;
}

BoundInfo SceneObject::getBounds(glm::mat4 trans) {
  trans = trans * pos.getWorldMatrix();
  trans = glm::scale(trans, glm::vec3(scale[0], scale[1], scale[2]));
  BoundInfo ret;
  ret.hasBounds = false;
  for (auto &model : models) {
    ret = mergeBounds(model->getBounds(trans), ret);
  }
  for (auto &subObject : subObjects) {
    ret = mergeBounds(subObject->getBounds(trans), ret);
  }
  return ret;
}
