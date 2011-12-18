#ifndef __ENEMY__H__
#define __ENEMY__H__

#include <windows.h>
#include "cTrajectory.h"
#include "cPath.h"
#include "cScene.h"
#include "cWalkabilityFunctor.h"
#include "cWalkabilityFunctorFlalling.h"
#include "cWalkabilityFunctorRandom.h"
#include "cStrategyFunctor.h"
#include "cStrategyPatrol.h"
#include "cStrategyFolouDeCritter.h"


typedef enum WalkingTypes{
	FLALLING=1,
	RANDOM=2,
	GRIJANDER=3
}WalkingTypes;

typedef enum StrategyTypes{
	PATROL=1,
	FOLOU=2
}StrategyTypes;


class cEnemy
{
public:

	cEnemy(int cx,int cy,WalkingTypes walkabilityType,StrategyTypes stype); //en función del tipo de walkability, crea el Functor correspondiente
	cWalkabilityFunctor* pWalkabilityFunctor;
	cStrategyFunctor* pStrategyFunctor;

	virtual ~cEnemy(void);

	void GoToCell(CTile2D **map,int destcx,int destcy);
	void Move();
	void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectRadar(RECT *rc,int *posx,int *posy);

	void SetPosition(int posx,int posy);
	void GetPosition(int *posx,int *posy);
	void SetCell(int cellx,int celly);
	void GetCell(int *cellx,int *celly);
	bool GetDestinyCell(int* cx, int* cy); //Devuelve el destino actual de la trayectoria del bicho
	
	
	bool HasDetectedPlayer(int x, int y);
	bool NextTarget(int CritterX, int CritterY,int* newx,int* newy);
	void RecargaWalkability();

private:
	int x,y;		//Position in total map
	int cx,cy;		//Cell position in total map
	int cxHome,cyHome; //Posiciones iniciales del enemigo, a las que vuelve cuando contacta con el critter.
	cPath* Trajectory; //Dinamic, with it's own walkeable function
	int seq;		//Sequence animation control
	int delay;		//Animation delay
	int filaTilesPersonaje; //Fila del fichero characters.png donde está su animación

public:
	static bool IsThisTileWalkeableForMe(CTile2D*);
	void GetNextTarget(int* newcx,int*newcy);
	void GoHome(); //vuelve a la posición inicial

};

#endif