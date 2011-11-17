#include "Projectile.h"

Collision polyCollision(RigidBody* bodyA, RigidBody* bodyB);

Projectile::Projectile(float x, float y, int width, int height, string textureSource)
	: Object(x, y, width, height, textureSource)
{
	mTravelled = 0.0f;
	setMaxDistance(300.0f);
	setDamage(10.0f);
	setLifeTime(4.0f);
	setAllowedBounces(0);
	setType(PROJECTILE);
	mBounces = 0;
}
	
Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
	// Kill if bounced more than allowed
	if(mBounces >= mAllowedBounces)
		kill();
	else
	{
		if(mTravelled < mMaxDistance)	
		{
			// Inverse counting of the life timer
			mLifeTimer -= dt;

			// Kill if it's lived longer than allowed
			if(mLifeTimer < 0)
				kill();

			updateTravelled(dt);

			// Rotate
			Vector velocity = getVelocity();
			getBody()->GetShape()->resetRotation();
			getBody()->Rotate(atan2f(velocity.y, velocity.x));
		}
		else
			kill();
	}
}
	
void Projectile::updateTravelled(float dt)
{
	// Increment travelled distance
	Vector velocity = getVelocity();
	mTravelled += dt * Mathematics::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
}

bool Projectile::collided(Object* collider)
{
	// Get information about the collision
	Collision collision = polyCollision(getBody(), collider->getBody());

	// Apply a force to the collider 
	// :TODO: should depend on the speed and projectile type!!
	float impulse = 2.5;

	if(collider != getParent() && collider->getSimulate())
		collider->getBody()->ApplyForce(Vector(collision.normal.x * impulse, collision.normal.y * impulse), collider->getPosition());

	if(mElasticity)
	{
		if((collider == getParent() && mTravelled > 30) || collider != getParent())
		{
			// Bounce counting
			mBounces++;

			// Move the projectile out of collision
			getBody()->Move(-collision.pushX, -collision.pushY);

			// Kinda hacky code, dont remember the meaning of everything
			float incomingAngle = atan2f(getVelocity().y, getVelocity().x);
			float normalAngle = -atan2f(collision.normal.x, -collision.normal.y);	// So the origin is at the top

			if(normalAngle < 0)
				normalAngle = 2*PI + normalAngle;
		
			incomingAngle = PI - incomingAngle;
			incomingAngle -= normalAngle;

			float outAngle;
			if(incomingAngle > 0)
				outAngle = PI - incomingAngle;
			else
				outAngle = -PI - incomingAngle;
				
			outAngle += normalAngle;

			if(outAngle > 2*PI)
				outAngle -= 2*PI;

			float velocity = Mathematics::sqrt(getVelocity().x * getVelocity().x +  getVelocity().y * getVelocity().y);
			Vector newVelocity(cosf(outAngle) * velocity * mElasticity, -sinf(outAngle) * velocity * mElasticity, 0);

			setVelocity(newVelocity.x, newVelocity.y);
		}
	}

	return true;
}

void Projectile::setSpeed(float speed)
{
	// Gets called when the projectile is created
	// Calculate the vector velocity depending on the rotation and the scalar speed
	setVelocity(Vector(speed * cosf(getBody()->GetRotation()), speed * sinf(getBody()->GetRotation())));
}