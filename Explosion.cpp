#include "Explosion.h"
#include "Particle.h"
#include "Level.h"
#include "ExplosionParticle.h"

Explosion::Explosion(float x, float y)
	:Object(x, y, 10, 10)
{
	setRotatingSpeed(PI/10);
	setRange(200.0f);
	setParticlesPerFrame(4);
	setInterval(0.0f);
	setCreationRadius(50.0f);
	setLifetime(2.0f);	// :TODO: Shouldn't use a static time
	setMaxParticles(20);

	setParticleSpeed(200.0f);
	setParticleTexture("imgs\\bullet.bmp");
	setParticleDimensions(6, 6);

	setVisible(false);
	setCollidable(false);
	
	mCounter = 0.5f;
	mRotation = 0.0f;
	mParticlesCreated = 0;
}
	
Explosion::~Explosion()
{

}

void Explosion::update(float dt)
{
	mCounter += dt;
	mLifetime -= dt;

	if(mCounter >= mInterval && mParticlesCreated < mMaxParticles)
	{
		// Create new particle
		for(int i = 0; i <  mParticlesPerFrame; i++)
			addParticle();

		mCounter = 0.0f;
	}

	if(mLifetime <= 0)// || mParticlesCreated >= mMaxParticles)
		kill();
}
	
void Explosion::addParticle()
{
	mRotation += mRotatingSpeed;
	//rotate(mRotatingSpeed);
	
	//float x = cosf(getRotation()) * mCreationRadius;
	//float y = sinf(getRotation()) * mCreationRadius;
	
	ExplosionParticle* particle = new ExplosionParticle(getPosition().x , getPosition().y, mPartilceDimensions.x, mPartilceDimensions.y, mParticleSpeed, mRotation);

	particle->setMaxDistance(mRange);
	particle->setSimulate(false);
	particle->setParent(this);
	getLevel()->addParticle(particle);
	mParticlesCreated++;	
}

void Explosion::addException(Object* object)
{
	mExceptionList.push_back(object);
}

bool Explosion::isException(Object* object)
{
	for(int i = 0; i < mExceptionList.size(); i++)
	{
		if(mExceptionList[i] == object)
			return true;
	}

	return false;
}

void Explosion::setParticlesPerFrame(int speed)
{
	mParticlesPerFrame = speed;
}
	
void Explosion::setRotatingSpeed(float speed)
{
	mRotatingSpeed = speed;
}
	
void Explosion::setRange(float range)
{
	mRange = range;
}

void Explosion::setParticleDimensions(int width, int height)
{
	mPartilceDimensions = Vector(width, height);
}

void Explosion::setParticleSpeed(float speed)
{
	mParticleSpeed = speed;
}

void Explosion::setParticleTexture(string textureSource)
{
	mParticleTextureSource = textureSource;
}

void Explosion::setInterval(float interval)
{
	mInterval = interval;
}

void Explosion::setCreationRadius(float radius)
{
	mCreationRadius = radius;
}

void Explosion::setLifetime(float lifetime)
{
	mLifetime = lifetime;
}

void Explosion::setMaxParticles(int maxParticles)
{
	mMaxParticles = maxParticles;
}

