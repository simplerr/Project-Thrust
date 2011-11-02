#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "d3dUtil.h"
#include "Object.h"
#include "enums.h"

class Projectile : public Object
{
public:
	Projectile(float x, float y, int width, int height, string textureSource);
	~Projectile();

	void update(float dt);
	
	void collided(Object* collider);

	void setDamage(float damage)				{mDamage = damage;}
	void setMaxDistance(float maxDistance)		{mMaxDistance = maxDistance;}
	void setSpeed(float speed);
	void setOwner(Object* owner);
	void setElasticity(float elasticity)		{mElasticity = elasticity;}
	void setLifeTime(float lifetime)			{mLifeTimer = lifetime;}
	void setAllowedBounces(int allowedBounces)	{mBounces = allowedBounces;}

	Object* getOwner();

private:
	Object* mOwner;
	float	mDamage;
	float	mElasticity;
	float	mLifeTimer;
	int		mTravelled;
	int		mMaxDistance;
	int		mBounces;

	// impact sounds
	// impact effect (splatter etc..)
};

#endif