#include "Object.h"
#include "Graphics.h"
#include "Level.h"
#include "ObjectData.h"

Object::Object(float x, float y, int width, int height, std::string textureSource)
{
	// Init defaults
	initDefaults();

	mBody = new RigidBody(x, y, width, height);
	mBody->SetOwner(this);

	mTexture = gGraphics->loadTexture(textureSource);	
}
	
Object::Object(ObjectData* data, float x, float y)
{
	// Init defaults
	initDefaults();

	// Get data from the XML element
	int width = data->getValueDouble("Width");
	int height = data->getValueDouble("Height");
	string texture = data->getValueString("Texture");

	// Set the data
	mBody = new RigidBody(x, y, width, height);
	mBody->SetOwner(this);
	mTexture = gGraphics->loadTexture(texture);
}

void Object::initDefaults()
{
	setType(PLATFORM);
	setParent(NULL);
	setVisible(true);
	setRectCollision(false);
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
	gGraphics->drawTexturedShape(*getBody()->GetShape(), mTexture);
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
	mBody->SetId(mId);
}

void Object::setType(ObjectType type)
{
	mType = type;
}

void Object::setRotation(float rotation)
{
	getBody()->GetShape()->resetRotation();
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
	getBody()->GetShape()->setRotationAxis(axis);
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

int Object::getWidth(bool rotated)
{
	return getBody()->GetWidth(rotated);
}

int	Object::getHeight(bool rotated)
{
	return getBody()->GetHeight(rotated);
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

void Object::setParent(Object* parent)
{
	mParent = parent;
}

Object*	Object::getParent()
{
	return mParent;
}

Rect Object::getRect()
{
	return getBody()->GetShape()->getWorldRect();
}

void Object::setTexture(IDirect3DTexture9* texture)
{
	mTexture = texture;
}

void Object::setSimulate(bool simulate)
{
	getBody()->SetSimulate(simulate);
}

bool Object::getSimulate()
{
	return getBody()->GetSimulate();
}

bool Object::getVisible()
{
	return mVisible;
}

void Object::setVisible(bool visible)
{
	mVisible = visible;
}

void Object::childEvent(string eventMessage)
{
	
}

void Object::loadData(ObjectData data)
{
	
}

bool Object::isRectCollision()
{
	return mRectCollision;
}

void Object::setRectCollision(bool rectCollision)
{
	mRectCollision = rectCollision;
}
