#include "PlayState.h"
#include "Graphics.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Loots.h"
#include "Enemy.h"
#include "DirectInput.h"
#include "ObjectData.h"
#include "RangedWeapon.h"

PlayState::PlayState()
{
	// Create the level
	mLevel = new Level();

	// Load background texture
	mBkgdTexture = gGraphics->loadTexture("imgs\\bkgd.bmp");

	// Create the player and add it to the level
	mPlayer = new Player(600, 200, 32, 64);
	mLevel->addObject(mPlayer);
	mPlayer->init();

	// Create the ground
	Object* object = new Object(600, 750, 1200, 100);
	object->getBody()->SetMass(0);
	mLevel->addObject(object);

	// Temporary test object
	object = new Object(800, 600, 100, 500);
	object->getBody()->SetMass(0);
	mLevel->addObject(object);

	ObjectData* data = mLevel->loadObjectData("RetardBox");
	object = new Object(data, 200, 200);
	mLevel->addObject(object);

	ObjectData* data2 = mLevel->loadObjectData("RangedWeapon");
	RangedWeapon* weapon = new RangedWeapon(data2, 100, 100);
	mLevel->addObject(weapon);

	object = new Object(300, 300, 100, 100);
	object->setSimulate(false);
	mLevel->addObject(object);

	SwordLoot* loot = new SwordLoot(400, 300, 50, 50);
	mLevel->addObject(loot);

	SwordLoot* loot1 = new SwordLoot(600, 300, 50, 50);
	mLevel->addObject(loot1);

	FistLoot* fistLoot = new FistLoot(200, 200, 50,  50);
	mLevel->addObject(fistLoot);

	RocketLoot* rocketLoot = new RocketLoot(500, 300, 50, 50);
	mLevel->addObject(rocketLoot);

	Enemy* enemy = new Enemy(300, 200, 32, 64);
	enemy->setMaxDistance(100.0f);
	enemy->setSpeed(0);
	mLevel->addObject(enemy);
}

PlayState::~PlayState()
{
	delete mLevel;
	ReleaseCOM(mBkgdTexture);
}

void PlayState::update(float dt)
{
	// Update all the objects in the level
	mLevel->update(dt);
}
	
void PlayState::draw()
{
	// Draw the background
	gGraphics->drawTexture(mBkgdTexture, 600, 400, 1200, 800);

	// Draw all the objects in the level
	mLevel->draw();
}