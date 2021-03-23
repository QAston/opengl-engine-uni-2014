#include "linearanimator.h"
#include "rapidjson/document.h"
#include "rapidjson/filestream.h"
#include "rapidjson/reader.h"
#include "rwconfig.h"
#include <iostream>

LinearAnimator::LinearAnimator(unique_ptr<vector<SimpleAnimEntry>> entries) {
  this->_entries = std::move(entries);
}

ObjectDesc LinearAnimator::getStateFor(int ms) {
  ObjectDesc d;
  SimpleAnimEntry entryi, entryi1;

  bool found = false;
  // Searching for t_i and t_i+1
  int t_i, t_i1;
  for (auto it = _entries->begin(); it != _entries->end(); it++) {
    auto next = std::next(it, 1);
    if (next != _entries->end() && ms >= it->time && next->time >= ms) {
      entryi = *it;
      t_i = it->time;
      entryi1 = *(std::next(it, 1));
      t_i1 = std::next(it, 1)->time;
      found = true;
      break;
    } else if (next == _entries->end()) {
      d.pos = ScenePos(it->pos[0], it->pos[1], it->pos[2], it->rot[0],
                       it->rot[1], it->rot[2]);
      d.scale = it->scale;
      return d;
    }
  }
  if (!found) {
    auto it = _entries->begin();
    d.pos = ScenePos(it->pos[0], it->pos[1], it->pos[2], it->rot[0], it->rot[1],
                     it->rot[2]);
    d.scale = it->scale;
    return d;
  }
  double a = (double)(ms - t_i) / (double)(t_i1 - t_i);
  // p(t) = 1-a * p(t_i) + a* p(t_(i+1))

  d.pos = ScenePos((1 - a) * entryi.pos[0] + a * entryi1.pos[0],
                   (1 - a) * entryi.pos[1] + a * entryi1.pos[1],
                   (1 - a) * entryi.pos[2] + a * entryi1.pos[2],
                   (1 - a) * entryi.rot[0] + a * entryi1.rot[0],
                   (1 - a) * entryi.rot[1] + a * entryi1.rot[1],
                   (1 - a) * entryi.rot[2] + a * entryi1.rot[2]);

  d.scale[0] = (1 - a) * entryi.scale[0] + a * entryi1.scale[0];
  d.scale[1] = (1 - a) * entryi.scale[1] + a * entryi1.scale[1];
  d.scale[2] = (1 - a) * entryi.scale[2] + a * entryi1.scale[2];
  return d;
}

LinearAnimator::~LinearAnimator() {
  // dtor
}

using namespace rapidjson;

struct AnimLoader {
  typedef char Ch;

  string currentFieldName = "";
  int numberArrayIndex = 0;
  bool nextReadFieldName = true;

  vector<SimpleAnimEntry> entries;
  SimpleAnimEntry current;

  void Null() { assert(false); }
  void Bool(bool /*unused*/) { assert(false); }
  void Int(int n) { Integer(n); }
  void Uint(unsigned n) { Integer(n); }
  void Int64(int64_t n) { Integer(n); }
  void Uint64(uint64_t n) { Integer(n); }
  void Double(double n) { Num(n); }

  void Integer(uint64_t n) {
    if (currentFieldName == "pos") {
      current.pos[numberArrayIndex++] = n;
    } else if (currentFieldName == "rot") {
      current.rot[numberArrayIndex++] = n;
    } else if (currentFieldName == "scale") {
      current.scale[numberArrayIndex++] = n;
    } else if (currentFieldName == "time") {
      current.time = n;
    } else {
      assert(false);
    }
    nextReadFieldName = true;
  }

  void Num(double n) {
    if (currentFieldName == "pos") {
      current.pos[numberArrayIndex++] = n;
    } else if (currentFieldName == "rot") {
      current.rot[numberArrayIndex++] = n;
    } else if (currentFieldName == "scale") {
      current.scale[numberArrayIndex++] = n;
    } else {
      assert(false);
    }
    nextReadFieldName = true;
  }

  void String(const Ch *str, int len, bool /*alloc*/) {
    if (nextReadFieldName) {
      currentFieldName = string(str, len);
      nextReadFieldName = false;
    } else {
      assert(false);
    }
  }
  void StartObject() {
    current.pos = {{0, 0, 0}};
    current.rot = {{0, 0, 0}};
    current.scale = {{1, 1, 1}};
    current.time = 0;
  }
  void EndObject(int /*s*/) {
    nextReadFieldName = true;
    entries.push_back(current);
  }
  void StartArray() {
    if (currentFieldName == "") {
    } else if (currentFieldName == "pos" || currentFieldName == "rot" ||
               currentFieldName == "scale") {
      numberArrayIndex = 0;
    } else {
      assert(false);
    }
  }
  void EndArray(int /*s*/) { nextReadFieldName = true; }
};

unique_ptr<vector<SimpleAnimEntry>> loadAnimEntries(const char *filename) {
  std::string s = resourcePath(filename);
  filename = s.c_str();
  AnimLoader handler;
  FILE *file = fopen(filename, "r");
  if (file == nullptr) {
    return nullptr;
  }

  FileStream inputStream(file);

  Reader reader;

  if (!reader.Parse<0>(inputStream, handler)) {
    std::cerr << "Error: failed to open anim file: " << filename << std::endl;
    std::cerr << reader.GetParseError() << std::endl;

    exit(0);
    return nullptr;
  }
  fclose(file);

  return make_unique<vector<SimpleAnimEntry>>(handler.entries);
}
