#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Animation.h"

class Level;
class Weapon;

class Player : public Object
{
public:
	Player(float x, float y, int width, int height);
	~Player();

	void update(float dt);
	void draw();

	void equipWeapon(Weapon* weapon);
	void dropWeapon();
	void updateWeapon();
	void checkLoot();

	bool collided(Object* collider);
	void setFacingDirection(Direction direction);
	void setLevel(Level* level);
	void setVelocity(Vector velocity);
	void setVelocity(float dx, float dy);

	void damage(float damage);
private:
	IDirect3DTexture9* mHeadTexture;
	Animation*	mAnimation;
	int			mHealth;
	float		mMaxVelocity;
	float		mAcceleration;
	Direction	mFaceDirection;
	bool		mInAir;

	Weapon*		mWeapon;
};

#endif