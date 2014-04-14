#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "inputlistener.h"
#include <memory>
using namespace std;

//interface
class InputManager
{
    public:
        virtual ~InputManager() {}

        virtual void registerObject(shared_ptr<InputListener>) = 0;
        virtual void unregisterObject(shared_ptr<InputListener>) = 0;
    protected:
    private:
};

#endif // INPUTMANAGER_H
