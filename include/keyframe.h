#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "scenepos.h"
#include "animationframe.h"
//#include "displaymanagerglut.h"

class KeyFrame
{
    //friend class DisplayManagerGLUT;
    public:
        KeyFrame(int time, ScenePos pos);
        virtual ~KeyFrame();

        /// Time relative to the start of animation in msecs.
        int _time;
    protected:
    private:


        /// Position of the object in _time.
        ScenePos _scenepos;

        double _scaleX;
        double _scaleY;
        double _scaleZ;
};

#endif // KEYFRAME_H
