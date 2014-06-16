#ifndef AABBCOLLISIONMGR_H
#define AABBCOLLISIONMGR_H

#include "boundedobject.h"
#include <memory>
#include <list>

class AABBCollisionMgr
{
    public:
        AABBCollisionMgr();
        virtual ~AABBCollisionMgr();

        bool isColliding() { return true; }

        void registerObject(shared_ptr<BoundedObject>);
        void unregisterObject(shared_ptr<BoundedObject>);
        static AABBCollisionMgr* get();
    protected:
    private:
        list<shared_ptr<BoundedObject>> _objects;
};

#endif // AABBCOLLISIONMGR_H
