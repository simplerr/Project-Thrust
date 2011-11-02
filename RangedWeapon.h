#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Object.h"
#include "enums.h"

class Level;

class RangedWeapon : public Object
{
public:
	RangedWeapon(float x, float y, int width, int height, float damage, string textureSource);
	~RangedWeapon();

	void shoot();	// or swing o.O

	void	setRange(int range)				{mRange = range;}
	void	setDamage(float damage)			{mDamage = damage;}
	void	setOwner(Object* owner)			{mOwner = owner;}
	void	setAllowedBounces(int bounces)	{mAllowedBounces = bounces;}
	void	setLifeTime(float lifetime)		{mLifeTime = lifetime;}

	float	getDamage()				{return mDamage;}
	Object*	getOwner()				{return mOwner;}
private:
	Object*	mOwner;
	float	mDamage;
	float	mLifeTime;
	int		mLifeLen;
	int		mRange;
	int		mAllowedBounces;
};

#endif
