#ifndef OBJECTDESC_H
#define OBJECTDESC_H

#include "scenepos.h"
#include <array>

struct ObjectDesc
{
    ScenePos pos;
    array<double, 3> scale;
};

#endif // OBJECTDESC_H
