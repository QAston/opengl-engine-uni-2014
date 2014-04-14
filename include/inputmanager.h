#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "inputlistener.h"

//interface
class InputManager
{
    public:
        virtual ~InputManager() {}

        virtual void registerObject(weak_ptr<InputListener>) = 0;
        virtual void unregisterObject(weak_ptr<InputListener>) = 0;
    protected:
    private:
};

#endif // INPUTMANAGER_H
