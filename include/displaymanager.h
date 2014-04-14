#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "drawable.h"
#include "camera.h"

// interface
class DisplayManager
{
    public:
        virtual ~DisplayManager() {}
        virtual void init(weak_ptr<Camera>) = 0;

        virtual void registerObject(weak_ptr<Drawable>) = 0;
        virtual void unregisterObject(weak_ptr<Drawable>) = 0;

    protected:
    private:
};

#endif // DISPLAYMANAGER_H
