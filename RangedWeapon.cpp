#include "RangedWeapon.h"
#include "Projectile.h"
#include "Level.h"
#include "DirectInput.h"
#include "Graphics.h"
//#include "ParticleEmitter.h"
//#include "Particle.h"

RangedWeapon::RangedWeapon(float x, float y, int width, int height, string textureSource)
	:Weapon(x, y, width, height, textureSource)
{
	setAllowedBounces(0);
	setType(RANGED_WEAPON);
	setRange(200);
	setLifeTime(5.0f);
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
	
	mRotation = rotation;

	// Get the delta rotation


	rotate(rotation - getRotation());

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
	
}

void RangedWeapon::attack(int attack)
{
	// Calculate where to spawn the projectile
	float offsetX = - 10 + 40*cosf(getRotation());
	float offsetY = - 5 + 40*sinf(getRotation());
	Projectile* bullet = new Projectile(getPosition().x + offsetX, getPosition().y + offsetY, 30, 15, "imgs\\bullet.bmp");
	
	// Set bullet properties
	bullet->setParent(getParent());
	bullet->getBody()->Rotate(getRotation());
	bullet->setSpeed(700);
	bullet->setMaxDistance(mRange);
	bullet->setElasticity(0.8f);
	bullet->setAllowedBounces(mAllowedBounces);
	bullet->setLifeTime(mLifeTime);
	bullet->getBody()->SetMass(10000);
	getLevel()->addObject(bullet);
}