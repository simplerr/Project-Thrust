#ifndef LEVEL_H
#define LEVEL_H

#include "World.h"
#include "Vector.h"

class Object;

class Level
{
public:
	Level();
	~Level();

	void update(float dt);
	void draw();

	void handleCollision(void* objA, void* objB);
	Object* findCollision(Rect rect, int id, ObjectType type);

	void addObject(Object* object);
	void removeObject(Object* object);
private:
	World* mWorld;
	std::vector<Object*> mObjectList;
};

#endif