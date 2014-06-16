#include "sceneobject.h"
#include <GL/gl.h>

#include "glm/gtc/matrix_transform.hpp"

SceneObject::~SceneObject()
{
    //dtor
}

void SceneObject::update(int msElapsed)
{
    ObjectDesc desc = _animator->getStateFor(msElapsed);
    this->pos = desc.pos;
    this->scale = desc.scale;
    for(auto sItr = subObjects.begin(); sItr != subObjects.end(); ++sItr)
    {
        (*sItr)->update(msElapsed);
    }
    glutPostRedisplay();
}

void SceneObject::draw()
{
    // calculate base matrix for all subobjects
    glTranslatef(pos.getPosX(), pos.getPosY(), pos.getPosZ());
    glRotatef(pos.getRotZ(), 0,0,1);
    glRotatef(pos.getRotX(), 1,0,0);
    glRotatef(pos.getRotZP(), 0,0,1);
    glScalef(scale[0], scale[1], scale[2]);

    glPushMatrix();
    for(auto mItr = models.begin(); mItr != models.end(); ++mItr)
    {
        // restore calculated matrix
        glPopMatrix();
        glPushMatrix();
        (*mItr)->draw();
    }

    for(auto sItr = subObjects.begin(); sItr != subObjects.end(); ++sItr)
    {
        // restore calculated matrix
        glPopMatrix();
        glPushMatrix();
        (*sItr)->draw();
    }
    glPopMatrix();
}

BoundInfo mergeBounds(BoundInfo a, BoundInfo b)
{
    if (!a.hasBounds && !b.hasBounds)
        return a;
    if (!b.hasBounds)
        return a;
    if (!a.hasBounds)
        return b;

    BoundInfo ret;
    ret.hasBounds = true;
    for(int i = 0; i < 3; ++i)
        ret.bounds[i] = std::min(a.bounds[i], b.bounds[i]);
    for(int i = 3; i < 6; ++i)
        ret.bounds[i] = std::max(a.bounds[i], b.bounds[i]);
    return ret;
}

BoundInfo SceneObject::getBounds(glm::mat4 trans)
{
    trans = trans * pos.getWorldMatrix();
    trans = glm::scale(trans, glm::vec3(scale[0], scale[1], scale[2]));
    BoundInfo ret;
    ret.hasBounds = false;
    for(auto mItr = models.begin(); mItr != models.end(); ++mItr)
    {
        ret = mergeBounds((*mItr)->getBounds(trans), ret);
    }
    for(auto sItr = subObjects.begin(); sItr != subObjects.end(); ++sItr)
    {
        ret = mergeBounds((*sItr)->getBounds(trans), ret);
    }
    return ret;
}
