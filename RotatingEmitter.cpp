#include "RotatingEmitter.h"
#include "Particle.h"
#include "Level.h"

RotatingEmitter::RotatingEmitter(float x, float y)
	:Object(x, y, 10, 10)
{
	setRotatingSpeed(PI/10);
	setRange(200.0f);
	setParticlesPerFrame(4);
	setInterval(0.0f);
	setCreationRadius(50.0f);
	setLifetime(1.0f);
	setMaxParticles(20);

	setParticleSpeed(200.0f);
	setParticleTexture("imgs\\bullet.bmp");
	setParticleDimensions(6, 6);

	setVisible(false);

	mCounter = 0.5f;
	mRotation = 0.0f;
	mParticlesCreated = 0;
}
	
RotatingEmitter::~RotatingEmitter()
{

}

void RotatingEmitter::update(float dt)
{
	mCounter += dt;
	mLifetime -= dt;

	if(mCounter >= mInterval)
	{
		// Create new particle
		for(int i = 0; i <  mParticlesPerFrame; i++)
		{
			mRotation += mRotatingSpeed;
			//rotate(mRotatingSpeed);

			//float x = cosf(getRotation()) * mCreationRadius;
			//float y = sinf(getRotation()) * mCreationRadius;

			Particle* particle = new Particle(getPosition().x , getPosition().y, mPartilceDimensions.x, mPartilceDimensions.y, mParticleSpeed, mRotation);

			particle->setMaxDistance(mRange);
			particle->setSimulate(false);
			particle->setParent(this);
			getLevel()->addParticle(particle);
			mParticlesCreated++;
		}

		mCounter = 0.0f;
	}

	if(mLifetime <= 0 || mParticlesCreated >= mMaxParticles)
		kill();
}
	
void RotatingEmitter::setParticlesPerFrame(int speed)
{
	mParticlesPerFrame = speed;
}
	
void RotatingEmitter::setRotatingSpeed(float speed)
{
	mRotatingSpeed = speed;
}
	
void RotatingEmitter::setRange(float range)
{
	mRange = range;
}

void RotatingEmitter::setParticleDimensions(int width, int height)
{
	mPartilceDimensions = Vector(width, height);
}

void RotatingEmitter::setParticleSpeed(float speed)
{
	mParticleSpeed = speed;
}

void RotatingEmitter::setParticleTexture(string textureSource)
{
	mParticleTextureSource = textureSource;
}

void RotatingEmitter::setInterval(float interval)
{
	mInterval = interval;
}

void RotatingEmitter::setCreationRadius(float radius)
{
	mCreationRadius = radius;
}

void RotatingEmitter::setLifetime(float lifetime)
{
	mLifetime = lifetime;
}

void RotatingEmitter::setMaxParticles(int maxParticles)
{
	mMaxParticles = maxParticles;
}

