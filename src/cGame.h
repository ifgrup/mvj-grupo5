
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "vlrSoundLayer.h"//sound
#include "cEnemy.h"
#include "cDialog.h"


#define STATE_MAIN	0
#define STATE_GAME	1
#define STATE_WIN	2
#define CXF			61
#define CYF			51

class cGame
{
public:
	cGame();
	virtual ~cGame();

	bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
	bool Loop(); 
	void Finalize();
	short GetNumEnemies();

private:
	bool LoopInput();
	bool LoopProcess();
	bool LoopOutput();

	void UpdateScene();
	void ActualizarIA();
	void AutoScroll();
    int CheckIfWin();
	cGraphicsLayer Graphics;
	cInputLayer Input;
	cScene Scene;
	cDialog *pDialog;
	
	cCritter Critter;
	cEnemy** listEnemies; //array of enemies
	short num_enemies;//num of enemies
	void UpdateEnemiesTarget(int cx,int cy);
	vlrSoundLayer Sound;//sound
	int state;
	bool SoundSistem();
	void ProcessOrder();
	bool Render();

	void EfectoPantalla(int idEfecto); //hará un efecto visual para indicar que nos han dado
	void LoadEnemies();
	bool boton_derecho_nunca_pulsado;
};

#endif
