#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef TRIANGULARPYRAMIDASSET_H_
#define TRIANGULARPYRAMIDASSET_H_

class TriangularPyramidAsset : public GameAsset {
 public:
  TriangularPyramidAsset();
  TriangularPyramidAsset(float x, float y, float z);
  ~TriangularPyramidAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
};

#endif // TRIANGULARPYRAMIDASSET_H_
