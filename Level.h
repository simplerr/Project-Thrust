#ifndef LEVEL_H
#define LEVEL_H

#include "World.h"
#include "Vector.h"

class ObjectLoader;
class Object;
class ObjectData;
class Particle;

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

	void updateParticles(float dt);
	void addParticle(Particle* particle);
	void removeParticle(Particle* particle);

	ObjectData* loadObjectData(string objectClass, string type = "Standard");
private:
	std::vector<Object*>	mObjectList;
	std::vector<Particle*>	mParticleList;
	ObjectLoader*			mObjectLoader;
	World*					mWorld;
};

#endif