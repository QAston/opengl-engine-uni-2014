#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "loadedobject.h"
#include <vector>
#include <memory>

/**
 * Loads .obj file.
 * @param path Path to .obj file.
 * @return loaded objects.
 */
vector<shared_ptr<Drawable>> loadObjFile(const char* path);

#endif // OBJLOADER_H
