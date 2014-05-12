#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "loadedobject.h"
#include <vector>
#include <memory>
#include <png.h>

/**
 * Loads .obj file.
 *
 * Supports obj files with normals and texture coordinates exported.
 * To generate texture coordinates, press 'u' while in edit mode and choose 'Smart project'.
 * (http://gamedev.stackexchange.com/questions/16136/blender-exporting-obj-with-texture-coords)
 *
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

array<double,2> extractTextureCoords(string input);

/// Loads png image. Invoked by initTexture.
GLubyte* loadPngImage(const char *name, int &outWidth, int &outHeight);

/// Loads texture. Invoked by objects loaded from obj files.
GLubyte* initTexture(const char *name);


#endif // OBJLOADER_H
