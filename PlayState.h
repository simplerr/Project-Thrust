#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include  "d3dUtil.h"

class Level;
class Player;
class Object;

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();

	void update(float dt);
	void draw();

	void rotationTest();
private:
	Level*	mLevel;
	Player* mPlayer;
	IDirect3DTexture9* mBkgdTexture;

	Vector mRotationPoint;
	Vector mPoint;
	Vector mRetard;

	Object* mTest;
	float mRotation;
};

#endif