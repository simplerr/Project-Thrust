#ifndef ROTATINGEMITTER_H
#define ROTATINGEMITTER_H

#include "Object.h"

class RotatingEmitter : public Object
{
public:
	RotatingEmitter(float x, float y);
	~RotatingEmitter();

	void update(float dt);
	
	void setParticlesPerFrame(int speed);
	void setRotatingSpeed(float speed);
	void setRange(float range);

	void setParticleDimensions(int width, int height);
	void setParticleSpeed(float speed);
	void setParticleTexture(string textureSource);
	void setInterval(float interval);
	void setCreationRadius(float radius);
	void setLifetime(float lifetime);
private:
	float	mRotatingSpeed;
	float	mRange;
	float	mParticleSpeed;
	float	mInterval;
	float	mCounter;
	float	mCreationRadius;
	float	mLifetime;
	int		mParticlesPerFrame;
	Vector	mPartilceDimensions;
	string	mParticleTextureSource;
};

#endif