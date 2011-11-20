#ifndef FIST_H
#define FIST_H

#include "RangedWeapon.h"
#include "d3dUtil.h"

class ObjectData;

class Fist : public RangedWeapon
{
public:
	Fist(float x, float y);
	Fist(ObjectData* data, float x, float y);
	~Fist();

	void update(float dt);
	void draw();
	void attack(int attack);

	void initDefaults();

	void childEvent(string eventMessage);
	bool collided(Object* collider);
private:
	float	mAttackDelay;
	float	mCounter;
	bool	mAttacking;
};

#endif