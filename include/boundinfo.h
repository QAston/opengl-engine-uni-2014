#ifndef BOUNDINFO_H
#define BOUNDINFO_H

#include "scenepos.h"
#include <array>
#include <iostream>

using namespace std;

struct BoundInfo
{
    // xmin, ymin, zmin, xmax, ymax, zmax
    std::array<double, 6> bounds;
    bool hasBounds;

    void printDebug()
    {
        cout << hasBounds << " " << bounds[0] << " "<<bounds[1]<<" "<<bounds[2];
    }

    array<double,24> calculateBox()
    {
        glm::mat4x4 m(1.0f);

        array<double,24> boundBoxVertices;
        if (hasBounds)
        {
            boundBoxVertices[0] = bounds[0];
            boundBoxVertices[1] = bounds[1];
            boundBoxVertices[2] = bounds[2];

            boundBoxVertices[3] = bounds[3];
            boundBoxVertices[4] = bounds[1];
            boundBoxVertices[5] = bounds[2];

            boundBoxVertices[6] = bounds[0];
            boundBoxVertices[7] = bounds[4];
            boundBoxVertices[8] = bounds[2];

            boundBoxVertices[9] = bounds[3];
            boundBoxVertices[10] = bounds[4];
            boundBoxVertices[11] = bounds[2];

            boundBoxVertices[12] = bounds[0];
            boundBoxVertices[13] = bounds[1];
            boundBoxVertices[14] = bounds[5];

            boundBoxVertices[15] = bounds[3];
            boundBoxVertices[16] = bounds[1];
            boundBoxVertices[17] = bounds[5];

            boundBoxVertices[18] = bounds[0];
            boundBoxVertices[19] = bounds[4];
            boundBoxVertices[20] = bounds[5];

            boundBoxVertices[21] = bounds[3];
            boundBoxVertices[22] = bounds[4];
            boundBoxVertices[23] = bounds[5];
        }
        return boundBoxVertices;
    }
};

#endif // BOUNDINFO_H
