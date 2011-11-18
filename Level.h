#ifndef LEVEL_H
#define LEVEL_H

#include "World.h"
#include "Vector.h"

class ObjectLoader;
class Object;
class ObjectData;

class Level
{
public:
	Level();
	~Level();

	void update(float dt);
	void draw();

	bool handleCollision(void* objA, void* objB);
	Object* findCollision(Rect rect, int id, ObjectType type);

	void addObject(Object* object);
	void removeObject(Object* object);

	void checkRectCollisions();

	ObjectData* loadObjectData(string objectName);
private:
	std::vector<Object*>	mObjectList;
	ObjectLoader*			mObjectLoader;
	World*					mWorld;
};

#endif