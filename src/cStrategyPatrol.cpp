#include "cStrategyPatrol.h"

#define ENEMY_DETECT_ZONE 2

cStrategyPatrol::cStrategyPatrol(void)
{
}

cStrategyPatrol::~cStrategyPatrol(void)
{
}

bool cStrategyPatrol::IsPlayerDetected(int EnemyX, int EnemyY, int PlayerX, int PlayerY)
{
	if((PlayerX > (EnemyX - ENEMY_DETECT_ZONE) && PlayerX < (EnemyX + ENEMY_DETECT_ZONE)) &&
		(PlayerY > (EnemyY - ENEMY_DETECT_ZONE) && PlayerY < (EnemyY + ENEMY_DETECT_ZONE)))
		return true;

	return false;
}

void cStrategyPatrol::IncTickCount()
{

}

void cStrategyPatrol::GoToNextTarget()
{

}