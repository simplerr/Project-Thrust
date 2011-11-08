#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"
#include "enums.h"

class Level;

class RangedWeapon : public Weapon
{
public:
	RangedWeapon(float x, float y, int width, int height, float damage, string textureSource);
	~RangedWeapon();

	void attack(int attack = 0);

	void	setRange(int range)				{mRange = range;}
	void	setAllowedBounces(int bounces)	{mAllowedBounces = bounces;}
	void	setLifeTime(float lifetime)		{mLifeTime = lifetime;}
private:
	float	mLifeTime;
	int		mLifeLen;
	int		mRange;
	int		mAllowedBounces;
};

#endif
