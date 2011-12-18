#pragma once
#define ENEMY_DETECT_ZONE 4

class cStrategyFunctor
{
public:
	cStrategyFunctor(void);
	~cStrategyFunctor(void);

	virtual void IncTickCount();
	virtual bool IsPlayerDetected(int EnemyX, int EnemyY, int PlayerX, int PlayerY);
	virtual bool GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y);

private:
	int TickCount;

};

