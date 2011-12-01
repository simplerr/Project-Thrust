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

	mAnimation = new KeyAnimation("animations.xml", "SwordAnimation");
	mAnimation->loadAnimation();
}
	
MeleeWeapon::MeleeWeapon(ObjectData* data, float x, float y)
	: Weapon(data, x, y)
{
	// Get data 
	float attackTime = data->getValueDouble("AttackTime");
	
	mAnimation = new KeyAnimation("animations.xml", "SwordAnimation");
	mAnimation->loadAnimation();
	setCooldown(mAnimation->getLength());
}

MeleeWeapon::~MeleeWeapon()
{

}

void MeleeWeapon::update(float dt)
{
	// If the animation is running -> get the rotation and movement
	if(mAnimation->interpolate(dt))	{
		Vector movement = mAnimation->getMovement();
		float  rotation = mAnimation->getRotation();

		// Different when flipped and not
		if(!getFlipped())	{
			rotate(rotation - getRotation());
			getBody()->Move(movement);
			setOffset(getOffset() + movement);	
		}
		else	{
			rotate(-rotation - getRotation());
			getBody()->Move(Vector(movement.x, -movement.y));			// :NOTE No idea why it should move with inversed Y and not X, maybe has to do with the rotation
			setOffset(getOffset() + Vector(movement.x, -movement.y));	
		}
		
	}
	else	{
		if(getRotation() != getStandardRotation())
			setRotation(getStandardRotation());	 // :NOTE: Sloppy
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
		//restoreRotation();
		setAttacking(false);
	}

	return true;
}

void MeleeWeapon::attack(int attack)
{
	// Start the attack animation
	mAnimation->start();
}

void MeleeWeapon::updatePosition(Vector ownerPos)
{
	// Set the position depending on the owners (players) position, offset and if flipped is true or not
	if(getFlipped())
		setPosition(ownerPos - Vector(getOffset().x, 0));	// :TODO: Y offset shouldn't be 0
	else
		setPosition(ownerPos + Vector(getOffset().x, 0));
}

void MeleeWeapon::setFlipped(bool flipped)
{
	// :NOTE: Not like this for all weapons
	if(flipped != getFlipped())
		setRotation(-getRotation());

	Weapon::setFlipped(flipped);
}