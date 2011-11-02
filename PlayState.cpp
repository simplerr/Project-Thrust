#include "PlayState.h"
#include "Graphics.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"

PlayState::PlayState()
{
	// Create the level
	mLevel = new Level();

	// Load background texture
	mBkgdTexture = gGraphics->loadTexture("imgs\\bkgd.bmp");

	// Create the player and add it to the level
	mPlayer = new Player(600, 200, 32, 64);
	mLevel->addObject(mPlayer);

	// Create the ground
	Object* object = new Object(600, 750, 1200, 100);
	object->getBody()->SetMass(0);
	mLevel->addObject(object);

	// Temporary test object
	object = new Object(800, 600, 100, 500);
	object->getBody()->SetMass(0);
	mLevel->addObject(object);
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