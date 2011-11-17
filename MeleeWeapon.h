#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"
#include <string>

using namespace std;

class MeleeWeapon : public Weapon
{
public:
	MeleeWeapon(float x, float y, int width, int height, string textureSource);
	MeleeWeapon(ObjectData* data, float x, float y);

	~MeleeWeapon();

	void update(float dt);
	void draw();
	void attack(int attack = 0);


	void setFlipped(bool flipped);
	void updatePosition(Vector ownerPos);

	virtual bool collided(Object* collider);
private:
	float	mAttackTime;
	float	mElapsedTime;
};

#endif