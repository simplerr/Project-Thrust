#ifndef FLYINGFIST_H
#define FLYINGFIST_H

#include "Projectile.h"

class ObjectData;

class FlyingFist : public Projectile
{
public:
	FlyingFist(float x, float y, int width, int height);
	FlyingFist(ObjectData* data, float x, float y);
	~FlyingFist();

	void update(float dt);

	bool collided(Object* collider);
private:
	bool mTurned;
};

#endif