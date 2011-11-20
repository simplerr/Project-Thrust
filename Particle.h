#ifndef PARTICLE_H
#define PARTICLE_H

#include "Enums.h"
#include "Object.h"

class Particle : public Object
{
public:
	Particle(float x, float y, int width, int height, float speed, float angle);
	~Particle();

	void update(float dt);
	void draw();

	void setMaxDistance(float distance)	{mMaxDistance = distance;}
	bool collided(Object* collider);

private:
	Vector			mStartPos;
	float			mMaxDistance;
	float			mTravelled;
};

#endif