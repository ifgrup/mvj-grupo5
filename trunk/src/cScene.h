
#ifndef __SCENE_H__
#define __SCENE_H__

//Resolution
#define SCREEN_RES_X	800
#define SCREEN_RES_Y	600

//Visible part
#define SCENE_WIDTH		25
#define SCENE_HEIGHT	17

//Dimension = Area^2
#define SCENE_AREA		32

//Map coordinate beginning
#define SCENE_Xo		0
#define SCENE_Yo		55
#define SCENE_Xf		( SCENE_Xo + (SCENE_WIDTH<<5)  )
#define SCENE_Yf		( SCENE_Yo + (SCENE_HEIGHT<<5) )

//Radar position (left,top)
#define RADAR_Xo		666
#define RADAR_Yo		86
#define RADAR_Xf		711
#define RADAR_Yf		214

// LHA
#define RADIO_VISIBLE   2

#include "CTile2D.h" //VMH
class cScene
{

public:
	
	cScene();
	virtual ~cScene();

	void LoadMap(char *file);
	void Move(int pointer);
	void MoveByRadar(int x,int y);
	bool Visible(int cellx,int celly);
	bool IsCellVisible(int cellx, int celly); //VMH
	bool IsCellVisited(int cellx, int celly); //LHA
	bool IsCellActive(int cellx, int celly);
	bool IsVisible(int cellx, int celly); // LHA
	bool IstWalkeableHero(int cellx, int celly);
	void ResetVisible();
	CTile2D** getTilesMap() { return TilesMap; }
	int  getTileType(int idx); //VMH
	
	int cx,cy; /*VMH casillas que marcan la esquina superior izquierda de las casillas visibles actualmente en pantalla*/

	void GetRect(int idx,RECT* r); //VMH: Devuelve el rect a elegir de la textura de Tiles para pintar
	void GetMiniRect(int idx, RECT* r);
	void UpdateVisibleZone(int cx,int cy); //VMH: El prota está aquí. Cada vez que se mueva, si radio de acción debe ponerse como visible.
	void IncTickCount(); //VMH actualiza el tick count para las celdas animadas.
	bool IsFogged(int cellx,int celly); //VMH Oscura inicialmente, ya visitada

private:
	CTile2D  **TilesMap;  /*VMH mapa cpn la información de las casillas. Inicialmente sólo tenía el índice para acceder al bitmap.
			     Ahora contiene más información, por eso utilizamos la estuctura InfoTile2D*/
	
};


#endif
