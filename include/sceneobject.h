#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>
#include "drawable.h"

using namespace std;

class SceneObject : public Drawable
{
    public:
        SceneObject();
        virtual ~SceneObject();
    protected:
    private:
    string _name;

};

#endif // SCENEOBJECT_H
