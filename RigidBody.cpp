#include "RigidBody.h"
#include "Graphics.h"
#include "enums.h"

RigidBody::RigidBody(float x, float y, int width, int height)
{
	// Create a Rectangle shape - origin middle
	mShape = new Shape();
	mShape->setOrigin(Vector(x, y, 0));
	mShape->addPoint(Vector(-width/2, -height/2, 0));	// top - left
	mShape->addPoint(Vector(-width/2, height/2, 0));	// bottom - left
	mShape->addPoint(Vector(width/2, height/2, 0));		// bottom - right
	mShape->addPoint(Vector(width/2, -height/2, 0));	// top - right

	SetMass(1);
	SetVelocity(0, 0);
	SetAngularVelocity(0.0f);
	SetForce(Vector(0, 0, 0));
	SetTorque(Vector(0, 0, 0));
	SetFriction(1.0f);
	SetFriction(0.5f),
	SetSimulate(true);
	SetOwner(NULL);
	
}
	
RigidBody::~RigidBody()
{
	// Dtor
	delete mShape;
}

void RigidBody::ApplyForce(Vector force, Vector pos)
{
	SetForce(GetForce() + force);

	// Torque = r x F
	//SetTorque(force.cross(pos));
	SetTorque((pos - GetPosition()).cross(force));
}

void RigidBody::ApplyGravity(float m)
{

}

void RigidBody::Rotate(float rotation)	
{
	mShape->rotate(rotation);
}