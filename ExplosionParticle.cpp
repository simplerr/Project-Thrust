#include "ExplosionParticle.h"
#include "Explosion.h"
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
	Explosion* explosion = dynamic_cast<Explosion*>(getParent());

	// Is the collider in the explosions exception list (has it already been affected by the explosion?)
	if(!explosion->isException(collider))
	{
		Collision collision = polyCollision(this->getBody(), collider->getBody());

		float impulse = 2.50f;
		float x = collider->getPosition().x - getParent()->getPosition().x;
		float y = collider->getPosition().y - getParent()->getPosition().y;

		// Special case when collider is a weapon, it's owners (players) position is then used instead
		if(collider->getParent() != NULL)	{
			if(collider->getParent()->getType() == PLAYER)	{
				float x = collider->getParent()->getPosition().x - getParent()->getPosition().x;
				float y = collider->getParent()->getPosition().y - getParent()->getPosition().y;
			}
		}
		
		// Angle between collider and the explosion source (parent)
		float angle = atan2f(y, x);

		// Get the force components in x and y direction
		x = cosf(angle) * impulse;
		y = sinf(angle) * impulse;

		// Make the object be properly affected by the explosion
		collider->setVelocity(Vector(0, 0));

		// Apply force (can be overridden, weapons does for example set the owners [players] force, the same with the one above)
		collider->applyForce(Vector(x, y));

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