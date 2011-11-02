#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include  "d3dUtil.h"

class Level;
class Player;

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();

	void update(float dt);
	void draw();
private:
	Level*	mLevel;
	Player* mPlayer;
	IDirect3DTexture9* mBkgdTexture;
};

#endif