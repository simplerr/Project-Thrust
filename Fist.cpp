#include "Fist.h"
#include "DirectInput.h"
#include "Projectile.h"
#include "Level.h"
#include "Graphics.h"
#include "FlyingFist.h"
#include "ObjectData.h"

Fist::Fist(float x, float y)
	: RangedWeapon(x, y, 22, 22, "imgs\\fist.bmp")
{
	// Init the default attributes
	initDefaults();
}
	
Fist::Fist(ObjectData* data, float x, float y)
	: RangedWeapon(data, x, y)
{
	// Init the default attributes
	initDefaults();
}

void Fist::initDefaults()
{
	// Init the default attributes 
	setType(FIST);
	mAttackDelay = 0.07f;
	mCounter = 0.0f;
	mAttacking = false;
}

Fist::~Fist()
{

}

	
void Fist::update(float dt)
{
	// Update rotation and cooldown counter
	RangedWeapon::update(dt);

	// :TODO:
	if(mAttacking)
	{
		mCounter += dt;

		if(mCounter >= mAttackDelay)
		{
			float offsetX = 40*cosf(getRotation());
			float offsetY = 40*sinf(getRotation());

			rotate(0.45);
			FlyingFist* bullet = new FlyingFist(getPosition().x + offsetX, getPosition().y + offsetY, getWidth(false), getHeight(false));
			rotate(-0.45);
	
			// Set bullet properties
			// :TODO:
			bullet->setParent(this);
			bullet->getBody()->Rotate(getRotation());
			bullet->setSpeed(400);
			bullet->setMaxDistance(getRange());
			bullet->setElasticity(0.8f);
			bullet->setAllowedBounces(1);
			bullet->setSimulate(false);
			getLevel()->addObject(bullet);

			mCounter = 0.0f;
			mAttacking = false;
			setVisible(false);
		}
	}
}
	
void Fist::draw()
{
	gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture());
	rotate(0.45);
	gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture());
	rotate(-0.45);
}

void Fist::attack(int attack)
{	
	float offsetX = 40*cosf(getRotation());
	float offsetY = 40*sinf(getRotation());
	FlyingFist* bullet = new FlyingFist(getPosition().x + offsetX, getPosition().y + offsetY, getWidth(false), getHeight(false));
	
	// Set bullet properties
	// :TODO:
	bullet->setParent(this);
	bullet->getBody()->Rotate(getRotation());
	bullet->setSpeed(400);
	bullet->setMaxDistance(getRange());
	bullet->setElasticity(0.8f);
	bullet->setAllowedBounces(1);
	bullet->setSimulate(false);
	getLevel()->addObject(bullet);

	mAttacking = true;
}

bool Fist::collided(Object* collider)
{
	int asda = 1;

	return true;
}

void Fist::childEvent(string eventMessage)
{
	if(eventMessage == "displayWeapon")	{
		setCooldownCounter(100000);	// :HACK: :>
		setVisible(true);
	}
}