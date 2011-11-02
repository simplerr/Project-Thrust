#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "DirectInput.h"

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
		mObjectList[i]->draw();
	}
}

void Level::handleCollision(void* objA, void* objB)
{
	Object* objectA;
	Object* objectB;

	// Cast the void pointers
	objectA = (Object*)objA;
	objectB = (Object*)objB;

	// Call the colide functions
	objectA->collided(objectB);
	objectB->collided(objectA);
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
			mObjectList.erase(mObjectList.begin() + i);
		}
	}
}