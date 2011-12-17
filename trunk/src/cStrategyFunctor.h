#pragma once
class cStrategyFunctor
{
public:
	cStrategyFunctor(void);
	~cStrategyFunctor(void);

	virtual void IncTickCount();
	virtual bool IsPlayerDetected(int EnemyX, int EnemyY, int PlayerX, int PlayerY);
	virtual void GoToNextTarget();

private:
	int TickCount;
};

