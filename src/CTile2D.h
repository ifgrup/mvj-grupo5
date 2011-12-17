#ifndef __CTile2D__
#define __CTile2D__

#include <windows.h>


#define TICS_OF_FIRE 300 //tics de duración de la animación de fuego de una tile

class CTile2D
{
private:
	
	//VMH El mapa pasa de ser una matriz de ints a una matriz de InfoTile2D
	int idTile; //El valor que tenía hasta ahora map[i][j]
	bool isVisible; //Si es visible o no. Por defecto, al cargar, todo visible
	bool isVisited; //Si era invisible y ha sido visitada, por tanto, habrá que aplicar niebla
	bool isFogged; //Era oculta por carga inicial, se ha visitado, y ha pasado de nuevo a ser oculta --> niebla.
	bool isWalkeable; //Indica si es walkeable a nivel del personaje
	bool isEnemyWalkeable; //Indica si es walkeable para los enemigos
	int  timeToHide; //Si queremos que la niebla sea temporal, y luego se haga de nuevo oculto
	bool isAnimated; //Se trata de una tile que debe mostrar una animación, por ejemplo, las llamas del fuego, agua
	int  seqAnimation; //Si es animada, qué índice de la animación se debe mostrar actualmente
	int  nSpritesAnimation; //Si es animada, cuántos sprites tiene la animación
	int  nTicsAnimation; //Num de tics que lleva la imagen actual de la animación. Utilizado para el delay
	bool isActive; //Indica si la tile está dentro de la zona "activa" del jugador
	bool isFired;
	
public:
	CTile2D(int n);
	virtual ~CTile2D(void);

	int getId() {return idTile;}
	bool IsVisible() {return isVisible;}
	bool IsVisited() {return isVisited;}
	bool IsFogged()  {return isFogged;}
	bool IsActive()  {return isActive;}

	bool IsWalkeable() {return isWalkeable;}
	bool IsEnemyWalkeable() {return isEnemyWalkeable;}   
	void GetRect(RECT* r);
	void GetMiniRect(RECT* r);
	void setVisible(bool bVisible);
	void setVisited(bool bVisible);
	void setFogged (bool bFogged);
	void setActive (bool bActive);
	void setWalkeable(bool bWalkeable);
	void setAnimated(bool bAnimated);
	void IncTickCount();
	void setNumSprites(int nSprites);
	void setFired (bool);
	bool IsFired();

};

typedef bool (*pFnCheckWalkeable)(CTile2D*); //VMH

#endif


