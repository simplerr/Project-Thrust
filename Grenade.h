#ifndef GRENADE_H
#define GRENADE_H

#include "Projectile.h"

class ObjectData;
class Object;

class Grenade : public Projectile
{
public:
	Grenade(float x, float y, int width, int height);
	Grenade(ObjectData* data, float x, float y);
	~Grenade();

	void update(float dt);
	void draw();
	bool collided(Object*  collider);

	void setTimer(float timer);
	void setExplosionTime(float time);
private:
	float mTimer;
	float mExplosionTime;
};

#endif

