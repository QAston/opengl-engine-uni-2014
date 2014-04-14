#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H


class InputListener
{
    public:
        virtual ~InputListener() {}
        virtual void specialInput(int key, int /*x*/, int /*y*/);
        virtual void keyboard(unsigned char key, int /*x*/, int /*y*/);
        virtual void mousePassive(int x, int y);
        virtual void mouseMotion(int x, int y);
    protected:
    private:
};

#endif // INPUTLISTENER_H
