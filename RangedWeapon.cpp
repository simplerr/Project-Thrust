#include "RangedWeapon.h"
#include "Projectile.h"
#include "Level.h"
//#include "ParticleEmitter.h"
//#include "Particle.h"

RangedWeapon::RangedWeapon(float x, float y, int width, int height, float damage, string textureSource)
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

void RangedWeapon::attack(int attack)
{
	// Calculate where to spawn the projectile
	float offsetX = - 10 + 40*cosf(getRotation());
	float offsetY = - 5 + 40*sinf(getRotation());
	Projectile* bullet = new Projectile(getPosition().x + offsetX, getPosition().y + offsetY, 30, 15, "imgs\\bullet.bmp");
	
	// Set bullet properties
	bullet->setOwner(getOwner());
	bullet->getBody()->rotate(getRotation());
	bullet->setSpeed(700);
	bullet->setMaxDistance(mRange);
	bullet->setElasticity(0.8f);
	bullet->setAllowedBounces(mAllowedBounces);
	bullet->setLifeTime(mLifeTime);
	bullet->getBody()->SetMass(10000);
	getLevel()->addObject(bullet);
}