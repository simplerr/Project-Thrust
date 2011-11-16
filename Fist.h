#ifndef FIST_H
#define FIST_H

#include "RangedWeapon.h"
#include "d3dUtil.h"

class Fist : public RangedWeapon
{
public:
	Fist(float x, float y);
	~Fist();

	void update(float dt);
	void draw();
	void attack(int attack);

	void childEvent(string eventMessage);
	bool collided(Object* collider);
private:
	IDirect3DTexture9* mSecondTexture;
	float	mAttackDelay;
	float	mCounter;
	bool	mAttacking;
};

#endif