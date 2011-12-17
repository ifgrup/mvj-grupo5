#pragma once
#include "cstrategyfunctor.h"
class cStrategyFolouDeCritter :	public cStrategyFunctor
{
public:
	cStrategyFolouDeCritter(void);
	virtual ~cStrategyFolouDeCritter(void);
	
	virtual bool GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y);

private:
	int actualx;
	int actualy;
};

