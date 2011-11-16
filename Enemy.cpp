#include "Enemy.h"
#include "Graphics.h"
#include "Player.h"
#include "MeleeWeapon.h"
#include "ParticleEmitter.h"
#include "Level.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

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

	mBloodEffect = NULL;
}
	
Enemy::~Enemy()
{
	delete mAnimation;
}

void Enemy::update(float dt)
{
	// If there is an active blood effect set it's origin to the enemies + offset
	if(mBloodEffect != NULL)	{
		if(mBloodEffect->effectEnded())
			mBloodEffect = NULL;
		else
			mBloodEffect->setPosition(getPosition() + mEffectOffset);
	}

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
	if(mHealth <= 0)	{
		kill();	// Replace with mDead = true, to draw death animation etc....
		//mBloodEffect->kill();	// Maybe shouldn't be here :NOTE:
	}
}
	
void Enemy::draw()
{
	// Draws the animation with the correct facing direction
	if(mSpeed >= 0)
		gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), &mAnimation->getSourceRect(), false);
	else if(mSpeed < 0)
		gGraphics->drawTexturedShape(*getBody()->GetShape(), getTexture(), &mAnimation->getSourceRect(), true);

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
	else if(collider->getType() == MELEE_WEAPON && collider->getParent()->getType() == PLAYER)
	{
		// Cast
		Weapon* weapon = (Weapon*) collider;

		// The weapon must be attackin to hurt the enemy
		if(weapon->getAttacking())	{
			// Deal damage to enemy
			damage(weapon->getDamage());
			
			// Get collision information
			Collision collision = polyCollision(getBody(), collider->getBody());
			Vector effectPos = collision.contactList[0].pos;
			Vector effectOffset = effectPos - getPosition();
			
			setEffectOffset(effectOffset);

			// Add a particle blood effect
			mBloodEffect = new ParticleEmitter(effectPos.x, effectPos.y);
			mBloodEffect->setDirection(atan2f(-collision.normal.y, -collision.normal.y));	// :NOTE: -PI/2 to fix the angle 0 to be the right x axis
			mBloodEffect->setParticleDimensions(6, 6);
			mBloodEffect->setParticleVelocity(1.5f);
			mBloodEffect->setInterval(.002);
			mBloodEffect->setSpreadAngle(PI/4);
			mBloodEffect->setMax(50);
			mBloodEffect->setLength(50);
			mBloodEffect->setLifeTime(0.3f);
			getLevel()->addObject(mBloodEffect);
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

void Enemy::setEffectOffset(Vector offset)
{
	mEffectOffset = offset;
}