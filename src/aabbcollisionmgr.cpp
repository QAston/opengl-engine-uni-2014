#include "aabbcollisionmgr.h"

AABBCollisionMgr::AABBCollisionMgr()
{
    //ctor
}

AABBCollisionMgr::~AABBCollisionMgr()
{
    //dtor
}

void AABBCollisionMgr::registerObject(shared_ptr<CollidingObject> bObject)
{
    _objects.push_back(bObject);
}

void AABBCollisionMgr::unregisterObject(shared_ptr<CollidingObject> bObject)
{
    _objects.remove(bObject);
}

static AABBCollisionMgr* _singleton = nullptr;

AABBCollisionMgr* AABBCollisionMgr::get()
{
    if (_singleton == nullptr)
    {
        _singleton = new AABBCollisionMgr();
    }
    return _singleton;
}

bool boundsCrossing(BoundInfo myBounds, BoundInfo otherBounds)
{
    // max coords > min coords
    return (otherBounds.bounds[3] > myBounds.bounds[0]  &&
              otherBounds.bounds[4] > myBounds.bounds[1]  &&
              otherBounds.bounds[5] > myBounds.bounds[2]  &&
    // min coords < max coords
              otherBounds.bounds[0] < myBounds.bounds[3]  &&
              otherBounds.bounds[1] < myBounds.bounds[4]  &&
              otherBounds.bounds[2] < myBounds.bounds[5]);
}

bool AABBCollisionMgr::isColliding(CollidingObject* what) {
    BoundInfo myBounds = what->getBounds();
    if (!myBounds.hasBounds)
        return false;
    for (auto itr = _objects.begin(); itr != _objects.end();++itr)
    {
        shared_ptr<CollidingObject> with = *itr;
        if (with.get() == what)
            continue;

        BoundInfo otherBounds = with->getBounds();

        if (!otherBounds.hasBounds)
            continue;

        if (boundsCrossing(myBounds, otherBounds))
            return true;
    }
    return false;
}
