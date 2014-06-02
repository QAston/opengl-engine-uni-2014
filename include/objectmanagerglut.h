#ifndef OBJECTMANAGERGLUT_H
#define OBJECTMANAGERGLUT_H

#include "objectmanager.h"
#include <list>
using namespace std;

class ObjectManagerGLUT : public ObjectManager
{
    public:
        static ObjectManagerGLUT* get();
        ~ObjectManagerGLUT();
        void registerObject(shared_ptr<GameObject>);
        void unregisterObject(shared_ptr<GameObject>);
    protected:
    private:
        ObjectManagerGLUT();
        static void idle();
        list<shared_ptr<GameObject>> _objects;
};

#endif // OBJECTMANAGERGLUT_H
