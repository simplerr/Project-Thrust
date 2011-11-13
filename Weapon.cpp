#include "Weapon.h"
#include "Graphics.h"

Weapon::Weapon(float x, float y, int width, int height, string textureSource)
	: Object(x, y, width, height, textureSource)
{
	setStandardRotation(0.0f);
	setAttacking(false);
	setFlipped(false);
	setOffset(Vector(0, 0));
	setDamage(50.0f);
	setType(WEAPON);
	setSimulate(false);
}

Weapon::~Weapon()
{

}

void Weapon::update(float dt)
{

}
	
void Weapon::draw()
{
	gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), NULL, getFlipped());
}

void Weapon::setDamage(float damage)
{
	mDamage = damage;
}

void Weapon::restoreRotation()
{
	if(!mFlipped)
		setRotation(mStandardRotation);
	else
		setRotation(-mStandardRotation);
}

void Weapon::setStandardRotation(float rotation)
{
	setRotation(rotation);
	mStandardRotation = rotation;
}

void Weapon::setFlipped(bool flipped)
{
	if(flipped != mFlipped)
		setRotation(-getRotation());

	mFlipped = flipped;
}

void Weapon::setOffset(Vector offset)
{
	mOffset = offset;
}

void Weapon::updatePosition(Vector ownerPos)
{
	if(mFlipped)
		setPosition(ownerPos - mOffset);
	else
		setPosition(ownerPos + mOffset);
}

void Weapon::setAttacking(bool attacking)
{
	mAttacking = attacking;
}

bool Weapon::getAttacking()
{
	return mAttacking;
}

bool Weapon::getFlipped()
{
	return mFlipped;
}

float Weapon::getDamage()
{
	return mDamage;
}