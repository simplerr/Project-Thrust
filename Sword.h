#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"
#include <string>

using namespace std;

class Sword : public Weapon
{
public:
	Sword(float x, float y);
	~Sword();

	void update(float dt);
	void draw();
	void attack(int attack = 0);

	void collided(Object* collider);
private:
	float	mAttackTime;
	float	mElapsedTime;
};

#endif