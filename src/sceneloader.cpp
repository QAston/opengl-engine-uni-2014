#include "sceneloader.h"
#include "constanimator.h"
#include "linearanimator.h"
#include "objloader.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/reader.h"
#include "rwconfig.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stack>

using namespace rapidjson;

struct SceneData {
  string objectName = "<no_name>";
  string currentFieldName = "";
  int numberArrayIndex = 0;
  int objectArrayIndex = 0;

  bool nextReadFieldName = true;
  bool readingObject = true;

  array<GLdouble, 3> pos{{0, 0, 0}};
  array<GLdouble, 3> rot{{0, 0, 0}};
  array<GLdouble, 3> scale{{1, 1, 1}};

  vector<SceneObject *> subobjects;
  vector<string> models;
  string animationFile = "";
};

struct SceneHandler {
  typedef char Ch;

  stack<SceneData *> objs;
  SceneObject *loadedObject = nullptr;

  bool Null() {
    assert(false);
    return false;
  }
  bool Bool(bool /*unused*/) {
    assert(false);
    return false;
  }
  bool Int(int n) { return Num(n); }
  bool Uint(unsigned n) { return Num(n); }
  bool Int64(int64_t n) { return Num(n); }
  bool Uint64(uint64_t n) { return Num(n); }
  bool Double(double n) { return Num(n); }

  bool Key(const Ch *str, SizeType len, bool copy) {
    return String(str, len, copy);
  }

  bool RawNumber(const Ch *str, SizeType len, bool copy) {
    return String(str, len, copy);
  }


  bool Num(double n) {
    if (!objs.top()->readingObject) {
      if (objs.top()->currentFieldName == "pos") {
        objs.top()->pos[objs.top()->numberArrayIndex++] = n;
      } else if (objs.top()->currentFieldName == "rot") {
        objs.top()->rot[objs.top()->numberArrayIndex++] = n;
      } else if (objs.top()->currentFieldName == "scale") {
        objs.top()->scale[objs.top()->numberArrayIndex++] = n;
      } else {
        assert(false);
        return false;
      }
    } else {
      assert(false);
      return false;
    }
    objs.top()->nextReadFieldName = objs.top()->readingObject;
    return true;
  }

  bool String(const Ch *str, int len, bool /*alloc*/) {
    if (objs.top()->readingObject && objs.top()->nextReadFieldName) {
      objs.top()->currentFieldName = string(str, len);
      objs.top()->nextReadFieldName = false;
    } else if (objs.top()->readingObject &&
               objs.top()->currentFieldName == "name") {
      objs.top()->objectName = resourcePath(string(str, len));
      objs.top()->nextReadFieldName = true;
    } else if (objs.top()->readingObject &&
               objs.top()->currentFieldName == "animation") {
      objs.top()->animationFile = resourcePath(string(str, len));
      objs.top()->nextReadFieldName = true;
    } else if (!objs.top()->readingObject &&
               objs.top()->currentFieldName == "models") {
      objs.top()->models.push_back(resourcePath(string(str, len)));
    } else {
      assert(false);
      return false;
    }
    return true;
  }
  bool StartObject() {
    if (objs.empty() || (objs.top()->currentFieldName == "objs" &&
                         !objs.top()->readingObject)) {
      objs.push(new SceneData());
    } else {
      assert(false);
      return false;
    }
    return true;
  }
  bool EndObject(int /*s*/) {
    // object and it's children are all ready
    // can now build sceneobject
    SceneData *data = objs.top();
    objs.pop();
    vector<shared_ptr<LoadedObject>> models;
    for (auto &m : data->models) {
      for (auto d : loadObjFile(m.c_str())) {
        models.push_back(d);
      }
    }

    vector<shared_ptr<SceneObject>> subObjs;
    for (auto s : data->subobjects) {
      shared_ptr<SceneObject> sp{s};
      subObjs.push_back(sp);
    }

    ScenePos pos = ScenePos(data->pos[0], data->pos[1], data->pos[2],
                            data->rot[0], data->rot[1], data->rot[2]);
    unique_ptr<Animator> animator;

    if (data->animationFile == "") {
      ObjectDesc desc;
      desc.pos = pos;
      desc.scale = data->scale;
      animator = make_unique<ConstAnimator>(desc);
    } else {
      animator = make_unique<LinearAnimator>(
          loadAnimEntries(data->animationFile.c_str()));
    }

    SceneObject *sceneObj =
        new SceneObject(data->objectName, pos, data->scale, models, subObjs,
                        std::move(animator));

    if (objs.empty()) {
      loadedObject = sceneObj;
    } else {
      objs.top()->subobjects.push_back(sceneObj);
      objs.top()->nextReadFieldName = objs.top()->readingObject;
    }
    delete data;
    return true;
  }
  bool StartArray() {
    if (!objs.top()->readingObject) {
      assert(false);
      return false;
    }
    objs.top()->readingObject = false;
    if (objs.top()->currentFieldName == "objs") {
    } else if (objs.top()->currentFieldName == "pos" ||
               objs.top()->currentFieldName == "rot" ||
               objs.top()->currentFieldName == "scale" ||
               objs.top()->currentFieldName == "models") {
      objs.top()->numberArrayIndex = 0;
    } else {
      assert(false);
      return false;
    }
    return true;
  }
  bool EndArray(int /*s*/) {
    objs.top()->readingObject = true;
    objs.top()->nextReadFieldName = true;
    return true;
  }
};

SceneObject *loadScene(const char *filename) {
  std::string s = resourcePath(filename);
  filename = s.c_str();
  SceneHandler handler;
  FILE *file = fopen(filename, "r");
  if (file == nullptr) {
    return nullptr;
  }

  char buffer[2000];

  FileReadStream inputStream(file, buffer, 2000);

  Reader reader;

  if (!reader.Parse<0>(inputStream, handler) ||
      handler.loadedObject == nullptr) {
    cerr << "Error: failed to open scene file: " << filename << endl;
    exit(0);
    return nullptr;
  }
  fclose(file);

  return handler.loadedObject;
}
