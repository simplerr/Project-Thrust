#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Object.h"

using namespace std;

class Weapon : public Object
{
public:
	Weapon(float x, float y, int width, int height, string textureSource);
	Weapon(ObjectData* data, float x, float y);
	~Weapon();

	virtual void update(float dt);
	virtual void draw();
	virtual void attack(int attack = 0) = 0;
	virtual bool collided(Object* collider);
	virtual void updatePosition(Vector ownerPos);
	virtual void setFlipped(bool flipped);
	void applyForce(Vector impulse);

	void restoreRotation();
	void initDefaults();

	void setVelocity(Vector velocity);			// Also sets the owner (players) velocity
	void setVelocity(float dx, float dy);		// Just sets the weapons velocity
	void setAttacking(bool attacking);
	void setDamage(float damage);
	void setOffset(Vector offset);
	void setStandardRotation(float standardRotation);
	void setCooldown(float cooldown);
	void setCooldownCounter(float count);

	void incrementCooldownCounter(float dt);

	bool	getAttacking();
	bool	getFlipped();
	float	getDamage();
	Vector	getOffset();

	virtual bool isReady();
private:
	Vector		mOffset;
	bool		mFlipped;
	bool		mAttacking;	// Not really what it says
	float		mDamage;
	float		mStandardRotation;
	float		mCooldownCounter;
	float		mCooldown;
};

#endif