#include "Player.h"
#include "Graphics.h"
#include "DirectInput.h"
#include "Level.h"
#include "Sword.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "Loots.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

Player::Player(float x, float y, int width, int height)
	: Object(x, y, width, height, "imgs\\mario.bmp")
{
	// Create the animation and set state and frame
	mAnimation = new Animation(32, 64, 0.1, 4, 4);
	mAnimation->pause();
	mAnimation->setFrame(4);

	// Set member variables
	mAcceleration = 500.0f;
	mMaxVelocity = 330.0f;
	mFaceDirection = RIGHT;
	mInAir = true;
	
	// Set the type to PLAYER
	setType(PLAYER);

	// High friction
	getBody()->SetFriction(5.0f);

	// Create and set the weapon attributes, the weapon will use this information when it creates projectiles
	/*mWeapon = new RangedWeapon(getPosition().x + 20, getPosition().y, 64, 16, 10.0f, "imgs\\normal_gun.bmp");
	mWeapon->setOwner(this);
	mWeapon->setAllowedBounces(2);
	mWeapon->setRange(2000);
	mWeapon->setLifeTime(15.0f);
	mWeapon->getBody()->getShape()->setRotationAxis(Vector(-5, 0));*/

	/*mWeapon = new Sword(getPosition().x, getPosition().y);
	mWeapon->setOffset(Vector(10, 0));
	mWeapon->setRotationAxis(Vector(0, 10));
	mWeapon->setStandardRotation(PI/5);
	mWeapon->setOwner(this);*/

	mWeapon = NULL;
}
	
Player::~Player()
{
	delete mAnimation;
}

void Player::update(float dt)
{
	// Update the animation
	mAnimation->animate(dt);

	// Update the weapon
	if(mWeapon != NULL)
		mWeapon->update(dt);

	/* Update the velocity */

	// Strafing sideways
	if(gDInput->keyDown(DIK_A))	{	// Left
		setVelocity(getVelocity() + Vector(-mAcceleration, 0));	
		setFacingDirection(LEFT);

		if(mWeapon != NULL)
			mWeapon->setFlipped(true);

		// If the player is on the ground, continue the animation
		if(!mInAir)	
			mAnimation->resume();
	}
	else if(gDInput->keyDown(DIK_D))	{	// Right
		setVelocity(getVelocity() + Vector(mAcceleration, 0));	
		setFacingDirection(RIGHT);

		if(mWeapon != NULL)
			mWeapon->setFlipped(false);

		// If the player is on the ground, continue the animation
		if(!mInAir)	
			mAnimation->resume();
	}
	
	// If A or D is released set the frame to 0 if the player not is in the air
	if(gDInput->keyReleased(DIK_A) || gDInput->keyReleased(DIK_D))	{
		mAnimation->pause();

		if(!mInAir)
			mAnimation->setFrame(0);
	}

	// Jump if the player is on the ground
	if(gDInput->keyDown(DIK_SPACE) && !mInAir)	{
		setVelocity(getVelocity() + Vector(0, -500));
		getBody()->move(0, -1);		// Move it out of collision (:HACK:)
		mAnimation->setFrame(4);	// Set the jumping frame
		mAnimation->pause();		// Pause the animation
		mInAir = true;				// The player is now in the air
	}

	// Shooting with the left mouse button
	if(gDInput->mouseButtonPressed(0))	{
		if(mWeapon != NULL)
			mWeapon->attack();
	}

	if(gDInput->keyPressed(DIK_G))
		dropWeapon();

	// Update the weapon position and rotation
	updateWeapon();

	// Clamp velocity
	if(getVelocity().x > mMaxVelocity)
		setVelocity(mMaxVelocity, getVelocity().y);
	else if(getVelocity().x < -mMaxVelocity)
		setVelocity(-mMaxVelocity, getVelocity().y);
}
	
void Player::draw()
{
	// Draw the player with the right facing direction
	if(mFaceDirection == LEFT)
		gGraphics->drawTexturedShape(*getBody()->getShape(), getTexture(), &mAnimation->getSourceRect(), true); 
	else
		gGraphics->drawTexturedShape(*getBody()->getShape(), getTexture(), &mAnimation->getSourceRect(), false);
	
	// Draw the weapon
	if(mWeapon != NULL)
		mWeapon->draw();
}

bool Player::collided(Object* collider)
{
	// Grab information about the collision :NOTE: Could be done in a better way, ie collided has that information as a parameter
	Collision collision = polyCollision(collider->getBody(), this->getBody());

	// True if the player is on the ground
	// Needs to check the y velocity because the objects can still be inside each other, but on their way of separating, might take 2-4 frames for them to be 100% separated
	if(collision.pushY < 0 && getVelocity().y > 0)	{
		if(mInAir)	{
  			mInAir = false;
			mAnimation->setFrame(0);
		}
	}

	return true;
}

void Player::updateWeapon()
{
	/* Rotate it pointing at the mouse position */
	//mWeapon->getBody()->getShape()->resetRotation();
	// Get mouse position
	//Vector mousePos = gDInput->getCursorPos();

	// Get distance to it
	//float dx = mousePos.x - mWeapon->getPosition().x;
	//float dy = mousePos.y - mWeapon->getPosition().y;

	// Point weapon in mouse direction - atan2 to not be limited to tans 180 degree period
	//float rotation = atan2f(dy, dx);

	//mWeapon->rotate(rotation);

	/* Update the position 
		- The position of the weapon is allways the same as the player + the offset asigned
	*/
	if(mWeapon != NULL)
		mWeapon->updatePosition(getPosition());
}

void Player::setFacingDirection(Direction direction)
{
	mFaceDirection = direction;
}

void Player::setLevel(Level* level)
{
	// Important to set the weapons level, so it know where to add the projectiles
	Object::setLevel(level);
	if(mWeapon != NULL)
		mWeapon->setLevel(level);
}

void Player::setVelocity(Vector velocity)
{
	Object::setVelocity(velocity);

	// Set the weapons velocity so it works correctly when collididing with bodies
	if(mWeapon != NULL)
		mWeapon->setVelocity(velocity);
}

void Player::setVelocity(float dx, float dy)
{
	setVelocity(Vector(dx, dy));
}

void Player::equipWeapon(Weapon* weapon)
{
	if(mWeapon != NULL)
		getLevel()->removeObject(mWeapon);
	
	mWeapon = weapon;
	mWeapon->setLevel(getLevel());

	if(mFaceDirection == LEFT)
		mWeapon->setFlipped(true);

	getLevel()->addObject(mWeapon);
}

void Player::dropWeapon()
{
	if(mWeapon != NULL)
	{
		// Remove the equipped weapon from the level
		getLevel()->removeObject(mWeapon);
		mWeapon = NULL;

		SwordLoot* newLoot = new SwordLoot(getPosition().x, getPosition().y, 50, 50);
		newLoot->setLevel(getLevel());
		if(mFaceDirection == RIGHT)	{
			newLoot->getBody()->move(50, -50);
			newLoot->getBody()->ApplyForce(Vector(1, -1), newLoot->getPosition());
		}
		else if(mFaceDirection == LEFT)	{
			newLoot->getBody()->move(-50, -50);
			newLoot->getBody()->ApplyForce(Vector(-1, -1), newLoot->getPosition());
		}

		getLevel()->addObject(newLoot);
	}
}