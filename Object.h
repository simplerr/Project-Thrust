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

	virtual bool collided(Object* collider);	// Collided return false if objectB is deleted inside the function

	void rotate(float rotate);

	virtual void setVelocity(Vector velocity);
	virtual void setVelocity(float dx, float dy);

	void setPosition(Vector pos);
	void setPosition(float x, float y);
	void setId(int id);
	void setType(ObjectType type);
	void setRotation(float rotation);
	void setRotationAxis(Vector axis);
	void setTexture(string textureSource);
	void setTexture(IDirect3DTexture9* texture);
	void setParent(Object* parent);
	void setSimulate(bool simulate);
	virtual void setLevel(Level* level);
	void kill();

	Vector		getPosition();
	Vector		getVelocity();
	int			getWidth(bool rotated = true);
	int			getHeight(bool rotated = true);
	int			getId();
	float		getRotation();
	RigidBody*	getBody();
	Rect		getRect();
	Level*		getLevel();
	Object*		getParent();
	ObjectType	getType();
	bool		getAlive();
	bool		getSimulate();

	IDirect3DTexture9* getTexture();
private:
	Level*		mLevel;				// The active level
	RigidBody*	mBody;				// The body used for simulation
	Object*		mParent;			// The parent, ex the player for a bullet
	ObjectType	mType;				// Type
	int			mId;				// Id, same in mBody
	bool		mAlive;				// Alive or dead
	IDirect3DTexture9* mTexture;	// Object texture

};

#endif