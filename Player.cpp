#include "Player.h"
#include "Graphics.h"
#include "DirectInput.h"
#include "Level.h"
#include "MeleeWeapon.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "Loots.h"
#include "Fist.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

Player::Player(float x, float y, int width, int height)
	: Object(x, y, width, height, "imgs\\mario.bmp")
{
	// Create the animation and set state and frame
	mAnimation = new Animation(32, 64, 0.1, 4, 4);
	mAnimation->pause();
	mAnimation->setFrame(4);

	// Load head texture
	mHeadTexture = gGraphics->loadTexture("imgs\\mario_head.bmp");
	mHeadFlipped = false;

	// Set member variables
	mAcceleration = 500.0f;
	mMaxVelocity = 330.0f;
	mFaceDirection = RIGHT;
	mHealth = 100;
	mInAir = true;
	mHeadRotation = 0.0f;
	mWeapon = NULL;

	// Set the type to PLAYER
	setType(PLAYER);

	// High friction
	getBody()->SetFriction(5.0f);

	//Fist* fist = new Fist(getPosition().x + 50, getPosition().y);	
}
	
Player::~Player()
{
	delete mAnimation;
	ReleaseCOM(mHeadTexture);
}

void Player::init()
{
	// Create and equip a Fist weapon
	/*ObjectData* data = getLevel()->loadObjectData("Fist");
	Fist* fist = new Fist(data, getPosition().x + 50, getPosition().y);
	fist->setOffset(Vector(-50, 0));
	fist->setRotationAxis(getPosition() - fist->getPosition());
	fist->setParent(this);
	fist->setCooldown(10.0f);

	mWeapon = fist;*/

	if(mWeapon != NULL)
		getLevel()->addObject(mWeapon);
}

void Player::update(float dt)
{
	// Update the animation
	mAnimation->animate(dt);

	// Update the head rotation
	updateHead();

	// Update the weapon
	if(mWeapon != NULL)	{
		mWeapon->updatePosition(getPosition());
		mWeapon->incrementCooldownCounter(dt);
	}

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
		getBody()->Move(0, -1);		// Move it out of collision (:HACK:)
		mAnimation->setFrame(4);	// Set the jumping frame
		mAnimation->pause();		// Pause the animation
		mInAir = true;				// The player is now in the air
	}

	// Shooting with the left mouse button
	if(gDInput->mouseButtonPressed(0))	{
		if(mWeapon != NULL)
			if(mWeapon->isReady())
				mWeapon->pollAttack();
	}

	// Drop the equipped weapon if the drop button was pressed
	if(gDInput->keyPressed(DIK_G))
		dropWeapon();

	// Loot
	if(gDInput->keyPressed(DIK_E))
		checkLoot();

	// Clamp velocity
	if(getVelocity().x > mMaxVelocity)
		setVelocity(mMaxVelocity, getVelocity().y);
	else if(getVelocity().x < -mMaxVelocity)
		setVelocity(-mMaxVelocity, getVelocity().y);
}
	
void Player::draw()
{
	// Draw the player with the right facing direction
	if(mFaceDirection == LEFT)	{
		gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), &mAnimation->getSourceRect(), true);
		gGraphics->drawTexture(mHeadTexture, getPosition().x, getPosition().y - 20, 32, 32, 0xffffffff, mHeadRotation, mHeadFlipped);
	}
	else	{
		gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), &mAnimation->getSourceRect(), false);
		gGraphics->drawTexture(mHeadTexture, getPosition().x, getPosition().y - 20, 32, 32, 0xffffffff, mHeadRotation, mHeadFlipped);
	}

	char buffer[256];
	sprintf(buffer, "head rotation: %f", mHeadRotation * 57.3);
	gGraphics->drawText(buffer, 10, 400);
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

void Player::checkLoot()
{
	// Calculate loot area
	Rect lootArea = getRect();
	lootArea.bottom += 20;
	lootArea.top -= 20;
	lootArea.left -= 20;
	lootArea.right += 20;

	// Find loot inside loot area
	Object* lootObject = getLevel()->findCollision(lootArea, getId(), LOOT);

	// If an object is found
	if(lootObject != NULL)
	{
		// If the object is loot
		if(lootObject->getType() == LOOT)	{
			// Cast and call equip()
			Loot* loot = dynamic_cast<Loot*>(lootObject);
			loot->equip(this);
		}
	}
}

void Player::equipWeapon(Weapon* weapon)
{
	// Remove the equipped weapon from the level (if there is any)
	if(mWeapon != NULL)
		getLevel()->removeObject(mWeapon);
	
	// Assign the new weapon to be equipped
	mWeapon = weapon;
	mWeapon->setLevel(getLevel());

	// Find out if it needs to be flipped
	if(mFaceDirection == LEFT)
		mWeapon->setFlipped(true);

	// Add the new weapon to the level
	getLevel()->addObject(mWeapon);
}

void Player::dropWeapon()
{
	// Find out if there's any weapon to drop
	if(mWeapon != NULL)
	{
		// Remove the equipped weapon from the level
		getLevel()->removeObject(mWeapon);
		mWeapon = NULL;

		// Create the new loot object
		SwordLoot* newLoot = new SwordLoot(getPosition().x, getPosition().y, 50, 50);
		newLoot->setLevel(getLevel());

		// Make it look good by a throwing effect
		if(mFaceDirection == RIGHT)	{
			newLoot->getBody()->Move(50, -50);
			newLoot->getBody()->ApplyForce(Vector(1, -1), newLoot->getPosition());
		}
		else if(mFaceDirection == LEFT)	{
			newLoot->getBody()->Move(-50, -50);
			newLoot->getBody()->ApplyForce(Vector(-1, -1), newLoot->getPosition());
		}

		// Add the loot to the level
		getLevel()->addObject(newLoot);
	}
}

void Player::damage(float damage)
{
	mHealth -= damage;
}

void Player::updateHead()
{
	// Get mouse position
	Vector mousePos = gDInput->getCursorPos();

	// Get distance to the mouse
	float dx = mousePos.x - getPosition().x;
	float dy = mousePos.y - getPosition().y - 20;

	// Point head in mouse direction - atan2 to not be limited to tans 180 degree period
	float rotation = atan2f(dy, dx);

	/*static float realRotation = 0.0f;

	if(gDInput->keyPressed(DIK_E))
		realRotation += 0.5;
	else if(gDInput->keyPressed(DIK_Q))
		realRotation -= 0.5;

	if(realRotation > 2*PI)
		realRotation -= 2*PI;
	else if(realRotation < 0)
		realRotation = 2*PI + realRotation;
	*/

	//mHeadRotation = realRotation;
	
	mHeadRotation = rotation;

	if(mHeadRotation > PI/2 || mHeadRotation < -PI/2)	{
		mHeadFlipped = true;
		mHeadRotation -= PI;
	}
	else	{
		mHeadFlipped = false;
		mHeadRotation += 2*PI;
	}
}

void Player::childEvent(string eventMessage)
{
	
}

Direction Player::getFacingDirection()
{
	return mFaceDirection;
}