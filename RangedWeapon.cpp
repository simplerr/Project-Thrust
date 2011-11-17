#include "RangedWeapon.h"
#include "Projectile.h"
#include "Level.h"
#include "DirectInput.h"
#include "Graphics.h"
#include "ObjectData.h"

RangedWeapon::RangedWeapon(float x, float y, int width, int height, string textureSource)
	:Weapon(x, y, width, height, textureSource)
{
	// Init defaults
	setAllowedBounces(0);
	setType(RANGED_WEAPON);
	setRange(200);
	setLifeTime(5.0f);
}

RangedWeapon::RangedWeapon(ObjectData* data, float x, float y)
	: Weapon(data, x, y)
{
	// Get data from the XML element
	int bounces = data->getValueDouble("Bounces");
	int range = data->getValueDouble("Range");
	float lifeTime = data->getValueDouble("Lifetime");

	// Set the data
	setAllowedBounces(bounces);
	setRange(range);
	setLifeTime(lifeTime);
}

RangedWeapon::~RangedWeapon()
{

}

void RangedWeapon::update(float dt)
{
	/* Rotate it pointing at the mouse position */
	getBody()->GetShape()->resetRotation();

	// Get mouse position
	Vector mousePos = gDInput->getCursorPos();
	
	// Get distance to weapons rotation axis
	float dx = mousePos.x - (getPosition().x - getBody()->GetShape()->getRotationAxis().x);
	float dy = mousePos.y - (getPosition().y - getBody()->GetShape()->getRotationAxis().y);
	
	// Point weapon in mouse direction - atan2 to not be limited to tans 180 degree period
	float rotation = atan2f(dy, dx);
	

	// Get the delta rotation
	rotate(rotation - getRotation());

	incrementCooldownCounter(dt);

	/*if(!getFlipped())	{
		if(rotation > -PI/2 && rotation < PI/2)
			rotate(rotation - getRotation());
		else if(rotation < -PI/2)
			rotate(getRotation() - PI/2);
		else if(rotation > PI/2)
			rotate(getRotation() + PI/2);
	}*/
	/*else	{
		if(rotation < -PI/2 || rotation > PI/2)
			rotate(rotation - getRotation());
		else if(rotation > -PI/2)
			rotate(getRotation() - PI/2);
		else if(rotation < PI/2)
			rotate(getRotation() + PI/2);
	}*/
}

void RangedWeapon::draw()
{
	gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), NULL, false);
}

void RangedWeapon::attack(int attack)
{
	// Calculate where to spawn the projectile
	float offsetX = - 10 + 50*cosf(getRotation());
	float offsetY = - 5 + 50*sinf(getRotation());
	Projectile* bullet = new Projectile(getPosition().x + offsetX, getPosition().y + offsetY, 30, 15, "imgs\\bullet.bmp");
	
	// Set bullet properties
	bullet->setParent(this);	//getParent()
	bullet->getBody()->Rotate(getRotation());
	bullet->setSpeed(700);
	bullet->setMaxDistance(mRange);
	bullet->setElasticity(0.8f);
	bullet->setAllowedBounces(mAllowedBounces);
	bullet->setLifeTime(mLifeTime);
	bullet->getBody()->SetMass(10000);
	getLevel()->addObject(bullet);
}

bool RangedWeapon::collided(Object* collider)
{
	return true;
}

void RangedWeapon::updatePosition(Vector ownerPos)
{
	// Set position at the owners + rotationAxis
	setPosition(ownerPos + getBody()->GetShape()->getRotationAxis());
}

void RangedWeapon::setFlipped(bool flipped)
{
	Weapon::setFlipped(flipped);
}