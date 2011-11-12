#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Animation.h"

class ParticleEmitter;

class Enemy : public  Object
{
public:
	Enemy(float x, float y, int width, int height);
	~Enemy();

	void update(float dt);
	void draw();

	void setMaxDistance(float maxDistance);
	void setSpeed(float speed);
	void setAttackCooldown(float cooldown);
	void setEffectOffset(Vector offset);

	bool collided(Object* collider);

	void damage(float damage);
private:
	Animation*			mAnimation;
	ParticleEmitter*	mBloodEffect;
	Vector		mEffectOffset;
	float		mMaxDistance;
	float		mSpeed;
	float		mWalkedDistance;
	float		mAttackCooldown;
	float		mCooldownTimer;
	float		mHealth;
};

#endif