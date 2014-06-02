#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "objectdesc.h"
class Animator
{
    public:
        virtual ~Animator() {};
        virtual ObjectDesc getStateFor(int ms) = 0;
    protected:
    private:
};

#endif // ANIMATOR_H
