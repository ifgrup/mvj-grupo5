#pragma once
#include "cstrategyfunctor.h"
class cStrategyPatrol :
	public cStrategyFunctor
{
public:
	cStrategyPatrol(void);
	~cStrategyPatrol(void);

	virtual void IncTickCount();
	virtual bool IsPlayerDetected(int EnemyX, int EnemyY, int PlayerX, int PlayerY);
	virtual void GoToNextTarget();

};

