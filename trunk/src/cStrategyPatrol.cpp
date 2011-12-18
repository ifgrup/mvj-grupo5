#include "cStrategyPatrol.h"



cStrategyPatrol::cStrategyPatrol(void)
{
	destino_y_actual=-5;
	destino_y_actual=-5; //marcas para que la primera vez siempre de que son diferentes al nuevo destino
	//Inicialmente la patrulla, hacia la derecha
	direccion_patrulla_actual=DERECHA;
	patrulla_iniciada=false;
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
	bool detected=IsPlayerDetected(ecx,ecy,ccx,ccy); //Eval�a si est� en nuestra zona de influencia

	if (!detected)
	{
		//hay que hacer la patrulla. Se mueve en cuadrado alrededor de su �ltima posici�n
		//como son las 4 direcciones del cuadrado, debemos saber en cu�l de ellas estamos:
		if (!patrulla_iniciada)
		{
			destino_x_actual=ecx+TAM_CUADRADO_PATRULLA<SCENE_WIDTH ? ecx+TAM_CUADRADO_PATRULLA : SCENE_AREA-1;
			destino_y_actual=ecy;
			*new_x=destino_x_actual;
			*new_y=destino_y_actual;
			direccion_patrulla_actual=(Direcciones)(rand()%4); //Iniciamos la patrulla en cualquier direcci�n
			patrulla_iniciada=true;
			return true;
		}
		switch(direccion_patrulla_actual)
		{
			case DERECHA:
				if (ecx==destino_x_actual)
				{
					//Hemos llegado a la patrulla en derecha. Pues hacia abajo
					direccion_patrulla_actual=(Direcciones)((direccion_patrulla_actual+1)%4);//las 4 direcciones, clockwise
					*new_y=ecy+TAM_CUADRADO_PATRULLA <SCENE_WIDTH ? ecy+TAM_CUADRADO_PATRULLA : SCENE_AREA-1;
					*new_x=ecx;
					destino_y_actual=*new_y;
					bcambio=true;
				}
				break;

			case IZQUIERDA:

				if (ecx==destino_x_actual)
				{
					//Hemos llegado a la patrulla en izda. Pues hacia arriba
					direccion_patrulla_actual=(Direcciones)((direccion_patrulla_actual+1)%4);//las 4 direcciones, clockwise
					*new_x=ecx;
					*new_y=ecy-TAM_CUADRADO_PATRULLA >0 ? ecy-TAM_CUADRADO_PATRULLA : 0;
					destino_y_actual=*new_y;
					bcambio=true;
				}
				break;
			case ARRIBA:

				if (ecy==destino_y_actual)
				{
					//Hemos llegado a la patrulla en abajo. Pues hacia derecha
					direccion_patrulla_actual=(Direcciones)((direccion_patrulla_actual+1)%4);//las 4 direcciones, clockwise
					*new_x=ecx+TAM_CUADRADO_PATRULLA <SCENE_AREA ? ecx+TAM_CUADRADO_PATRULLA : SCENE_AREA-1;
					*new_y=ecy;
					destino_x_actual=*new_x;
					bcambio=true;
				}
				break;

			case ABAJO:
				if (ecy==destino_y_actual)
				{
					//Hemos llegado a la patrulla en abajo. Pues hacia izquierda
					direccion_patrulla_actual=(Direcciones)((direccion_patrulla_actual+1)%4);//las 4 direcciones, clockwise
					*new_x=ecx-TAM_CUADRADO_PATRULLA >0 ? ecx-TAM_CUADRADO_PATRULLA : 0;
					*new_y=ecy;
					destino_x_actual=*new_x;
					bcambio=true;
				}

		}
		return bcambio;
	}
	else
	{
		//est� en nuestra zona de influencia
		patrulla_iniciada=false; //Ya no estamos de patrulla, estamos en persecuci�n
		if (destino_x_actual==ccx && destino_y_actual == ccy)
		{
			//estoy yendo a donde est� el critter, y no ha cambiado su posici�n
			return false;
		}

		//aqu� sabemos que el critter est� en otra celda diferente a la que est�bamos yendo, reevaluamos
		destino_x_actual=ccx;
		destino_y_actual=ccy;
		*new_x=destino_x_actual;
		*new_y=destino_y_actual;
		return true;
	}
}