#ifndef LOADEDOBJECT_H
#define LOADEDOBJECT_H

#include "boundedobject.h"
#include "drawable.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include <array>
#include <vector>

using namespace std;

/**
 * Class used for drawing objects loaded from .obj file.
 */
class LoadedObject : public Drawable, public BoundedObject {
public:
  LoadedObject(const vector<array<double, 3>> &vertici,
               const vector<array<int, 4>> &faces,
               const vector<array<double, 3>> &normals,
               tinyobj::material_t material,
               const vector<array<double, 2>> &texCoords, bool smooth = false);
  LoadedObject(float x, float y, float z, float rX, float rY);
  virtual ~LoadedObject();
  void draw() override;
  BoundInfo getBounds(glm::mat4 trans) override;

protected:
private:
  vector<array<GLdouble, 3>> _vertici;
  vector<array<GLubyte, 4>> _faces;
  vector<array<GLdouble, 3>> _normals;
  vector<GLfloat> _colors;
  tinyobj::material_t _material;
  vector<array<double, 2>> _texCoords;

  GLubyte *_textureImage = NULL;
  int _texWidth = 0, _texHeight = 0;
  bool _smooth;
};

#endif // LOADEDOBJECT_H
