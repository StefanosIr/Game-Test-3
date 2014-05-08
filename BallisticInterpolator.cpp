#include "BallisticInterpolator.h"

BallisticInterpolator::BallisticInterpolator(Vector3 launch, int fps) {
  this->launch = make_shared<Vector3>(launch);
  this->G = make_shared<Vector3>(0.0f, -9.8f, 0.0f);
  this->fps = fps;
  this->count = 1;
}

Vector3 BallisticInterpolator::update() {
  count++;
  float time = ((float)count)/((float)fps);
  return ((*launch)*time) + ((*G) * ((1.0f/2.0f) * pow(time, 2.0f)));
}
