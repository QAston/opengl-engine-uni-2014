#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>
#include <array>
#include <vector>
#include <memory>
#include <GL/glut.h>
#include "drawable.h"
#include "scenepos.h"
#include "gameobject.h"
#include "animator.h"


using namespace std;

class SceneObject : public Drawable, public GameObject
{
    public:
        SceneObject(string name, ScenePos pos, array<GLdouble, 3> scale, vector<shared_ptr<Drawable>> models, vector<shared_ptr<SceneObject>> subObjects, unique_ptr<Animator> animator)
        {
            this->_name = name;
            this->pos = pos;
            this->scale = scale;
            this->models = models;
            this->subObjects = subObjects;
            this->_animator = std::move(animator);
        }
        virtual ~SceneObject();
        void draw();
        void update(int);
    protected:
    private:
        string _name = string("<noname>");
        ScenePos pos = ScenePos(0, 0, 0, 0, 0, 0);
        array<GLdouble, 3> scale;
        vector<shared_ptr<Drawable>> models;
        vector<shared_ptr<SceneObject>> subObjects;
        unique_ptr<Animator> _animator;
};

#endif // SCENEOBJECT_H
