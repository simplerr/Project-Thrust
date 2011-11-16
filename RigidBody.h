#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <string>
#include "Shape.h"
#include "Vector.h"

using namespace Mathematics;
class Rect;

// :NOTE: Scaling objects doesnt change the inertia tensor!

/// Class used in the physic simulation
class RigidBody
{
public:
	RigidBody(float x, float y, int width, int height);
	~RigidBody();

	// General functions
	void ApplyForce(Vector force, Vector pos);
	void ApplyGravity(float gravity);
	void Rotate(float rotation);
	void ResetRotation()			{mShape->resetRotation();}
	void Scale(float scalor)		{mShape->scale(scalor);}
	void Move(float dx, float dy)	{mShape->move(dx, dy);}
	void Move(Vector speed)			{Move(speed.x, speed.y);}

	// Set functions
	void SetCollidable(bool collides)			{mCollidable = collides;}
	void SetPosition(Vector position)			{mPosition = position; mShape->setOrigin(position);}		// :TODO: mShape also needs to update
	void SetVelocity(Vector velocity)			{mVelocity = velocity;}
	void SetVelocity(float x, float y)			{mVelocity = Vector(x, y, 0);}
	void SetAngularVelocity(float velocity)		{mAngularVelocity = velocity;}
	void SetForce(Vector force)					{mForce = force;}
	void SetTorque(Vector torque)				{mTorque = torque.z;}
	void SetTorque(float torque)				{mTorque = torque;}
	void SetMass(float mass)					{mMass = mass; mInertiaTensor = GetMass()*(GetWidth()*GetWidth() + GetHeight() * GetHeight()) / 12;}
	void SetFriction(float friction)			{mFriction = friction;}
	void SetInertia(float inertia)				{mInertiaTensor = inertia;}
	void SetOwner(void* owner)					{mOwner = owner;}
	void SetSimulate(bool simulate)				{mSimulate = simulate;}
	void SetId(int id)							{mId = id;}
	void SetParentId(int id)					{mParentId = id;}

	// Get functions
	Shape*	GetShape()			{return mShape;}	
	Vector	GetPosition()		{return mShape->getOrigin();}
	Vector	GetForce()			{return mForce;}
	Vector	GetVelocity()		{return mVelocity;}	
	int		GetId()				{return mId;}
	int		GetParentId()		{return mParentId;}
	int		GetWidth()			{return mShape->getWidth();}
	int		GetHeight()			{return mShape->getHeight();}
	float	GetRotation()		{return mShape->getRotation();}
	float	GetTorque()			{return mTorque;}
	float	GetAngularVelocity(){return mAngularVelocity;}
	float	GetMass()			{return mMass;}
	float	GetInvMass()		{return mMass == 0 ? 0 : 1 / mMass;}
	float	GetInertia()		{return mInertiaTensor;}
	float	GetInvInertia()		{return mInertiaTensor == 0 ? 0 : 1 / mInertiaTensor;}
	float	GetFriction()		{return mFriction;}
	bool	GetSimulate()		{return mSimulate;}
	bool	GetCollidable()		{return mCollidable;}
	void*	GetOwner()			{return mOwner;}

private:
	// General members
	Shape*		mShape;
	void*		mOwner;
	bool		mCollidable;		// Needed? All rigids can collide? :NOTE:
	bool		mSimulate;
	int			mId;
	int			mParentId;

	// Physic members
	Vector		mPosition;			// Position of center of mass (CM)
	Vector		mVelocity;
	Vector		mForce;
	float		mTorque;
	float		mAngularVelocity;
	float		mMass;
	float		mInertiaTensor;
	float		mInvInertia;
	float		mFriction;
};

#endif