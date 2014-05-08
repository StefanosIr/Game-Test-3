#include <vectormath/scalar/cpp/vectormath_aos.h>

using namespace Vectormath::Aos;

#ifndef IINTERPOLATOR_H_
#define IINTERPOLATOR_H_

class IInterpolator {
 public:
  virtual Vector3 update()=0;
};

#endif
