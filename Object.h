#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "RigidBody.h"

using namespace std;

class ObjectData;
class Level;

class Object
{
public:
	Object(float x, float y, int width, int height, std::string textureSource = "imgs\\crate.bmp");
	Object(ObjectData* data, float x, float y);
	virtual ~Object();

	virtual void update(float dt);
	virtual void draw();
	virtual void loadData(ObjectData data);
	virtual void childEvent(string eventMessage);
	virtual void initDefaults();
	virtual void applyForce(Vector force);

	virtual bool collided(Object* collider);	// Collided return false if objectB is deleted inside the function

	void initBody(float x, float y);

	void rotate(float rotate);

	virtual void setVelocity(Vector velocity);
	virtual void setVelocity(float dx, float dy);
	virtual void setLevel(Level* level);
	
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
	void setVisible(bool visible);
	void setCollidable(bool collides);
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
	Object*		getGrandParent();
	ObjectType	getType();
	bool		getAlive();
	bool		getSimulate();
	bool		getVisible();

	IDirect3DTexture9* getTexture();
private:
	Level*		mLevel;				// The active level
	RigidBody*	mBody;				// The body used for simulation
	Object*		mParent;			// The parent, ex the player for a bullet
	ObjectType	mType;				// Type
	int			mId;				// Id, same in mBody
	bool		mAlive;				// Alive or dead
	bool		mVisible;			// Drawn or not
	IDirect3DTexture9* mTexture;	// Object texture
};

#endif