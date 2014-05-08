#include "GameAsset.h"
#include "IInterpolator.h"
#include "TriangularPyramidAsset.h"


#ifndef PLAYERASSET_H_
#define PLAYERASSET_H_

class PlayerAsset : public GameAsset {
 public:
  PlayerAsset();
  PlayerAsset(float x, float y, float z);
  ~PlayerAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;



};
#endif // PLAYERASSET_H_