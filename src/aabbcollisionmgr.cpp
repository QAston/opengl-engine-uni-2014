#include "aabbcollisionmgr.h"

AABBCollisionMgr::AABBCollisionMgr()
{
    //ctor
}

AABBCollisionMgr::~AABBCollisionMgr()
{
    //dtor
}

void AABBCollisionMgr::registerObject(shared_ptr<BoundedObject> bObject)
{
    _objects.push_back(bObject);
}

void AABBCollisionMgr::unregisterObject(shared_ptr<BoundedObject> bObject)
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
