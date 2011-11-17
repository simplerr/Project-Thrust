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
	void updateTravelled(float dt);

	bool collided(Object* collider);

	void initDefaults();

	void setDamage(float damage)				{mDamage = damage;}
	void setMaxDistance(float maxDistance)		{mMaxDistance = maxDistance;}
	void setSpeed(float speed);
	void setElasticity(float elasticity)		{mElasticity = elasticity;}
	void setLifeTime(float lifetime)			{mLifeTimer = lifetime;}
	void setAllowedBounces(int allowedBounces)	{mAllowedBounces = allowedBounces;}
	void setTravelledDistance(float travelled)	{mTravelled = travelled;}

	float	getTravelled()						{return mTravelled;}
	float	getMaxDistance()					{return mMaxDistance;}
private:
	float	mDamage;
	float	mElasticity;
	float	mLifeTimer;
	float	mTravelled;
	float	mMaxDistance;
	int		mAllowedBounces;
	int		mBounces;

	// impact sounds
	// impact effect (splatter etc..)
};

#endif