#include "cStrategyPatrol.h"



cStrategyPatrol::cStrategyPatrol(void)
{
	actualx=-5;
	actualy=-5; //marcas para que la primera vez siempre de que son diferentes al nuevo destino
}

cStrategyPatrol::~cStrategyPatrol(void)
{
}



void cStrategyPatrol::IncTickCount()
{

}

bool cStrategyPatrol::GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y)
{
	bool bcambio=false;
	bool detected=IsPlayerDetected(ecx,ecy,ccx,ccy);

	if (!detected)
		return false;

	//está en nuestra zona de influencia
	if (actualx==ccx && actualy == ccy)
	{
		//estoy yendo a donde está el critter, y no ha cambiado su posición
		return false;
	}

	//aquí sabemos que el critter está en otra celda diferente a la que estábamos yendo, reevaluamos
	actualx=ccx;
	actualy=ccy;
	*new_x=actualx;
	*new_y=actualy;
	return true;

}