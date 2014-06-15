#include "sceneobject.h"
#include <GL/gl.h>

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
    glTranslatef(movementTransposition.getPosX(), movementTransposition.getPosY(), movementTransposition.getPosZ());
    glRotatef(movementTransposition.getRotZ(), 0,0,1);
    glRotatef(movementTransposition.getRotX(), 1,0,0);
    glRotatef(movementTransposition.getRotZP(), 0,0,1);
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

