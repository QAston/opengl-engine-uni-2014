#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "sceneobject.h"

class WorldObject : public CollidingObject,
                    public Movable,
                    public Drawable,
                    public GameObject {
public:
  explicit WorldObject(shared_ptr<SceneObject>);
  virtual ~WorldObject();

  ScenePos getMovementTransposition() override { return movementTransposition; }
  void moveTo(ScenePos pos) override;
  void setBoundingBoxVisible(bool option) { _bboxVisible = option; };

  void draw() override;
  void update(int n) override { _object->update(n); };
  BoundInfo getBounds() override {
    return _object->getBounds(movementTransposition.getWorldMatrix());
  };

protected:
private:
  shared_ptr<SceneObject> _object;
  bool _bboxVisible = true;
  ScenePos movementTransposition = ScenePos(0, 0, 0, 90, 0, -90);
};

#endif // WORLDOBJECT_H
