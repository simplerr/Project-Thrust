#include "RangedWeapon.h"
#include "Projectile.h"
#include "Level.h"
#include "DirectInput.h"
#include "Graphics.h"
#include "ObjectData.h"
#include "Grenade.h"

RangedWeapon::RangedWeapon(float x, float y, int width, int height, string textureSource)
	:Weapon(x, y, width, height, textureSource)
{
	// Init defaults
	setType(RANGED_WEAPON);
	setRange(200);
	setProjectile("Projectile");
}

RangedWeapon::RangedWeapon(ObjectData* data, float x, float y)
	: Weapon(data, x, y)
{
	// Get data from the XML element
	int range = data->getValueDouble("Range");
	string projectileName = data->getValueString("Projectile");

	// Set the data
	setProjectile(projectileName);
	setRange(range);
	setType(RANGED_WEAPON);
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
	float offsetX = - 10 + 70*cosf(getRotation());
	float offsetY = - 5 + 70*sinf(getRotation());
	ObjectData* data = getLevel()->loadObjectData(mProjectileName);

	Projectile* projectile;

	if(mProjectileName == "Projectile")
		projectile = new Projectile(data, getPosition().x + offsetX, getPosition().y + offsetY);
	else if(mProjectileName == "Grenade")
		projectile = new Grenade(data, getPosition().x + offsetX, getPosition().y + offsetY);

	projectile->setParent(this);
	projectile->rotate(getRotation());
	projectile->setMaxDistance(mRange);
	projectile->setSpeed(projectile->getSpeed());	// Required because the speed gets set in the ctor, when the rotation is 0

	getLevel()->addObject(projectile);
}

bool RangedWeapon::collided(Object* collider)
{
	getParent()->collided(collider);

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

void RangedWeapon::setProjectile(string name)
{
	mProjectileName = name;
}