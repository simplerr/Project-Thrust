#include "Enemy.h"
#include "Graphics.h"
#include "Player.h"
#include "Sword.h"
#include "ParticleEmitter.h"
#include "Level.h"

Enemy::Enemy(float x, float y, int width, int height)
	: Object(x, y, width, height, "imgs\\mario.bmp")
{
	mAnimation = new Animation(32, 64, 0.1, 4, 4);

	setMaxDistance(200.0f);
	setSpeed(1.0f);
	setType(ENEMY);
	setAttackCooldown(1.0f);

	mWalkedDistance = 0.0f;
	mCooldownTimer = 0.0f;
	mHealth = 100;

	getBody()->SetFriction(10.0f);
	//getBody()->SetFriction(0.0f);
}
	
Enemy::~Enemy()
{
	delete mAnimation;
}

void Enemy::update(float dt)
{
	// Update the attack timer
	mCooldownTimer += dt;

	if(mSpeed != 0)
	{
		// Update the animation
		mAnimation->animate(dt);

		// Find out when the enemy should turn
		if(mWalkedDistance < mMaxDistance)	{
			mWalkedDistance += Mathematics::abs(mSpeed) * dt;
		
			// :NOTE: Shouldn't be here, forces the velocity which leads to ungly simulation
			// If it's not here then the friction needs to be 0
			setVelocity(mSpeed, getVelocity().y);	
		}
		else
		{
			// Change moving direction and reset the walked distance
			mSpeed *= -1;
			mWalkedDistance = 0.0f;
			setVelocity(mSpeed, getVelocity().y);
		}
	}
	else
		mAnimation->setFrame(0);

	// Kill when no life
	if(mHealth <= 0)
		kill();	// Replace with mDead = true, to draw death animation etc....
}
	
void Enemy::draw()
{
	// Draws the animation with the correct facing direction
	if(mSpeed >= 0)
		gGraphics->drawTexturedShape(*getBody()->getShape(), getTexture(), &mAnimation->getSourceRect(), false);
	else if(mSpeed < 0)
		gGraphics->drawTexturedShape(*getBody()->getShape(), getTexture(), &mAnimation->getSourceRect(), true);

	// :TODO: There should be a state for a static enemy texture
}

void Enemy::setMaxDistance(float maxDistance)
{
	mMaxDistance = maxDistance;
}
	
void Enemy::setSpeed(float speed)
{
	mSpeed = speed;
	setVelocity(mSpeed, getVelocity().y);
}

bool Enemy::collided(Object* collider)
{
	// Check if the collider is a player and that the cooldown isn't active
	if(collider->getType() == PLAYER && mCooldownTimer > mAttackCooldown)
	{
		// Cast and damage the player
		Player* player = (Player*) collider;
		player->damage(50);

		// Reset the cooldown timer
		mCooldownTimer = 0.0f;
	}
	// Check if the enemy was attacked by a player
	else if(collider->getType() == WEAPON && collider->getOwner()->getType() == PLAYER)
	{
		// Cast
		Weapon* weapon = (Weapon*) collider;

		// The weapon must be attackin to hurt the enemy
		if(weapon->getAttacking())	{
			// Deal damage to enemy
			damage(weapon->getDamage());
			
			// Add a particle blood effect
			ParticleEmitter* emitter = new ParticleEmitter(getPosition().x, getPosition().y);
			emitter->setDirection(0 -PI/2);	// :NOTE: -PI/2 to fix the angle 0 to be the right x axis
			emitter->setParticleDimensions(8, 8);
			emitter->setParticleVelocity(3.0f);
			emitter->setInterval(.005);
			emitter->setSpreadAngle(PI/4);
			emitter->setMax(20);
			emitter->setLength(50);
			emitter->setLifeTime(0.3f);
			getLevel()->addObject(emitter);
		}
	}

	return true;
}

void Enemy::setAttackCooldown(float cooldown)
{
	mAttackCooldown = cooldown;
}

void Enemy::damage(float damage)
{
	mHealth -= damage;
}