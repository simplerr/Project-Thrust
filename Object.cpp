#include "Object.h"
#include "Graphics.h"
#include "Level.h"

Object::Object(float x, float y, int width, int height, std::string textureSource)
{
	mBody = new RigidBody(x, y, width, height);
	mBody->SetOwner(this);

	mTexture = gGraphics->loadTexture(textureSource);

	setType(PLATFORM);
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

void Object::collided(Object* collider)
{
	//showMsg("object");
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

void Object::setWidth(int width)
{
	
}
	
void Object::setHeight(int height)
{

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
	return 0;
}

int	Object::getHeight()
{
	return 0;
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