#ifndef CONSTANIMATOR_H
#define CONSTANIMATOR_H

#include "animator.h"

class ConstAnimator : public Animator
{
    public:
        explicit ConstAnimator(ObjectDesc desc)
        {
            this->_desc = desc;
        }
        virtual ~ConstAnimator() {}
        virtual ObjectDesc getStateFor(int ms)
        {
            return _desc;
        }
    protected:
    private:
        ObjectDesc _desc;
};

#endif // CONSTANIMATOR_H
