#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "scenepos.h"
#include "animationframe.h"
#include "objectdesc.h"

class KeyFrame
{
    //friend class DisplayManagerGLUT;
    public:
        KeyFrame(int time, ObjectDesc desc);
        virtual ~KeyFrame();

        /// Time relative to the start of animation in msecs.
        int _time;
        ObjectDesc _desc;
    protected:
    private:
};

#endif // KEYFRAME_H
