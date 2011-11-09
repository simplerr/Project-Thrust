#include "Loots.h"
#include "Player.h"
#include "Enums.h"
#include "Vector.h"
#include "Graphics.h"
#include "Sword.h"

Loot::Loot(float x, float y, int width, int height, string textureSource)
	:	Object(x, y, width, height, textureSource)
{
	
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
	if(collider->getType() == PLAYER)	{
		equip((Player*)collider);
		return false;
	}

	if(collider->getOwner() != NULL)	{
		if(collider->getOwner()->getType() == PLAYER)	{
			equip((Player*)collider->getOwner());
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
	Sword* sword = new Sword(getPosition().x, getPosition().y);
	sword->setOffset(Vector(10, 0));
	sword->setRotationAxis(Vector(0, 10));
	sword->setStandardRotation(PI/5);
	sword->setOwner(player);

	// Equip the player with the sword
	player->equipWeapon(sword);

	// The loot gets removed when equiped
	kill();
}