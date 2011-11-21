#include "Grenade.h"
#include "Level.h"
#include "RotatingEmitter.h"

Grenade::Grenade(float x, float y, int width, int height)
	: Projectile(x, y, width, height, "imgs\\grenade.bmp")
{
	// Two seconds timer as default
	mTimer = 2.0f;
}
	
Grenade::Grenade(ObjectData* data, float x, float y)
	: Projectile(data, x, y)
{
	float timer = data->getValueDouble("Timer");

	setTimer(timer);
}
	
Grenade::~Grenade()
{

}

void Grenade::update(float dt)
{
	if(mTimer > 0.0f)	
		mTimer -= dt;
	else
	{
		// Create the explosion particles
		RotatingEmitter* emitter = new RotatingEmitter(getPosition().x, getPosition().y);
		emitter->setParticleTexture("imgs\\explosion_particle.bmp");		
		emitter->setParticleSpeed(900.0f),
		emitter->setSimulate(false);
		getLevel()->addObject(emitter);
		kill();	
	}
}
	
void Grenade::draw()
{
	Object::draw();
}
	
bool Grenade::collided(Object*  collider)
{
	Projectile::collided(collider);

	return true;
}

void Grenade::setTimer(float timer)
{
	mTimer = timer;
}