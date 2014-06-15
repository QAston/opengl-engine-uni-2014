#ifndef BOUNDINFO_H
#define BOUNDINFO_H

#include "scenepos.h"
#include <array>

using namespace std;

struct BoundInfo
{
    // xmin, ymin, zmin, xmax, ymax, zmax
    std::array<double, 6> bounds;
    bool hasBounds;
};

#endif // BOUNDINFO_H
