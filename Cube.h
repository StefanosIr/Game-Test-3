#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef CUBE_H_
#define CUBE_H_

class Cube : public GameAsset {
public:
	Cube();
	Cube(float x, float y, float z, float e);
	~Cube();

	virtual void update();
	virtual void draw();
	void setInterpolator(shared_ptr<IInterpolator> li);
private:
	shared_ptr<IInterpolator> li;
};

#endif // TRIANGULARPYRAMIDASSET_H_