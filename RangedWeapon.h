#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include <string>
#include "Weapon.h"
#include "enums.h"

using namespace std;

class Level;
class ObjectData;

class RangedWeapon : public Weapon
{
public:
	RangedWeapon(float x, float y, int width, int height, string textureSource);
	RangedWeapon(ObjectData* data, float x, float y);
	~RangedWeapon();

	virtual void	update(float dt);
	virtual void	draw();
	virtual void	attack(int attack = 0);
	virtual bool	collided(Object* collider);
	void			setProjectile(string projectileClass, string type);
	void			updatePosition(Vector ownerPos);
	void			setFlipped(bool flipped);

	void	setRange(int range)				{mRange = range;}

	int		getRange()						{return mRange;}

private:
	int		mRange;
	string  mProjectileClass;
	string	mProjectileType;
};

#endif
