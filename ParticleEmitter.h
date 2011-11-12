#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Enums.h"
#include "Vector.h"
#include <vector>
#include "d3dUtil.h"
#include "Graphics.h"
#include "Object.h"

class Particle;

class ParticleEmitter : public Object
{
public:
	ParticleEmitter(float x, float y, float direction = 0, int max = 20, float length = 100, float speed = 5.0f,
					float interval = 0.5f, float spreadAngle = PI/4, float lifetime = 1.0f);
	~ParticleEmitter();

	void update(float dt);
	void add();
	void draw();
	
	void setDirection(float angle)			{mDirection = angle;}
	void setMax(int max)					{mMaxParticles = max;}
	void setLength(float length)			{mLength = length;}
	void setParticleVelocity(float velocity){mParticleVelocity = velocity;}
	void setInterval(float interval)		{mInterval = interval;}
	void setSpreadAngle(float angle)		{mSpreadAngle = angle;}
	void setLifeTime(float lifetime)		{mLifeTime = lifetime;}
	void setParticleDimensions(float width, float height)	{mParticleWidth = width, mParticleHeight = height;}
	void loadParticleTexture(string textureSource)	{mParticleTexture = gGraphics->loadTexture(textureSource);}

	bool effectEnded()						{return mEffectEnded;}
private:
	typedef std::vector<Particle*>::iterator	iter;
	std::vector<Particle*>						mParticleList;
	IDirect3DTexture9*	mParticleTexture;
	float		mParticleWidth, mParticleHeight;
	float		mDirection, mLength;
	float		mParticleVelocity;
	float		mScale;
	float		mLifeTime, mInterval;
	float		mDeltaSum, mLifeSum;
	float		mSpreadAngle;
	int			mMaxParticles;
	bool		mEffectEnded;
};

#endif