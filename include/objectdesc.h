#ifndef OBJECTDESC_H
#define OBJECTDESC_H

#include "scenepos.h"
#include <array>

using namespace std;

struct ObjectDesc {
  ScenePos pos;
  std::array<double, 3> scale;
};

#endif // OBJECTDESC_H
