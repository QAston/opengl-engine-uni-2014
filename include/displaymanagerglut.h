#ifndef DISPLAYMANAGERGLUT_H
#define DISPLAYMANAGERGLUT_H

#include <memory>
#include <list>
using namespace std;

#include "displaymanager.h"
#include "animationframe.h"
#include "keyframe.h"


class DisplayManagerGLUT : public DisplayManager
{
    public:
        static DisplayManagerGLUT* get();
        void init(shared_ptr<Camera>);
        void registerObject(shared_ptr<Drawable>);
        void unregisterObject(shared_ptr<Drawable>);
        void render();

        /// Calculates animation frames from keyframes.
        list<AnimationFrame> createAnimationFrames(const KeyFrame &d1, const KeyFrame &d2);
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
