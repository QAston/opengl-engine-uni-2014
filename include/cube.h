#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>
#include "drawable.h"
#include "soundsource.h"
#include "inputlistener.h"

class Cube : public Drawable
{
    public:
        Cube(ScenePos);
        virtual ~Cube();
        void draw();
    protected:
        float _posX;
        float _posY;
        float _posZ;
        float rotateX;
        float rotateY;

        GLint cubeVerticles[24] = {0, 0, 0,
                                  1, 0, 0,
                                  1, 1, 0,
                                  0, 1, 0,
                                  0, 0, 1,
                                  1, 0, 1,
                                  1, 1, 1,
                                  0, 1, 1};

        GLfloat cubeColors[24];

        GLubyte frontIndices[4] = {4, 5, 6, 7};
        GLubyte rightIndices[4] = {1, 2, 6, 5};
        GLubyte bottomIndices[4] = {0, 1, 5, 4};
        GLubyte backIndices[4] = {0, 3, 2, 1};
        GLubyte leftIndices[4] = {0, 4, 7, 3};
        GLubyte topIndices[4] = {2, 3, 7, 6};

    public:
        class Input : public InputListener
        {
        public:
            Input(Cube* cube, SoundSource* sound);
            void specialInput(int key, int /*x*/, int /*y*/) override;
            void keyboard(unsigned char key, int /*x*/, int /*y*/) override;
            void mousePassive(int x, int y) override;
            void mouseMotion(int x, int y) override;
        private:
            SoundSource* _sound;
        };
};

#endif // CUBE_H
