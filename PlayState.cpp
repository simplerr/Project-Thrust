#include "PlayState.h"
#include "Graphics.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Loots.h"
#include "Enemy.h"
#include "DirectInput.h"

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

	object = new Object(300, 300, 100, 100);
	object->setSimulate(false);
	mLevel->addObject(object);

	SwordLoot* loot = new SwordLoot(400, 300, 50, 50);
	//mLevel->addObject(loot);

	SwordLoot* loot1 = new SwordLoot(600, 300, 50, 50);
	mLevel->addObject(loot1);

	Enemy* enemy = new Enemy(300, 200, 32, 64);
	enemy->setMaxDistance(100.0f);
	enemy->setSpeed(0);
	mLevel->addObject(enemy);

	mRotationPoint = Vector(600, 500);
	mPoint = Vector(600, 200);

	mTest = new Object(600, 400, 50, 50);
	mTest->setSimulate(false);
	mTest->setRotationAxis(Vector(200, -100));
	mLevel->addObject(mTest);

	mRetard = Vector(600, 400);
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

	rotationTest();

	// Testing..
	// Rotate the shape with D3DXVec4Transform
	float rotation = 0.03f;
	D3DXMATRIX rotationMatrix;
	D3DXVECTOR4 vector;
	vector.z = 0;
	vector.w = 1;
	D3DXMatrixRotationZ(&rotationMatrix, rotation);

	// For the position
	vector.x = mPoint.x - mRotationPoint.x;
	vector.y = mPoint.y - mRotationPoint.y;

	D3DXVec4Transform(&vector,  &vector, &rotationMatrix);

	//mPoint = Vector(vector.x, vector.y) + mRotationPoint;

	if(gDInput->keyPressed(DIK_G))
		mTest->getBody()->Move(50, 0);
}
	
void PlayState::draw()
{
	// Draw the background
	gGraphics->drawTexture(mBkgdTexture, 600, 400, 1200, 800);

	// Draw all the objects in the level
	mLevel->draw();

	gGraphics->drawRect(mTest->getPosition().x - mTest->getBody()->GetShape()->getRotationAxis().x, mTest->getPosition().y - mTest->getBody()->GetShape()->getRotationAxis().y, 10, 10, true, 0xff1f0aa4);
	////gGraphics->drawRect(mPoint.x, mPoint.y, 10, 10, true, D3DCOLOR_ARGB(255, 0, 255, 0));

	//gGraphics->drawRect(mTest->getPosition().x, mTest->getPosition().y, 10, 10, true, D3DCOLOR_ARGB(255, 0, 255, 0));
	//
	gGraphics->drawRect(mTest->getBody()->GetShape()->getWorldRect());

	//char buffer[256];
	//sprintf(buffer, "x: %f, y: %f", mTest->getBody()->GetShape()->axisOffset.x, mTest->getBody()->GetShape()->axisOffset.y);
	//gGraphics->drawText(buffer, 10, 500);
}

void PlayState::rotationTest()
{
	/* Rotate it pointing at the mouse position */
	Vector mousePos = gDInput->getCursorPos();

	float dx = mousePos.x - (mTest->getPosition().x - mTest->getBody()->GetShape()->getRotationAxis().x);
	float dy = mousePos.y - (mTest->getPosition().y - mTest->getBody()->GetShape()->getRotationAxis().y);
	
	// Point weapon in mouse direction - atan2 to not be limited to tans 180 degree period
	float rotation = atan2f(dy, dx) + PI/2*0;	// Hmm why PI/2?? :NOTE:

	// Just interested in the delta angle
	rotation -= mTest->getRotation();
	mRotation = rotation;

	mTest->rotate(rotation);
}