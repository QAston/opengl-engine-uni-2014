#ifndef LINEARANIMATOR_H
#define LINEARANIMATOR_H

#include "animator.h"

#include "unique.h"
#include <array>
#include <memory>
#include <vector>

using namespace std;

struct SimpleAnimEntry {
  long time;
  array<double, 3> pos;
  array<double, 3> rot;
  array<double, 3> scale;
};

class LinearAnimator : public Animator {
public:
  explicit LinearAnimator(unique_ptr<vector<SimpleAnimEntry>> entries);
  virtual ~LinearAnimator();
  ObjectDesc getStateFor(int ms) override;

protected:
private:
  unique_ptr<vector<SimpleAnimEntry>> _entries;
};

unique_ptr<vector<SimpleAnimEntry>> loadAnimEntries(const char *filename);

#endif // LINEARANIMATOR_H
