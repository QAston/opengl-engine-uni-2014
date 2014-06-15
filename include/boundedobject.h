#ifndef BOUNDEDOBJECT_H
#define BOUNDEDOBJECT_H

#include <array>

#include "glm/mat4x4.hpp"

class BoundedObject
{
    public:
        virtual ~BoundedObject() {}
        // xmin, ymin, zmin, xmax, ymax, zmax
        virtual std::array<double,6> getBounds(glm::mat4 trans) = 0;
    protected:
    private:
};

#endif // BOUNDEDOBJECT_H
