#include "Object.h"
#include "Graphics.h"
#include "Level.h"

Object::Object(float x, float y, int width, int height, std::string textureSource)
{
	mBody = new RigidBody(x, y, width, height);
	mBody->SetOwner(this);

	mTexture = gGraphics->loadTexture(textureSource);

	setType(PLATFORM);
	setOwner(NULL);
}
	
Object::~Object()
{
	// Don't delete mBody, mWorld in Level does it
	ReleaseCOM(mTexture);
}

void Object::update(float dt)
{

}
	
void Object::draw()
{
	gGraphics->drawTexturedShape(*getBody()->getShape(), mTexture);
}

bool Object::collided(Object* collider)
{
	return true;
}

void Object::setPosition(Vector pos)
{
	mBody->SetPosition(pos);
}

void Object::setPosition(float x, float y)
{
	mBody->SetPosition(Vector(x, y));
}

void Object::setVelocity(Vector velocity)
{
	getBody()->SetVelocity(velocity);
}
	
void Object::setVelocity(float dx, float dy)
{
	getBody()->SetVelocity(Vector(dx, dy));
}

void Object::setId(int id)
{
	mId = id;
	mBody->setID(mId);
}

void Object::setType(ObjectType type)
{
	mType = type;
}

void Object::setRotation(float rotation)
{
	getBody()->getShape()->resetRotation();
	getBody()->Rotate(rotation);
}

void Object::setTexture(string textureSource)
{
	mTexture = gGraphics->loadTexture(textureSource);
}

void Object::rotate(float rotate)
{
	getBody()->Rotate(rotate);
}

void Object::setRotationAxis(Vector axis)
{
	getBody()->getShape()->setRotationAxis(axis);
}

Vector Object::getPosition()
{
	return mBody->GetPosition();
}

Vector Object::getVelocity()
{
	return getBody()->GetVelocity();	
}

int Object::getId()
{
	return mId;
}

RigidBody*	Object::getBody()
{
	return mBody;
}

ObjectType Object::getType()
{
	return mType;
}

IDirect3DTexture9* Object::getTexture()
{
	return mTexture;
}

int Object::getWidth()
{
	return getBody()->getWidth();
}

int	Object::getHeight()
{
	return getBody()->getHeight();
}

float Object::getRotation()
{
	return getBody()->GetRotation();
}

void Object::kill()
{
	mAlive = false;
}

void Object::setLevel(Level* level)
{
	mLevel = level;
}

Level* Object::getLevel()
{
	return mLevel;
}

bool Object::getAlive()
{
	return mAlive;
}

void Object::setOwner(Object* owner)
{
	mOwner = owner;

	if(owner != NULL)
		getBody()->SetParentBody(owner->getBody());
	else
		getBody()->SetParentBody(NULL);
}

Object*	Object::getOwner()
{
	return mOwner;
}

Rect Object::getRect()
{
	return getBody()->getShape()->getWorldRect();
}

void Object::setTexture(IDirect3DTexture9* texture)
{
	mTexture = texture;
}