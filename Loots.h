#ifndef LOOT_H
#define LOOT_H

#include <string>
#include "d3dUtil.h"
#include "Object.h"
using namespace std;

class Player;
class Rect;
class Vector;

class Loot : public Object
{
public:
	Loot(float x, float y, int width, int height, string textureSource);
	~Loot();

	virtual void update(float dt);
	virtual void draw();

	virtual void equip(Player* player);		// Gets called within the collided function

	bool collided(Object* collider);
private:
};

class SwordLoot : public Loot
{
public:
	SwordLoot(float x, float y, int width, int height);
	~SwordLoot();

	void equip(Player* player);
private:
};

#endif