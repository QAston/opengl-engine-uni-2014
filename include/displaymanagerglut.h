#ifndef DISPLAYMANAGERGLUT_H
#define DISPLAYMANAGERGLUT_H

#include <memory>
using namespace std;

#include "displaymanager.h"


class DisplayManagerGLUT : public DisplayManager
{
    public:
        void init(weak_ptr<Camera>);
        void registerObject(weak_ptr<Drawable>);
        void unregisterObject(weak_ptr<Drawable>);
        ~DisplayManagerGLUT();
    protected:
    private:

};

#endif // DISPLAYMANAGERGLUT_H
