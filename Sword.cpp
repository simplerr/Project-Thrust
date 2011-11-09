#include "Sword.h"
#include "Graphics.h"
#include "Weapon.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

Sword::Sword(float x, float y)
	: Weapon(x, y, 15, 53, "imgs\\sword.bmp")
{
	mAttackTime = 0.15f;
	mElapsedTime = 0.0f;
}
	
Sword::~Sword()
{

}

void Sword::update(float dt)
{
	if(getAttacking() && mElapsedTime < mAttackTime)
	{
		if(!getFlipped())
			rotate(PI/18);
		else
			rotate(-PI/18);

		mElapsedTime += dt;
	}
	else if(mElapsedTime > mAttackTime)	
	{
		// Restore the rotation and position
		restoreRotation();

		setAttacking(false);
	}
}
	
void Sword::draw()
{
	gGraphics->drawTexturedShape(*getBody()->getShape(), getTexture(), NULL, getFlipped());
}

bool Sword::collided(Object* collider)
{
	if(getOwner() != collider)
	{
		// Move both the sword and the owner out of collision
		Collision collision = polyCollision(collider->getBody(), this->getBody());

		// Apply impulse to the collided object
		if(collider->getBody()->GetMass() != 0.0f && getAttacking())	{
			float forceMagnitude = 5.0f;
			float angle = getRotation();

			//if(angle < 0.0f)
			//	angle = PI - angle;
			angle -= PI/2;

			float x = cosf(angle) * forceMagnitude;
			float y = sinf(angle) * forceMagnitude;

			collider->getBody()->ApplyForce(Vector(x, y), collider->getPosition());
		}

		// Move the owner and the sword out of collision
		// Here only the owner gets moved, but indirectly it's both of them because the sward has the same position as the ower + offset
		// :NOTE: Not physically correct!
		getOwner()->getBody()->move(collision.pushX, collision.pushY);

		// Stop the attack
		restoreRotation();
		setAttacking(false);
	}

	return true;
}

void Sword::attack(int attack)
{
	// Support for different attacks
	if(attack == 0)
	{
		// Currently attacking
		if(getAttacking())	{
			restoreRotation();
		}

		mElapsedTime = 0.0f;
		setAttacking(true);
	}
}