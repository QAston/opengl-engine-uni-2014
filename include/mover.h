#ifndef MOVER_H
#define MOVER_H

#include "inputlistener.h"
#include "movable.h"

class Mover : public InputListener
{
    public:
        Mover(Movable* object) { _object = object; }
        virtual ~Mover();
        void specialInput(int key, int /*x*/, int /*y*/) override {}
        void keyboard(unsigned char key, int /*x*/, int /*y*/) override;
        void mousePassive(int x, int y) override {}
        void mouseMotion(int x, int y) override {}
    private:
        void positionChanged();
        Movable* _object;
};

#endif // MOVER_H
