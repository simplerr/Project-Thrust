#include "Particle.h"
#include "Graphics.h"

Particle::Particle(float x, float y, int width, int height, float speed, float angle)
	:Object(x, y, width, height)
{
	mStartPos = Vector(x, y);
	mMaxDistance = 100;
	mTravelled = 0;
	setVelocity(speed * cosf(angle), speed * sinf(angle));

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
		mTravelled += Mathematics::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
	}
	else	{
		// Move the start pos if it's outside the range
		setPosition(mStartPos);
		mTravelled = 0.0f;
	}

	// Move the particle, not affected by anything
	getBody()->move(getVelocity());
}