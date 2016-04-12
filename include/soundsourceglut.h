#ifndef SOUNDSOURCEGLUT_H
#define SOUNDSOURCEGLUT_H

#include <AL/alut.h>
#include "soundsource.h"

class SoundSourceGLUT : public SoundSource
{
    public:
        explicit SoundSourceGLUT(ALuint audioBuffer);
        virtual ~SoundSourceGLUT();
        void play() override;
        void setPosition(ScenePos) override;
    protected:
    private:
        ALuint alsource;
};

#endif // SOUNDSOURCEGLUT_H
