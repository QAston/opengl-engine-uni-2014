#include "rwconfig.h"

std::string resourcePath(const std::string &p) {
  // assume data dir is inside working dir, needs to run from workdir
  // return "data/" + p;
  // when starting from build dir could also use this as a working dir
  return "../data/" + p;
}
