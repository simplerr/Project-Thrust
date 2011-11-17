#include "Loots.h"
#include "Player.h"
#include "Enums.h"
#include "Vector.h"
#include "Graphics.h"
#include "MeleeWeapon.h"
#include "Fist.h"

Loot::Loot(float x, float y, int width, int height, string textureSource)
	:	Object(x, y, width, height, textureSource)
{
	setType(LOOT);
}
	
Loot::~Loot()
{
	
}

void Loot::update(float dt)
{

}

void Loot::draw()
{
	Object::draw();
}

void Loot::equip(Player* player)
{

}

bool Loot::collided(Object* collider)
{
	// If the collider is a player we let it equip the loot
	if(collider->getType() == PLAYER)	{
		//equip((Player*)collider);	// Cast to player
		return false;	// To show that this object was deleted with in this function
	}

	// If the colliders owner is a player we let it equip the loot as well, for instance when the players sword hits the loot and not the player itself
	if(collider->getParent() != NULL)	{
		if(collider->getParent()->getType() == PLAYER)	{
		//	equip((Player*)collider->getOwner());
			return false;
		}
	}
}

SwordLoot::SwordLoot(float x, float y, int width, int height)
	:	Loot(x, y, width, height, "imgs\\sword_loot.bmp")
{

}
	
SwordLoot::~SwordLoot()
{

}

void SwordLoot::equip(Player* player)
{
	// Create the sword
	MeleeWeapon* sword = new MeleeWeapon(getPosition().x, getPosition().y, 15, 53, "imgs\\sword.bmp");
	sword->setOffset(Vector(10, 0));
	sword->setRotationAxis(Vector(0, 10));
	sword->setStandardRotation(PI/5);
	sword->setParent(player);
	sword->setDamage(0);

	// Equip the player with the sword
	player->equipWeapon(sword);

	// Remove the loot from the level
	kill();
}

FistLoot::FistLoot(float x, float y, int width, int height)
	:	Loot(x, y, width, height, "imgs\\fist_loot.bmp")
{

}
	
FistLoot::~FistLoot()
{

}

void FistLoot::equip(Player* player)
{
	// Create the sword
	Fist* fist = new Fist(getPosition().x + 50, getPosition().y);
	fist->setOffset(Vector(-50, 0));
	fist->setRotationAxis(getPosition() - fist->getPosition());
	fist->setParent(player);

	// Equip the player with the sword
	player->equipWeapon(fist);

	// Remove the loot from the level
	kill();
}

RocketLoot::RocketLoot(float x, float y, int width, int height)
	:	Loot(x, y, width, height, "imgs\\rocket_loot.bmp")
{

}
	
RocketLoot::~RocketLoot()
{

}

void RocketLoot::equip(Player* player)
{
	// Create the rocket
	RangedWeapon* weapon = new RangedWeapon(getPosition().x + 20, getPosition().y, 64, 16, "imgs\\normal_gun.bmp");
	weapon->setParent(this);
	weapon->setVisible(true);
	weapon->setAllowedBounces(3);
	weapon->setRange(2000);
	weapon->setLifeTime(15.0f);
	weapon->getBody()->GetShape()->setRotationAxis(Vector(-5, 0));

	// Equip the player with the sword
	player->equipWeapon(weapon);

	// Remove the loot from the level
	kill();
}