#ifndef FLYINGFIST_H
#define FLYINGFIST_H

#include "Projectile.h"

class FlyingFist : public Projectile
{
public:
	FlyingFist(float x, float y, int width, int height);
	~FlyingFist();

	void update(float dt);

	bool collided(Object* collider);
private:
	bool mTurned;
};

#endif