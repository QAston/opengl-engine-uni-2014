#include "worldobject.h"

#include <iostream>
#include "aabbcollisionmgr.h"

WorldObject::WorldObject(shared_ptr<SceneObject> object)
{
    _object = object;
}

WorldObject::~WorldObject()
{
    //dtor
}

void WorldObject::moveTo(ScenePos pos)
{
    ScenePos oldPos = this->movementTransposition;

    movementTransposition = pos;

    AABBCollisionMgr*mgr =  AABBCollisionMgr::get();

    // it's colliding - move to old pos
    if (mgr->isColliding(this))
        movementTransposition = oldPos;
}

void WorldObject::draw()
{
    BoundInfo bounds = getBounds();
    if (bounds.hasBounds)
    {
        array<double,24> boundBoxVertices = bounds.calculateBox();

        GLubyte frontIndices[4] = {1,3,2,0};
        GLubyte rightIndices[4] = {1,3,7,5};
        GLubyte bottomIndices[4] = {5,1,0,4};
        GLubyte backIndices[4] = {5,4,6,7};
        GLubyte leftIndices[4] = {4,0,2,6};
        GLubyte topIndices[4] = {3,2,6,7};

        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glFrontFace(GL_CCW);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer (3, GL_DOUBLE, 0, (double*)boundBoxVertices.data());

        glColor3f(1.0f, 1.0f, 1.0f);

        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
    glTranslatef(movementTransposition.getPosX(), movementTransposition.getPosY(), movementTransposition.getPosZ());
    glRotatef(movementTransposition.getRotZ(), 0,0,1);
    glRotatef(movementTransposition.getRotX(), 1,0,0);
    glRotatef(movementTransposition.getRotZP(), 0,0,1);
    _object->draw();
}
