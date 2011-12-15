
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "vlrSoundLayer.h"//sound
#include "cEnemy.h"
#define STATE_MAIN	0
#define STATE_GAME	1

class cGame
{
public:
	cGame();
	virtual ~cGame();

	bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
	bool Loop(); 
	void Finalize();

private:
	bool LoopInput();
	bool LoopProcess();
	bool LoopOutput();

	void UpdateScene();

	cGraphicsLayer Graphics;
	cInputLayer Input;
	cScene Scene;
	cCritter Critter;
	cSkeleton Skeleton;
	cEnemy** listEnemies; //array of enemies
	short num_enemies;//num of enemies
	void UpdateEnemiesTarget(int cx,int cy);
	vlrSoundLayer Sound;//sound
	int state;
	bool SoundSistem();
	void ProcessOrder();
	bool Render();
};

#endif
