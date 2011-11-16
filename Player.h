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

	void init();
	void update(float dt);
	void draw();

	void childEvent(string eventMessage);

	void equipWeapon(Weapon* weapon);
	void dropWeapon();
	void checkLoot();

	void updateHead();

	bool collided(Object* collider);
	void setFacingDirection(Direction direction);
	void setLevel(Level* level);
	void setVelocity(Vector velocity);
	void setVelocity(float dx, float dy);

	void damage(float damage);
private:
	IDirect3DTexture9* mHeadTexture;
	Animation*	mAnimation;
	Direction	mFaceDirection;
	int			mHealth;
	float		mMaxVelocity;
	float		mAcceleration;
	float		mHeadRotation;
	bool		mInAir;
	bool		mHeadFlipped;

	Weapon*		mWeapon;
};

#endif