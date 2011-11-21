#ifndef EXPLOSIONPARTICLE_H
#define EXPLOSIONPARTICLE_H

#include "Particle.h"

class ExplosionParticle : public Particle
{
public:
	ExplosionParticle(float x, float y, int width, int height, float speed, float angle);
	~ExplosionParticle();

	void update(float dt);
	void draw();

	bool collided(Object* collider);
private:

};

#endif