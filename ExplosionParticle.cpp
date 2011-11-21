#include "ExplosionParticle.h"
#include "RotatingEmitter.h"
#include "Player.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

ExplosionParticle::ExplosionParticle(float x, float y, int width, int height, float speed, float angle)
	: Particle(x, y, width, height, speed, angle)
{
	setMaxDistance(200.0f);
}
	
ExplosionParticle::~ExplosionParticle()
{

}

void ExplosionParticle::update(float dt)
{
	Particle::update(dt);
}

void ExplosionParticle::draw()
{
	Particle::draw();
}

bool ExplosionParticle::collided(Object* collider)
{
	RotatingEmitter* explosion = dynamic_cast<RotatingEmitter*>(getParent());

	// Is the collider in the explosions exception list (has it already been affected by the explosion?)
	if(!explosion->isException(collider))
	{
		Collision collision = polyCollision(this->getBody(), collider->getBody());
		float impulse = 4.0f;

		float x = collider->getPosition().x - getPosition().x;
		float y = collider->getPosition().y - getPosition().y;
		float angle = atan2f(y, x);

		x = cosf(angle) * impulse;
		y = sinf(angle) * impulse;

		// :NOTE: Todo! Other weapon types must also be checked!!
		if(collider->getType() == RANGED_WEAPON)	{
			collider->getParent()->getBody()->ApplyForce(Vector(x, y), collider->getPosition());
		}
		else
			if(collider != getParent() && collider->getSimulate())
				collider->getBody()->ApplyForce(Vector(x, y), collider->getPosition());

		// Add new exception to the explosion
		explosion->addException(collider);

		// Special case if it's the player, since both the player and weapon needs to be added
		if(collider->getType() == PLAYER)	
		{
			// Collider was the player -> add it's weapon
			Player* player = dynamic_cast<Player*>(collider);
			if(player->getWeapon() != NULL)
				explosion->addException((Object*)player->getWeapon());
		}
		else if(collider->getParent() != NULL)
		{
			// Collider was players weapon -> add the player (the weapons parent)
			if(collider->getParent()->getType() == PLAYER)
				explosion->addException(collider->getParent());
		}
	}

	kill();

	return true;
}