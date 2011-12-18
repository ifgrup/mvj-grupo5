#include "cStrategyFolouDeCritter.h"


cStrategyFolouDeCritter::cStrategyFolouDeCritter(void)
{
	first_detected=false;
	//actualx,y las marcamos para que inicialmente sean seguro diferentes a la posición del critter
	actualx=-4;
	actualy=-4;
}


cStrategyFolouDeCritter::~cStrategyFolouDeCritter(void)
{
}




bool cStrategyFolouDeCritter::GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y)
{
	bool bcambio=false;
	
	
	if (!first_detected)
	{
		first_detected=IsPlayerDetected(ecx,ecy,ccx,ccy);
	}
	
	if(!first_detected)
		return false;

	//ya está detectado_
    
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