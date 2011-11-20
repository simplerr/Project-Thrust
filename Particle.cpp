#include "Particle.h"
#include "Graphics.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

Particle::Particle(float x, float y, int width, int height, float speed, float angle)
	:Object(x, y, width, height)
{
	mStartPos = Vector(x, y);
	mMaxDistance = 100;
	mTravelled = 0;
	setVelocity(speed * cosf(angle), speed * sinf(angle));
	setSimulate(false);
	setType(PARTICLE);

	// Could test which type and load the correct texture
}
	
Particle::~Particle()
{

}
	
void Particle::update(float dt)
{	
	// Move the particle - could be optimized by removing the cosfs, sinsfs and sqrt
	if(mTravelled < mMaxDistance)	{
		Vector velocity = getVelocity();
		mTravelled += dt * Mathematics::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
	}
	else	{
		// Move the start pos if it's outside the range
		//setPosition(mStartPos);
		//mTravelled = 0.0f;

		// :NOTE: Not for all!
		kill(); 
	}

	// Move the particle, not affected by anything
	getBody()->Move(getVelocity() * dt);
}

void Particle::draw()
{
	Object::draw();
}

bool Particle::collided(Object* collider)
{
	Collision collision = polyCollision(this->getBody(), collider->getBody());
	float impulse = 5.0f;

	float x = collider->getPosition().x - getPosition().x;
	float y = collider->getPosition().y - getPosition().y;
	float angle = atan2f(y, x);

	x = cosf(angle) * impulse;
	y = sinf(angle) * impulse;

	// :NOTE: Todo! Other weapon types must also be checked!!
	if(collider->getType() == RANGED_WEAPON)	{
		collider->getParent()->getBody()->ApplyForce(Vector(x, y), collider->getPosition());
	}
	else
		if(collider != getParent() && collider->getSimulate())
			collider->getBody()->ApplyForce(Vector(x, y), collider->getPosition());

	kill();

	return true;
}