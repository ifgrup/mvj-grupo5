#include "cStrategyFunctor.h"


cStrategyFunctor::cStrategyFunctor(void)
{
	
}


cStrategyFunctor::~cStrategyFunctor(void)
{
}

bool cStrategyFunctor::IsPlayerDetected(int EnemyX, int EnemyY, int PlayerX, int PlayerY)
{
	if((PlayerX > (EnemyX - ENEMY_DETECT_ZONE) && PlayerX < (EnemyX + ENEMY_DETECT_ZONE)) &&
		(PlayerY > (EnemyY - ENEMY_DETECT_ZONE) && PlayerY < (EnemyY + ENEMY_DETECT_ZONE)))
		return true;

	return false;
}

void cStrategyFunctor::IncTickCount()
{

}

bool cStrategyFunctor::GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y)
{
	return false; //Por defecto no hace nada

}