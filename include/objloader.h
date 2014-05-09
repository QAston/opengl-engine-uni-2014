#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "loadedobject.h"
#include <vector>
#include <memory>

/**
 * Loads .obj file.
 * @todo Import normal vectors, textures.
 * @param path Path to .obj file.
 * @return loaded objects.
 */
vector<shared_ptr<Drawable>> loadObjFile(const char* path);

/**
 * Helper function. Strips "//2" from "24//3" in face declaration line.
 */
string stripFaceIndex(string input);

/**
 * Extracts a single normal vector form input line
 * @param input Single line. Example: "vn 0.000000 -1.000000 -0.000000"
 */
array<double,3> extractNormal(string input);

#endif // OBJLOADER_H
