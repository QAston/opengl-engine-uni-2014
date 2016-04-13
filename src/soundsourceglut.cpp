#include "soundsourceglut.h"

SoundSourceGLUT::SoundSourceGLUT(ALuint audioBuffer) {
  /* Generate a single source, attach the buffer to it and start playing. */
  alGenSources(1, &alsource);
  alSourcei(alsource, AL_BUFFER, audioBuffer);
  alSourcei(alsource, AL_SOURCE_RELATIVE, AL_TRUE);
}

SoundSourceGLUT::~SoundSourceGLUT() {
  // todo unregister sounds
}

void SoundSourceGLUT::play() { alSourcePlay(alsource); }

void SoundSourceGLUT::setPosition(ScenePos pos) {
  alSource3f(alsource, AL_POSITION, pos.getPosX(), pos.getPosY(),
             pos.getPosZ());
}
