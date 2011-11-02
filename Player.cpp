#include "Player.h"
#include "Graphics.h"
#include "DirectInput.h"
#include "Level.h"
#include "RangedWeapon.h"

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
	mWeapon = new RangedWeapon(getPosition().x + 20, getPosition().y, 64, 16, 10.0f, "imgs\\normal_gun.bmp");
	mWeapon->setOwner(this);
	mWeapon->setAllowedBounces(2);
	mWeapon->setRange(2000);
	mWeapon->setLifeTime(15.0f);
	mWeapon->getBody()->getShape()->setRotationAxis(Vector(-5, 0));
}
	
Player::~Player()
{
	delete mAnimation;
	delete mWeapon;
}

void Player::update(float dt)
{
	// Update the animation
	mAnimation->animate(dt);

	/* Update the velocity */

	// Strafing sideways
	if(gDInput->keyDown(DIK_A))	{	// Left
		setVelocity(getVelocity() + Vector(-mAcceleration, 0));	
		setFacingDirection(LEFT);

		// If the player is on the ground, continue the animation
		if(!mInAir)	
			mAnimation->resume();
	}
	else if(gDInput->keyDown(DIK_D))	{	// Right
		setVelocity(getVelocity() + Vector(mAcceleration, 0));	
		setFacingDirection(RIGHT);

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
		mWeapon->shoot();
	}

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
	mWeapon->draw();
}

void Player::collided(Object* collider)
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
}

void Player::updateWeapon()
{
	/* Rotate it pointing at the mouse position */
	mWeapon->getBody()->getShape()->resetRotation();
	// Get mouse position
	Vector mousePos = gDInput->getCursorPos();

	// Get distance to it
	float dx = mousePos.x - mWeapon->getPosition().x;
	float dy = mousePos.y - mWeapon->getPosition().y;

	// Point weapon in mouse direction - atan2 to not be limited to tans 180 degree period
	float rotation = atan2f(dy, dx);

	mWeapon->getBody()->rotate(rotation);

	/* Update the position */
	mWeapon->setPosition(getPosition().x + 20, getPosition().y);
}

void Player::setFacingDirection(Direction direction)
{
	mFaceDirection = direction;
}

void Player::setLevel(Level* level)
{
	// Important to set the weapons level, so it know where to add the projectiles
	Object::setLevel(level);
	mWeapon->setLevel(level);
}