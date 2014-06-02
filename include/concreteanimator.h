#ifndef CONCRETEANIMATOR_H
#define CONCRETEANIMATOR_H

#include <list>

#include "animator.h"
#include "keyframe.h"


class ConcreteAnimator : public Animator
{
    public:
        ConcreteAnimator(std::list<KeyFrame> frames)
        {
            _frames = frames;
        }
        ObjectDesc getStateFor(int ms);
        virtual ~ConcreteAnimator() { }
    protected:
    private:
        std::list<KeyFrame> _frames;
};

#endif // CONCRETEANIMATOR_H
