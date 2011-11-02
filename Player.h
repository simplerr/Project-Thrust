#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Animation.h"

class Level;
class RangedWeapon;

class Player : public Object
{
public:
	Player(float x, float y, int width, int height);
	~Player();

	void update(float dt);
	void draw();

	void updateWeapon();
	void collided(Object* collider);
	void setFacingDirection(Direction direction);
	void setLevel(Level* level);
private:
	Animation*	mAnimation;
	int			mHealth;
	float		mMaxVelocity;
	float		mAcceleration;
	Direction	mFaceDirection;
	bool		mInAir;

	RangedWeapon* mWeapon;
};

#endif