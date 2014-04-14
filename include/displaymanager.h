#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "drawable.h"

class DisplayManager
{
    public:
        virtual ~DisplayManager() {}

        virtual registerObject(weak_ptr<Drawable>) = 0;
        virtual unregisterObject(weak_ptr<Drawable>) = 0;

        virtual void init(weak_ptr<Camera>) = 0;
    protected:
    private:
};

#endif // DISPLAYMANAGER_H
