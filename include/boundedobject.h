#ifndef BOUNDEDOBJECT_H
#define BOUNDEDOBJECT_H

#include "glm/mat4x4.hpp"
#include "boundinfo.h"

class BoundedObject
{
    public:
        virtual ~BoundedObject() {}
        virtual BoundInfo getBounds(glm::mat4 trans) = 0;
    protected:
    private:
};

#endif // BOUNDEDOBJECT_H
