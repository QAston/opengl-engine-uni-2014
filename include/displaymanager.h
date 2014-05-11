#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "drawable.h"
#include "camera.h"

// interface
class DisplayManager
{
    public:
        virtual ~DisplayManager() {}
        virtual void init(shared_ptr<Camera>) = 0;
        virtual void render() = 0;
        virtual void registerObject(shared_ptr<Drawable>) = 0;
        virtual void unregisterObject(shared_ptr<Drawable>) = 0;

    protected:
    private:

};

#endif // DISPLAYMANAGER_H
