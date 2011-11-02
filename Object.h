#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "RigidBody.h"

class Level;

class Object
{
public:
	Object(float x, float y, int width, int height, std::string textureSource = "imgs\\crate.bmp");
	virtual ~Object();

	virtual void update(float dt);
	virtual void draw();

	virtual void collided(Object* collider);

	void setPosition(Vector pos);
	void setPosition(float x, float y);
	void setVelocity(Vector velocity);
	void setVelocity(float dx, float dy);
	void setWidth(int width);
	void setHeight(int height);
	void setId(int id);
	void setType(ObjectType type);
	virtual void setLevel(Level* level);
	void kill();

	Vector		getPosition();
	Vector		getVelocity();
	int			getWidth();
	int			getHeight();
	int			getId();
	float		getRotation();
	RigidBody*	getBody();
	ObjectType	getType();
	Level*		getLevel();
	bool		getAlive();

	IDirect3DTexture9* getTexture();
private:
	Level*		mLevel;
	RigidBody*	mBody;
	ObjectType	mType;
	int			mId;
	bool		mAlive;
	IDirect3DTexture9* mTexture;

};

#endif