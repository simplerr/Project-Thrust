#include "Fist.h"
#include "DirectInput.h"
#include "Projectile.h"
#include "Level.h"
#include "Graphics.h"
#include "FlyingFist.h"
#include "ObjectData.h"

Fist::Fist(float x, float y)
	: RangedWeapon(x, y, 22, 22, "imgs\\simple_fist.bmp")
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
	mWaiting = false;
	mHandleChildEvent = false;
}

Fist::~Fist()
{

}

	
void Fist::update(float dt)
{
	// Update rotation and cooldown counter
	RangedWeapon::update(dt);

	if(mWaiting)
	{
		mCounter += dt;

		if(mCounter >= mAttackDelay)
		{
			spawnSecondFist();
			
			mCounter = 0.0f;
			setVisible(false);
			mWaiting = false;
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
	ObjectData* data = getLevel()->loadObjectData("FlyingFist");
	FlyingFist* bullet = new FlyingFist(data, getPosition().x + offsetX, getPosition().y + offsetY);
	
	// Set bullet properties
	bullet->setParent(this);
	bullet->getBody()->Rotate(getRotation());
	bullet->setSpeed(bullet->getSpeed());	// Important to set the speed after rotating
	bullet->setMaxDistance(getRange());
	getLevel()->addObject(bullet);

	mWaiting = true;
	mHandleChildEvent = false;	
}

void Fist::spawnSecondFist()
{
	float offsetX = 40 * cosf(getRotation());
	float offsetY = 40 * sinf(getRotation());

	rotate(0.45);
	ObjectData* data = getLevel()->loadObjectData("FlyingFist");
	FlyingFist* bullet = new FlyingFist(data, getPosition().x + offsetX, getPosition().y + offsetY);
	rotate(-0.45);

	// Set bullet properties
	bullet->setParent(this);
	bullet->getBody()->Rotate(getRotation());
	bullet->setSpeed(bullet->getSpeed());
	bullet->setMaxDistance(getRange());
	getLevel()->addObject(bullet);
}

bool Fist::collided(Object* collider)
{

	return true;
}

bool Fist::isReady()
{
	return !getAttacking();
}

void Fist::childEvent(string eventMessage)
{
	if(!mHandleChildEvent)
		mHandleChildEvent = true;
	else if(eventMessage == "displayWeapon" && mHandleChildEvent)	{
		setVisible(true);
		setAttacking(false);
		mHandleChildEvent = false;
	}
}