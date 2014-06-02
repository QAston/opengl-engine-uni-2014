#include "keyframe.h"

KeyFrame::KeyFrame(int time, ObjectDesc desc)
{
    _time = time;
    _desc = desc;
}

KeyFrame::~KeyFrame()
{
    //dtor
}
