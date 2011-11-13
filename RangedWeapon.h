#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"
#include "enums.h"

class Level;

class RangedWeapon : public Weapon
{
public:
	RangedWeapon(float x, float y, int width, int height, string textureSource);
	~RangedWeapon();

	virtual void update(float dt);
	virtual void attack(int attack = 0);

	void	setRange(int range)				{mRange = range;}
	void	setAllowedBounces(int bounces)	{mAllowedBounces = bounces;}
	void	setLifeTime(float lifetime)		{mLifeTime = lifetime;}

	int		getRange()						{return mRange;}
	int		getAllowedBounces()				{return mAllowedBounces;}
	float	getLifeTime()					{return mLifeTime;}

private:
	float	mLifeTime;
	int		mLifeLen;
	int		mRange;
	int		mAllowedBounces;
};

#endif
