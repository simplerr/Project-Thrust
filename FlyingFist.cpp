#include "FlyingFist.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

FlyingFist::FlyingFist(float x, float y, int width, int height)
	: Projectile(x, y, width, height, "imgs\\fist.bmp")
{
	mTurned = false;
}

FlyingFist::~FlyingFist()
{

}

void FlyingFist::update(float dt)
{
	// Update the travelled distance
	updateTravelled(dt);

	// Find out if it should change direction
	if(getTravelled() > getMaxDistance() && !mTurned)	
	{
		setVelocity(-getVelocity());
		mTurned = true;
	}

	// Kill and display the parent weapon after a certain distance travelled
	if(getTravelled() > getMaxDistance()*2 && mTurned)
	{
		kill();
		// :TODO: Fix if the parent dissapears
		if(getParent() != NULL)
			getParent()->childEvent("displayWeapon");
	}
}

bool FlyingFist::collided(Object* collider)
{
	// Kill if collides with Fist weapon on it's way back to it
	if(mTurned && collider == getParent())	{
		kill();
		getParent()->childEvent("displayWeapon");
	}

	// Change velocity
	if(!mTurned)	{
		setVelocity(-getVelocity());
		mTurned = true;
		setTravelledDistance(getMaxDistance());
	}

	// Get information about the collision
	Collision collision = polyCollision(getBody(), collider->getBody());
	
	// Apply impulse to collider
	if(collider != getParent() && collider->getSimulate())
		collider->getBody()->ApplyForce(Vector(collision.normal.x * 2.5, collision.normal.y * 2.5), collider->getPosition());

	return true;
}