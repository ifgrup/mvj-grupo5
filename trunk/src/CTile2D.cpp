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
	this->isFired=false;
}

CTile2D::~CTile2D(void)
{
}

void CTile2D::GetMiniRect(RECT* r)
{
	int tile = idTile - 1;
	//KK
	if (this->IsActive()||this->IsVisible())
		SetRect(r,tile<<5,0,((tile+1)<<5)-28,2);
	else
		SetRect(r,32,0,36,2); //Para que el radar se vea oscuro
	return;
}

void CTile2D::GetRect(RECT* r)
{
	int tile = idTile - 1;
	if (!isAnimated) //Es estática, por tanto, como hasta ahora, indice de la textura, y pinpan
	{
		SetRect(r,tile<<5,0,(tile+1)<<5,32);
		return;
	}
	else //En función de la secuencia, será un índice u otro
	{
		int fila=idTile; //utilizamos idTile como fila de las animaciones en animated.png
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

void CTile2D::setWalkeable(bool bWalkeable)
{
	this->isWalkeable=bWalkeable;
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


	if (!isAnimated)
		return;

	this->nTicsAnimation++;
	if (nTicsAnimation%10==0) //Hacer un #define majo
	{
	    seqAnimation=(seqAnimation+1)%nSpritesAnimation;
		//char kk[100];
		//sprintf(kk,"TickCount %d %d\n",nTicsAnimation,isFired);
		//cLog::Instance()->Msg(kk);
	}

	//Control de la animación de fuego
	if (this->isFired && nTicsAnimation>=TICS_OF_FIRE)
	{//Apagamos el fuego,dejamos el tile chamuscao, y lo ponemos como walkeable
		this->idTile=ID_TILE_CHAMUSCADA; //Tile chamuscada
		this->isWalkeable=true;
		this->isAnimated=false;
		this->isFired=false;
		this->isActive=true;
		nTicsAnimation=0;
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

void CTile2D::setFired(bool bVisible)
{
	isFired=bVisible;
}

bool CTile2D::IsFired()
{
	return isFired;
}

bool CTile2D::IsAnimated()
{
	return isAnimated;
}


void CTile2D::setIdTile(int nidTile)
{
this->idTile=nidTile;
}