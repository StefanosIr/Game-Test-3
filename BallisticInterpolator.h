#include <vectormath/scalar/cpp/vectormath_aos.h>

#include<memory>

#include "IInterpolator.h"

using namespace Vectormath::Aos;
using namespace std;

#ifndef BALLISTICINTERPOLATOR_H_
#define BALLISTICINTERPOLATOR_H_

class BallisticInterpolator : public IInterpolator {
 public:
  BallisticInterpolator(Vector3 launch, int fps);
  Vector3 update();
 private:
  int fps, count;
  shared_ptr<Vector3> launch, G;
};

#endif
