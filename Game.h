#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include "d3dUtil.h"
#include "Runnable.h"
#include "Camera.h"
#include "GfxStats.h"
#include "RigidBody.h"
#include "Enums.h"
#include "GameState.h"

class World;

class Game : public Runnable
{
public:
	Game(HINSTANCE hInstance, std::string caption, int width, int height, D3DDEVTYPE devType, DWORD requestedVP);
	~Game();

	void init();
	void update(float t, float dt);
	void draw();
	void changeState(State newState);
private:
	Camera* mCamera;
	GfxStats* mGfxStats;
	GameState* mCurrentState;
};

#endif