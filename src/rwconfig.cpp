#include "rwconfig.h"

// assume data dir is inside working dir, needs to run from workdir
std::string resourcePath(const std::string & p)
{
    return "data/" + p;
    //when starting from build dir could also use this as a working dir
    //return "../data/" + p;
}
