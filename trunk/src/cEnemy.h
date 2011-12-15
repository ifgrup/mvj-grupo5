#ifndef __ENEMY__H__
#define __ENEMY__H__

#include <windows.h>
#include "cTrajectory.h"
#include "cPath.h"
#include "cScene.h"



class cEnemy
{
public:
	cEnemy(void);
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