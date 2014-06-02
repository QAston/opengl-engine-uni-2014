#include "keyframe.h"

KeyFrame::KeyFrame(int time, ScenePos pos)
{
    _time = time;
    _scenepos = pos;
}

KeyFrame::~KeyFrame()
{
    //dtor
}
