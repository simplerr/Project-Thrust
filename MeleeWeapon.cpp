#include "MeleeWeapon.h"
#include "Graphics.h"
#include "Weapon.h"
#include "ObjectData.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

MeleeWeapon::MeleeWeapon(float x, float y, int width, int height, string textureSource)
	: Weapon(x, y, width, height, textureSource)
{
	// Init default variables
	setType(MELEE_WEAPON);
	mAttackTime = 0.15f;
	mElapsedTime = 0.0f;
}
	
MeleeWeapon::MeleeWeapon(ObjectData* data, float x, float y)
	: Weapon(data, x, y)
{
	// Get data 
	float attackTime = data->getValueDouble("AttackTime");

	mAttackTime = attackTime;
}

MeleeWeapon::~MeleeWeapon()
{

}

void MeleeWeapon::update(float dt)
{
	// :TODO: 
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
	
void MeleeWeapon::draw()
{
	gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), NULL, getFlipped());
}

bool MeleeWeapon::collided(Object* collider)
{
	// Don't do anything if the collision is with the owner :NOTE: Maybe can't be the case anymore
	if(getParent() != collider)
	{
		// Move both the sword and the owner out of collision
		Collision collision = polyCollision(collider->getBody(), this->getBody());

		// Apply impulse to the collided object
		if(collider->getBody()->GetMass() != 0.0f && getAttacking())	{
			float forceMagnitude = 1.0f;
			float angle = getRotation();

			angle -= PI/2;	// Correctment, shouldn't be needed

			// Impulse compnent calculation
			float x = cosf(angle) * forceMagnitude;
			float y = sinf(angle) * forceMagnitude;

			// Apply the impulse
			collider->getBody()->ApplyForce(Vector(x, y), collider->getPosition());
		}

		// Move the owner and the sword out of collision
		// Here only the owner gets moved, but indirectly it's both of them because the sward has the same position as the ower + offset
		// :NOTE: Not physically correct!
		getParent()->getBody()->Move(collision.pushX, collision.pushY);

		// Stop the attack
		restoreRotation();
		setAttacking(false);
	}

	return true;
}

void MeleeWeapon::attack(int attack)
{
	// Support for different attacks
	if(attack == 0)
	{
		// Reset the rotation if currently attacking
		if(getAttacking())	{
			restoreRotation();
		}

		// Start the attack
		mElapsedTime = 0.0f;
		setAttacking(true);
	}
}

void MeleeWeapon::updatePosition(Vector ownerPos)
{
	// Set the position depending on the owners (players) position, offset and if flipped is true or not
	if(getFlipped())
		setPosition(ownerPos - getOffset());
	else
		setPosition(ownerPos + getOffset());
}

void MeleeWeapon::setFlipped(bool flipped)
{
	// :NOTE: Not like this for all weapons
	if(flipped != getFlipped())
		setRotation(-getRotation());

	Weapon::setFlipped(flipped);
}