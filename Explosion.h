#ifndef Explosion_H
#define Explosion_H

#include "Object.h"

class ExplosionParticle;

class Explosion : public Object
{
public:
	Explosion(float x, float y);
	~Explosion();

	void update(float dt);
	
	void addParticle();

	void addException(Object* object);
	void setParticlesPerFrame(int speed);
	void setRotatingSpeed(float speed);
	void setRange(float range);

	void setParticleDimensions(int width, int height);
	void setParticleSpeed(float speed);
	void setParticleTexture(string textureSource);
	void setInterval(float interval);
	void setCreationRadius(float radius);
	void setLifetime(float lifetime);
	void setMaxParticles(int maxParticles);

	bool isException(Object* object);
private:
	std::vector<Object*> mExceptionList;

	float	mRotation;
	float	mRotatingSpeed;
	float	mRange;
	float	mParticleSpeed;
	float	mInterval;
	float	mCounter;
	float	mCreationRadius;
	float	mLifetime;

	int		mParticlesCreated;
	int		mMaxParticles;
	int		mParticlesPerFrame;
	Vector	mPartilceDimensions;
	string	mParticleTextureSource;
};

#endif