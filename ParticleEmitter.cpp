#include <time.h>
#include "ParticleEmitter.h"
#include "Particle.h"

ParticleEmitter::ParticleEmitter(float x, float y, float direction, int max, float length, float speed, float interval, float spreadAngle, float lifetime)
	:Object(x, y, 1, 1)
{
	// Sett attributes
	setLength(length);
	setMax(max);
	setDirection(direction);
	setParticleVelocity(speed);
	setLength(length);
	setInterval(interval);
	setSpreadAngle(spreadAngle);
	setLifeTime(lifetime);

	setParticleDimensions(10, 10);
	getBody()->SetCollidable(false);
	mDeltaSum = 0;
	mLifeSum = 0;
	mEffectEnded = false;
	srand(time(0));
}
	
ParticleEmitter::~ParticleEmitter()
{
	// Destroy particles
	for (iter i = mParticleList.begin(); i != mParticleList.end(); ++i)
	{
		delete *i;
	}
	mParticleList.clear();
}

void ParticleEmitter::update(float dt)
{
	// One iteration delay when it gets deleted, pointers pointing on it can be informed
	if(mEffectEnded)
		kill();

	// Add and update particles
	if(mLifeSum < mLifeTime)	
	{
		// Add new particle
		if(mDeltaSum >= mInterval)	{
			if(mParticleList.size() < mMaxParticles)	{
				add();
				add();
				add();
			}

			mDeltaSum = 0;
		}
		else
			mDeltaSum += dt;

		// Update and move each particle
		for (iter i = mParticleList.begin(); i != mParticleList.end(); ++i)
		{
			(*i)->update(dt);
		}

		mLifeSum += dt;
	}
	// Remove all particles if the lifetime is exceeded
	else	{
		for(int i = 0; i < mParticleList.size(); i++)
		{
			delete mParticleList[i];
			mParticleList[i] = NULL;
			mParticleList.erase(mParticleList.begin() + i);
		}

		mParticleList.clear();

		// Kill the emitter in the next iteration
		mEffectEnded = true;
	}
}
	
void ParticleEmitter::add()
{
	// Randomize the angle within the spread angle
	int spreadAngle = mSpreadAngle * 1000;
	float spread = mDirection + (float)(rand() % spreadAngle) / 1000; 

	// Create and add new particle to the particle list
	Particle* particle = new Particle(getPosition().x, getPosition().y, mParticleWidth, mParticleHeight, mParticleVelocity, spread);
	particle->setMaxDistance(mLength);
	particle->setTexture("imgs\\blood_particle.bmp");
	mParticleList.push_back(particle);

	//showMsg("sad");
}
	
void ParticleEmitter::draw()
{
	// Draw all particles
	for(int i = 0; i < mParticleList.size(); i++)
		mParticleList[i]->draw();
}