#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>
#include <array>
#include <vector>
#include <memory>
#include <GL/glut.h>
#include "drawable.h"
#include "scenepos.h"



using namespace std;

class SceneObject : public Drawable
{
    public:
        SceneObject(string name, ScenePos pos, array<GLdouble, 3> angle, vector<shared_ptr<Drawable>> models, vector<shared_ptr<SceneObject>> subObjects)
        {
            this->_name = name;
            this->pos = pos;
            this->angle = angle;
            this->models = models;
            this->subObjects = subObjects;
        }
        virtual ~SceneObject();
        void draw();
    protected:
    private:
        string _name = string("<noname>");
        ScenePos pos = ScenePos(0, 0, 0, 0, 0, 0);
        array<GLdouble, 3> angle;
        vector<shared_ptr<Drawable>> models;
        vector<shared_ptr<SceneObject>> subObjects;
};

#endif // SCENEOBJECT_H
