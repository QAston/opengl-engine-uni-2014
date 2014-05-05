#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "loadedobject.h"
#include <vector>

/**
 * Loads .obj file.
 * @param path Path to .obj file.
 * @return loaded objects.
 */
vector<LoadedObject> loadObjFile(const char* path);

#endif // OBJLOADER_H
