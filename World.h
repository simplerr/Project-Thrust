#ifndef World_H
#define World_H

#include <list>
#include <map>
#include <boost\function.hpp>
#include <boost\bind.hpp>
#include "Enums.h"
#include "Shape.h"

enum GetType
{
	RIGHT_PRESSED,
	LEFT_PRESSED,
	INSIDE
};

enum RotationMode
{
	NO_ROTATION,
	ROTATION
};

class RigidBody;
class Arbiter;
class ArbiterKey;

class World
{
public:
	World();
	~World();

	void Init();	
	void Update(float dt);
	void Step(float dt);
	void Draw();
	void BroadPhase();
	void SetGravity(float gravity);

	void Add(RigidBody* body);
	void Remove(RigidBody* body);

	void Load(string source);
	void Save(string source);
	void ClearWorld();

	RigidBody* GetBody(Vector mousePos);

	void Pause();
	void Unpause();
	bool GetPaused();

	void SetRotationMode(RotationMode mode);
	RotationMode GetRotationMode();

	// Gets called when a collision occurs
	boost::function<void(void* objA, void* objB)> callback;

	template <class T>
	void connect(void(T::*_callback)(void* objA, void* objB), T* _object)	{
		callback = boost::bind(_callback, _object, _1, _2);
	}

private:
	std::vector<RigidBody*> mBodyList;
	std::map<ArbiterKey, Arbiter> arbiters;
	Vector mNormal;
	Vector mCollisionPoint;

	float GRAVITY;

	const double SMALL_NEGATIVE;
	const double SMALL_POSITIVE;

	bool mPaused;
	RotationMode mRotationMode;
};

#endif