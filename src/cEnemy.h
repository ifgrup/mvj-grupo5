#ifndef __ENEMY__H__
#define __ENEMY__H__

#include <windows.h>
#include "cTrajectory.h"
#include "cPath.h"
#include "cScene.h"
#include "cWalkabilityFunctor.h"
#include "cWalkabilityFunctorFlalling.h"
#include "cStrategyFunctor.h"
#include "cStrategyPatrol.h"

#define ENEMY_DETECT_ZONE 4

typedef enum WalkingTypes{
	FLALLING=1,
	PATROL=2,
	SQUADRON=3
}WalkingTypes;


class cEnemy
{
public:
	cEnemy(void);
	cEnemy(WalkingTypes walkabilityType); //en función del tipo de walkability, crea el Functor correspondiente
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

	bool HasDetectedPlayer(int x, int y);

private:
	int x,y;		//Position in total map
	int cx,cy;		//Cell position in total map

	cPath* Trajectory; //Dinamic, with it's own walkeable function
public:
	static bool IsThisTileWalkeableForMe(CTile2D*);
	void GetNextTarget(int* newcx,int*newcy);
	int seq;		//Sequence animation control
	int delay;		//Animation delay

};

#endif