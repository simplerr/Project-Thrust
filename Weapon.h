#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Object.h"

using namespace std;

class Weapon : public Object
{
public:
	Weapon(float x, float y, int width, int height, string textureSource);
	~Weapon();

	virtual void update(float dt);
	virtual void draw();
	virtual void attack(int attack = 0) = 0;

	void updatePosition(Vector ownerPos);
	void restoreRotation();

	void setAttacking(bool attacking);
	void setDamage(float damage);
	void setOffset(Vector offset);
	void setStandardRotation(float standardRotation);
	void setFlipped(bool flipped);

	bool	getAttacking();
	bool	getFlipped();
	float	getDamage();
private:
	Vector		mOffset;
	bool		mFlipped;
	bool		mAttacking;
	float		mDamage;
	float		mStandardRotation;
};

#endif