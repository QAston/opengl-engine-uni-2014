#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "camera.h"
#include "inputlistener.h"
#include <GL/glut.h>
#include <memory>
#include "glm/mat4x4.hpp"

using namespace std;


class FPSCamera : public Camera
{
    public:
        FPSCamera(float x, float y, float z, float rX, float rY);
        ~FPSCamera() override;
        void glLoadRevWorldMatrix() override;
        glm::mat4 getWorldMatrix();

        class Input : public InputListener
        {
        public:
            Input(shared_ptr<FPSCamera> camera);
            void specialInput(int key, int /*x*/, int /*y*/) override;
            void keyboard(unsigned char key, int /*x*/, int /*y*/) override;
            void mousePassive(int x, int y) override;
            void mouseMotion(int x, int y) override;
        private:
            shared_ptr<FPSCamera> _camera;

            int _mouseX;
            int _mouseY;
            bool init;
        };
    protected:
    private:
        GLfloat _posX;
        GLfloat _posY;
        GLfloat _posZ;
        GLfloat _rotX;
        GLfloat _rotY;
};

#endif // FPSCAMERA_H
