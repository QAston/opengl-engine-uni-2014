#include "loadedobject.h"
#include "objloader.h"
#include "rwconfig.h"
#include "tiny_obj_loader.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

using namespace std;

LoadedObject::LoadedObject(const vector<array<double, 3>> &vertici,
                           const vector<array<int, 4>> &faces,
                           const vector<array<double, 3>> &normals,
                           tinyobj::material_t material,
                           const vector<array<double, 2>> &texCoords,
                           bool smooth) {
  vector<array<int, 4>>::const_iterator fit;

  _vertici = vertici;

  for (fit = faces.begin(); fit != faces.end(); ++fit) {
    array<GLubyte, 4> tmp;
    tmp[0] = (GLubyte)(*fit)[0];
    tmp[1] = (GLubyte)(*fit)[1];
    tmp[2] = (GLubyte)(*fit)[2];
    tmp[3] = (GLubyte)(*fit)[3];
    _faces.push_back(tmp);
  }
  _normals = normals;
  _material = material;
  _texCoords = texCoords;

  if (_material.diffuse_texname != "") {
    std::string s = resourcePath("/png/" + _material.diffuse_texname);
    _textureImage = loadPngImage(s.c_str(), _texWidth, _texHeight);
    if (_textureImage == nullptr) {
      cerr << "Unable to load png file :" << s << endl;
    } else {
      cout << "Image loaded. Width: " << _texWidth << " Height: " << _texHeight
           << endl;
    }
  }
  _smooth = smooth;
}

LoadedObject::~LoadedObject() {
  // dtor
}

BoundInfo LoadedObject::getBounds(glm::mat4 trans) {
  std::array<double, 6> ret{{0, 0, 0, 0, 0, 0}};
  BoundInfo retObj;

  if (!_normals.empty()) {
    retObj.hasBounds = true;
    // init with first point
    {
      auto it = _vertici.begin();
      glm::vec4 pos = glm::vec4(glm::vec3((*it)[0], (*it)[1], (*it)[2]), 1.0f);
      glm::vec4 point = trans * pos;
      ret[0] = point[0];
      ret[1] = point[1];
      ret[2] = point[2];
      ret[3] = point[0];
      ret[4] = point[1];
      ret[5] = point[2];
    }
    for (auto &it : _vertici) {
      glm::vec4 pos = glm::vec4(glm::vec3(it[0], it[1], it[2]), 1.0f);
      glm::vec4 point = trans * pos;
      if (point[0] <= ret[0]) {
        ret[0] = point[0];
      }
      if (point[1] <= ret[1]) {
        ret[1] = point[1];
      }
      if (point[2] <= ret[2]) {
        ret[2] = point[2];
      }
      if (point[0] >= ret[3]) {
        ret[3] = point[0];
      }
      if (point[1] >= ret[4]) {
        ret[4] = point[1];
      }
      if (point[2] >= ret[5]) {
        ret[5] = point[2];
      }
    }
  } else {
    retObj.hasBounds = false;
  }

  retObj.bounds = ret;

  return retObj;
}

void LoadedObject::draw() {
  if (!_normals.empty()) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, _normals.data());
  }

  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, (double *)_vertici.data());
  //} else
  // glEnableClientState (GL_COLOR_ARRAY);
  // glColorPointer (3, GL_FLOAT, 0, _colors.data());
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
  glFrontFace(GL_CCW);

  // glLoadIdentity ();
  // glTranslatef(_posX, _posY, _posZ);
  // glRotatef(rotateX, 0,1,0);
  // glRotatef(rotateY, 1,0,0);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_AMBIENT, _material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, _material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, _material.specular);
  glMaterialfv(GL_FRONT, GL_EMISSION, _material.emission);
  glMaterialf(GL_FRONT, GL_SHININESS, _material.shininess);

  glColor3fv(_material.diffuse);

  if (_textureImage != nullptr) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_DOUBLE, 0, _texCoords.data());
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, _texWidth, _texHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, _textureImage);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
  }

  for (auto &_face : _faces) {
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, _face.data());
  }

  // glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  if (!_normals.empty()) {
    glDisableClientState(GL_NORMAL_ARRAY);
  }

  // set GL state for non-textured objects
  if (_textureImage != nullptr) {
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  // glDisable(GL_LIGHTING);
  // glDisable(GL_LIGHT0);
}
