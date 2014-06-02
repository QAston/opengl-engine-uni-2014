#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "scenepos.h"

class KeyFrame
{
    public:
        KeyFrame(int time, ScenePos pos);
        virtual ~KeyFrame();
    protected:
    private:
        /// Time relative to the start of animation in msecs.
        int _time;

        /// Position of the object in _time.
        ScenePos _scenepos;

        double _scaleX;
        double _scaleY;
        double _scaleZ;
};

#endif // KEYFRAME_H
