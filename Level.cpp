#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Graphics.h"
#include "DirectInput.h"
#include "Enums.h"

Level::Level()
{
	// Create the physic simulation world and set important attributes
	mWorld = new World();
	mWorld->SetRotationMode(NO_ROTATION);
	mWorld->SetGravity(1000.0f);

	// Connect the callback to the function to call every time there is a collision between two bodies
	mWorld->connect(&Level::handleCollision, this);	
}
	
Level::~Level()
{
	// Delete the level
	delete mWorld;
}

void Level::update(float dt)
{
	// Update the physic simulation
	mWorld->Update(dt);

	// Loop through and update the game objects
	for(int i = 0; i < mObjectList.size(); i++)
	{
		// Update if the object is alive, else remove it from the object list
		if(mObjectList[i]->getAlive())
			mObjectList[i]->update(dt);
		else
			removeObject(mObjectList[i]);
	}

	// Temporary create object thingie
	if(gDInput->mouseButtonPressed(1))	{
		Object* object = new Object(gDInput->getCursorPos().x, gDInput->getCursorPos().y, 100, 100);
		addObject(object);
	}
}

void Level::draw()
{
	// Loop through and draw all the objects
	for(int i = 0; i < mObjectList.size(); i++)
	{
		if(mObjectList[i]->getVisible())
			mObjectList[i]->draw();
	}

	char buffer[256];
	sprintf(buffer, "objects: %i", mObjectList.size());
	gGraphics->drawText(buffer, 10, 300);
}

bool Level::handleCollision(void* objA, void* objB)
{
	Object* objectA;
	Object* objectB;

	// Cast the void pointers
	objectA = (Object*)objA;
	objectB = (Object*)objB;

	if(objectA->getType() == PLAYER || objectB->getType() == PLAYER)
		int asda = 1;

	// Find out if the collision should be added to the simulation
	if(objectA->getParent() == objectB->getParent() && objectA->getParent() != NULL)
		return false;

	// Call the collided functions
	if(objectA->collided(objectB))	// Collided return false if objectB is deleted inside the function
		objectB->collided(objectA);

	return true;
}

void Level::addObject(Object* object)
{
	// Id counter
	static int idCounter = 0;

	// Set required attributes and add to the game object list
	object->setId(idCounter);
	object->setLevel(this);

	mObjectList.push_back(object);

	// Add the objects body to the physic simulation world
	mWorld->Add(object->getBody());

	// Increment the static id counter
	idCounter++;
}

void Level::removeObject(Object* object)
{
	// Remove the objects body from the physics simulation world
	mWorld->Remove(object->getBody());

	// Find the object and remove it from the game object list
	for(int i = 0; i < mObjectList.size(); i++)
	{
		if(mObjectList[i]->getId() == object->getId())	{
			delete mObjectList[i];
			mObjectList[i] = NULL;
			mObjectList.erase(mObjectList.begin() + i);
		}
	}
}

Object* Level::findCollision(Rect rect, int id, ObjectType type)
{
	Rect objectRect = rect;
	Object* collider = NULL;

	for(int i = 0; i < mObjectList.size(); i++)	{
		if(mObjectList[i]->getId() == id)
			continue;

		Rect testRect = mObjectList[i]->getRect();

		if(objectRect.left < testRect.right && objectRect.right > testRect.left && objectRect.top < testRect.bottom && objectRect.bottom > testRect.top && mObjectList[i]->getType() == type)
			return mObjectList[i];	
	}

	return collider;
}