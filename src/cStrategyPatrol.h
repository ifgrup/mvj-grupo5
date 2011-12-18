#pragma once
#include "cstrategyfunctor.h"
class cStrategyPatrol :	public cStrategyFunctor
{
public:
	cStrategyPatrol(void);
	~cStrategyPatrol(void);

	virtual void IncTickCount();
	virtual bool GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y);
private:
	int actualx;
	int actualy;
};
