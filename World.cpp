#include "World.h"
#include "DirectInput.h"
#include "Graphics.h"
#include "RigidBody.h"
#include "Shape.h"
#include "Arbiter.h"
#include <limits>
#include <fstream>

using std::vector;
using std::map;
using std::pair;

typedef map<ArbiterKey, Arbiter>::iterator ArbIter;
typedef pair<ArbiterKey, Arbiter> ArbPair;
extern std::ofstream fout;

bool PointInsideShape(Vector point, Shape* shape);

World::World() : SMALL_NEGATIVE(-1E-10), SMALL_POSITIVE(1E-10)
{
	mCollisionPoint = Vector(500, 500,0 );
	SetGravity(500.0f);
	Unpause();
	SetRotationMode(ROTATION);
}
	
World::~World()
{
	for(int i = 0; i < mBodyList.size(); i++)
	{
		Remove(mBodyList[i]);
	}
}

void World::SetGravity(float gravity)
{
	GRAVITY = gravity;
}

void World::BroadPhase()
{
	for(int i = 0; i < mBodyList.size(); i++)
	{
		RigidBody* bi = mBodyList[i];

		for(int j = i + 1; j < mBodyList.size(); j++)
		{
			RigidBody* bj = mBodyList[j];

			Arbiter		newArb(bi, bj);
			ArbiterKey	key(bi, bj);

			// Check if there's any collision between the bodies
			if((int)newArb.contactList.size() > 0)	{
				// Don't add a collision if one of the objects isn't collidable
				if(!newArb.bodyA->GetCollidable() || !newArb.bodyB->GetCollidable())
					continue;
				// or if the callback function returns false
				if(!callback(newArb.bodyA->GetOwner(), newArb.bodyB->GetOwner()))
					continue;
				// or if one of the bodies isn't suppose to be simulated
				if(!newArb.bodyA->GetSimulate() || !newArb.bodyB->GetSimulate())
					continue;
			}
			
			// Same as above - this to make it easier
			if((int)newArb.contactList.size() > 0)
			{			
				ArbIter iter = arbiters.find(key);

				// If the arbiter doesn't exist in the list we just add it
				if(iter == arbiters.end())
					arbiters.insert(ArbPair(key, newArb));
				else	{
					// The arbiter already existed so we update it (iter->second is the mapped value, iter->first is the key value)
					iter->second.Update(newArb.contactList);
				}
			}
			else	{
				// If there's no contact between the bodies then the arbiter gets removed
				ArbIter iter = arbiters.find(key);
				if(iter != arbiters.end())
					arbiters.erase(key);
			}
		}
	}
}

void World::Step(float dt)
{
	if(!GetPaused())	// The world is not paused
	{
		// Determine overlapping bodies and update contact points
		BroadPhase();

		// Integrate forces
		for(int i = 0; i < mBodyList.size(); i++)
		{
			RigidBody* b = mBodyList[i];

			if(b->GetMass() != 0)	
			{
				if(b->GetSimulate())
					b->SetVelocity(b->GetVelocity() + dt * (Vector(0, GRAVITY, 0) + (b->GetInvMass()) * b->GetForce() * 10000));
				else
					b->SetVelocity(b->GetVelocity() + b->GetInvMass() * b->GetForce() * 10000);

				b->SetAngularVelocity(b->GetAngularVelocity() + dt * (b->GetInvInertia()) * b->GetTorque() * 1000);
			}
		}

		// Perform pre-steps
		for(ArbIter arb = arbiters.begin(); arb != arbiters.end(); arb++)
		{
			if(arb->second.active)	{
				arb->second.PreStep(1/dt);
			}
		}

		// Perform iterations
		// :TODO: fix iteration variable
		for(int i = 0; i < 50; i++)
		{
			for(ArbIter arb = arbiters.begin(); arb != arbiters.end(); arb++)
			{
				if(arb->second.active)
					arb->second.ApplyImpulse();
			}
		}

		// Integrate velocities
		for(int i = 0; i < mBodyList.size(); i++)
		{
			RigidBody* b = mBodyList[i];

			if(b->GetMass() != 0)	
			{
				b->SetPosition(b->GetPosition() + dt * b->GetVelocity());
				b->Rotate(dt * b->GetAngularVelocity());
				b->SetTorque(0);
				b->SetForce(Vector(0, 0));
			}
		}
	}
	else if(GetPaused())	// The world is paused - no simulation
	{

	}
}

// Here DirectInput is setup
void World::Init()
{
	
}

void World::Update(float dt)	// step() or evaluate()
{
	Step(dt);
}

void World::Load(string source)
{

}
	
void World::Save(string source)
{

}

void World::Add(RigidBody* body)
{
	if(!mRotationMode)
		body->SetInertia(0.0f);

	mBodyList.push_back(body);
}
	
void World::Remove(RigidBody* body)
{
	for(int i = 0; i < mBodyList.size(); i++)
	{
		if(mBodyList[i]->GetId() == body->GetId())	{
			// Find arbiters containing the deleted body
			int d = 0;
			for(ArbIter arb = arbiters.begin(); arb != arbiters.end(); arb++, d++)
			{
				if(arb->second.bodyA->GetId() == body->GetId() || arb->second.bodyB->GetId() == body->GetId())	{
					// :NOTE: Hack solution, should be removed from the arbiter list instead!
					arb->second.active = false;
				}
			}
			mBodyList.erase(mBodyList.begin() + i);
		}
	}
}	

RigidBody* World::GetBody(Vector mousePos)
{
	for(int i = 0; i < mBodyList.size(); i++)
	{
		if(PointInsideShape(gDInput->getCursorPos(), mBodyList[i]->GetShape()))
		{						
			return mBodyList[i];
		}
	}

	return NULL;
}

void World::Pause()
{
	// :NOTE: Maybe you want to reset these values
	/*for(int i = 0; i < mBodyList.size(); i++)
	{
		mBodyList[i]->SetVelocity(0, 0);
		mBodyList[i]->SetForce(Vector(0, 0));
		mBodyList[i]->SetTorque(0);
	}*/

	mPaused = true;
}
	
void World::Unpause()
{
	mPaused = false;
}
	
bool World::GetPaused()
{
	return mPaused;
}

void World::SetRotationMode(RotationMode mode)
{
	mRotationMode = mode;
}

RotationMode World::GetRotationMode()
{
	return mRotationMode;
}

void World::ClearWorld()
{
	// :TODO:
	/*std::list<RigidBody*>::iterator iter = mBodyList.begin();
	while(iter != mBodyList.end())
	{
		delete (*iter);
		iter++;
	}
	
	mBodyList.clear();*/
}