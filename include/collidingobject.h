#ifndef COLLIDINGOBJECT_H
#define COLLIDINGOBJECT_H

#include "glm/mat4x4.hpp"
#include "boundinfo.h"

class CollidingObject
{
    public:
        virtual ~CollidingObject() {}
        /// returns object bounds in world coords
        virtual BoundInfo getBounds() = 0;
    protected:
    private:
};

#endif // COLLIDINGOBJECT_H
