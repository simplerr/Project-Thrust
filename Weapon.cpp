#include "Weapon.h"
#include "Graphics.h"
#include "ObjectData.h"

Weapon::Weapon(float x, float y, int width, int height, string textureSource)
	: Object(x, y, width, height, textureSource)
{
	// Init the default attributes
	initDefaults();
}

Weapon::Weapon(ObjectData* data, float x, float y)
	: Object(data, x, y)
{
	// Init the default attributes
	initDefaults();

	// Get data from the XML element
	float damage = data->getValueDouble("Damage");
	float cooldown = data->getValueDouble("Cooldown");
	float standardRotation = data->getValueDouble("Rotation");

	// Set the data
	setDamage(damage);
	setCooldown(cooldown);
	setStandardRotation(standardRotation);
	setFlipped(false);
}

void Weapon::initDefaults()
{
	// Init defaults
	setStandardRotation(0.0f);
	setAttacking(false);
	setFlipped(false);
	setOffset(Vector(0, 0));
	setDamage(50.0f);
	setType(WEAPON);
	setSimulate(false);
	setCooldown(0.0f);
	mCooldownCounter = 100.0f;
}

Weapon::~Weapon()
{

}

void Weapon::update(float dt)
{
	mCooldownCounter += dt;
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
	mFlipped = flipped;
}

void Weapon::pollAttack()
{
	// Check the cooldown is active
	if(isReady())	{
		// Attack and reset the cooldown counter
		attack();
		mCooldownCounter = 0.0f;
	}
}

void Weapon::setOffset(Vector offset)
{
	mOffset = offset;
}

void Weapon::updatePosition(Vector ownerPos)
{
	// RangedWeapon and MeleeWeapon does different things
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

bool Weapon::collided(Object* collider)
{
	return true;
}

Vector Weapon::getOffset()
{
	return mOffset;
}

bool Weapon::isReady()
{
	// Return true if the counter is over the cooldown
	if(mCooldownCounter >= mCooldown)
		return true;
	else 
		return false;
}

void Weapon::setCooldown(float cooldown)
{
	mCooldown = cooldown;
}

void Weapon::incrementCooldownCounter(float dt)
{
	mCooldownCounter += dt;
}

void Weapon::setCooldownCounter(float count)
{
	mCooldownCounter = count;
}