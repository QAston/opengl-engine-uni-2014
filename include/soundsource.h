#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include "scenepos.h"

class SoundSource
{
    public:
        virtual ~SoundSource() {};
        virtual void play() = 0;
        virtual void setPosition(ScenePos pos) = 0;
    protected:
    private:
};

#endif // SOUNDSOURCE_H
