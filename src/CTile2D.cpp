#include "CTile2D.h"
#include "cLog.h"

CTile2D::CTile2D(int n)
{
	this->idTile=n ; //Indice dentro del bitmap de tiles
	this->isVisited=0; //por defecto siempre lo será al crearse, en la carga del mapa
	this->isWalkeable=(n==0); //Actualmente, si es la cero, es walkeable 	
	this->isEnemyWalkeable=(n==0); //De momento, igual para los dos. PAra los enemigos, será dinámico en función de los disparos de fuego. 	
	this->isAnimated=0;
	this->seqAnimation=0;
	this->nTicsAnimation=0;
	this->isFogged=false;
}

CTile2D::~CTile2D(void)
{
}

void CTile2D::GetMiniRect(RECT* r)
{
	SetRect(r,idTile<<5,0,((idTile+1)<<5)-28,4);
	return;
}

void CTile2D::GetRect(RECT* r)
{
	if (!isAnimated) //Es estática, por tanto, como hasta ahora, indice de la textura, y pinpan
	{
		SetRect(r,idTile<<5,0,(idTile+1)<<5,32);
		return;
	}
	else //En función de la secuencia, será un índice u otro
	{
		int fila=idTile; //1ª fila las estáticas, luego, una fila por animación.Como empiezan en 1, no hay que sumar 1
		int columna=seqAnimation;
		
		SetRect(r,columna<<5,fila<<5,(columna+1)<<5,(fila+1)<<5);
		return;
	}
}

void CTile2D::setVisible(bool bVisible)
{
	this->isVisible=bVisible;
}

void CTile2D::setVisited(bool bVisited)
{
	this->isVisited=bVisited;
}

void CTile2D::setAnimated(bool bAnimated)
{
	this->isAnimated=bAnimated;
}

void CTile2D::setActive(bool bActive)
{
	this->isActive = bActive;
}

void CTile2D::IncTickCount()
{
  //Updates counter of all animated tiles, in order to change it animation sequence
	char kk[100];
	sprintf(kk,"TickCount %d %d\n",nTicsAnimation,seqAnimation);
	//cLog::Instance()->Msg(kk);

	this->nTicsAnimation++;
	if (nTicsAnimation>10) //Hacer un #define majo
	{
		nTicsAnimation=0;
	    seqAnimation=(seqAnimation+1)%nSpritesAnimation;
		
	}
  
}

void CTile2D::setNumSprites(int nSprites)
{
	this->nSpritesAnimation=nSprites;
}

void CTile2D::setFogged(bool bFogged)
{
	this->isFogged=bFogged;
}
