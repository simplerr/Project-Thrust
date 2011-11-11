#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Animation.h"

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

	bool collided(Object* collider);

	void damage(float damage);
private:
	Animation*	mAnimation;
	float		mMaxDistance;
	float		mSpeed;
	float		mWalkedDistance;
	float		mAttackCooldown;
	float		mCooldownTimer;
	float		mHealth;
};

#endif