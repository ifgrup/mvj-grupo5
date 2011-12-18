#pragma once
#include "cstrategyfunctor.h"
#include "cScene.h" //Yo haría un Globals.h o algo asi, que aquí haya que hacer el include de Scene no me mola...

#define TAM_CUADRADO_PATRULLA 4 //Tamaño del cuadrado de patrulla

typedef enum 
{

	DERECHA=0,
	ABAJO=1,
	IZQUIERDA=2,
	ARRIBA=3
}Direcciones;

class cStrategyPatrol :	public cStrategyFunctor
{
public:
	cStrategyPatrol(void);
	~cStrategyPatrol(void);

	virtual void IncTickCount();
	virtual bool GoToNextTarget(int ccx, int ccy,int ecx,int ecy,int* new_x,int *new_y);
private:
	int destino_x_actual;
	int destino_y_actual;
	Direcciones direccion_patrulla_actual;
	bool patrulla_iniciada;
};

