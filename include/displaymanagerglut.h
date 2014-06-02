#ifndef DISPLAYMANAGERGLUT_H
#define DISPLAYMANAGERGLUT_H

#include <memory>
#include <list>
using namespace std;

#include "displaymanager.h"
#include "keyframe.h"


class DisplayManagerGLUT : public DisplayManager
{
    public:
        static DisplayManagerGLUT* get();
        void init(shared_ptr<Camera>);
        void registerObject(shared_ptr<Drawable>);
        void unregisterObject(shared_ptr<Drawable>);
        void render();

        ~DisplayManagerGLUT();
    protected:
    private:
        DisplayManagerGLUT();
        static void display();
        shared_ptr<Camera> camera;
        list<shared_ptr<Drawable>> objects;
        int _framerate = 15;

};

#endif // DISPLAYMANAGERGLUT_H
