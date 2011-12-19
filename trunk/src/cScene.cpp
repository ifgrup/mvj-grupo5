
#include "cScene.h"
#include "cMouse.h"
#include <stdio.h>
#include "CTile2D.h"
#include "cLog.h"


cScene::cScene()
{
	cx=0;
	cy=0;
}

cScene::~cScene(){}

bool isWalkeable(int TileID)
{
	switch(TileID)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 31:
	case 32:
	case 33:
		return true;
		break;
	default:
		return false;
		break;
	}
}


void cScene::LoadMap(char *file)
{
	int i,j,k,n;

	//VMH: Reservamos memoria para el resto de info del mapa, s�lo para los punteros, el contenido se crear� din�micamente
	//TilesMap=(CTile2D**) malloc(sizeof(CTile2D*)*(SCENE_AREA*SCENE_AREA));
	TilesMap = new CTile2D*[SCENE_AREA*SCENE_AREA];

	FILE *f;
	f=fopen(file,"r");
	k=0;

	for(int x = 0; x < SCENE_AREA*SCENE_AREA; x++)
	{
		fscanf(f,"%d",&n);
		TilesMap[x]=new CTile2D(n); 
		TilesMap[x]->setWalkeable(isWalkeable(n)); 
		TilesMap[x]->setVisible(false);
		TilesMap[x]->setFogged(true);
	}



	fclose(f);
}

void cScene::Move(int pointer)
{
	//map=32x32, visible=20x17 => move=0..32-20,0..32-17=0..12,0..15

	//Up
	if((pointer==MN)||(pointer==MNO)||(pointer==MNE))
	{
		if(cy>0) cy--;
	}
	//South
	else if((pointer==MS)||(pointer==MSO)||(pointer==MSE))
	{
		if(cy<SCENE_AREA-SCENE_HEIGHT) cy++;
	}
	//West
	if((pointer==MO)||(pointer==MNO)||(pointer==MSO))
	{
		if(cx>0) cx--;
	}
	//East
	else if((pointer==ME)||(pointer==MNE)||(pointer==MSE))
	{
		if(cx<SCENE_AREA-SCENE_WIDTH) cx++;
	}

	//VMH : Una vez movido, las zonas que pasan a ser invisibles, si estaban ocultas, pasan a ser en niebla para siempre:
	for (int f=0;f<SCENE_AREA;f++)
		for (int c=0;c<SCENE_AREA;c++)
		{
			if (!Visible(c,f))
			{
				int idx=(f*SCENE_AREA)+c;
				if ((!TilesMap[idx]->IsVisible()) && TilesMap[idx]->IsVisited())
				{
					 TilesMap[idx]->setFogged(true);
				}
			}
		}
}

void cScene::MoveByRadar(int x,int y)
{
	//move=0..12,0..15
	//rect=(80x68)/4=20x17

	cx=(x-RADAR_Xo)>>1;
	cy=(y-RADAR_Yo)>>1;

	if(cx<=9)		cx=0;
	else if(cx>=21)	cx=12;
	else			cx-=9;
	
	if(cy<=8)		cy=0;
	else if(cy>=23)	cy=15;
	else			cy-=8;
}


void cScene::MoveScroll(int x,int y)
{
	//move=0..12,0..15
	//rect=(80x68)/4=20x17

	cx=x;
	cy=y;

	if(cx<=9)		cx=0;
	else if(cx>=21)	cx=12;
	else			cx-=9;
	
	if(cy<=8)		cy=0;
	else if(cy>=23)	cy=15;
	else			cy-=8;
}
bool cScene::Visible(int cellx,int celly)
{
	/*VMH Devuelve si la casilla cx,cy est� actualmente dentro de zona visible.
	*/
	bool enZona=((cellx>=cx)&&(cellx<cx+SCENE_WIDTH)&&(celly>=cy)&&(celly<cy+SCENE_HEIGHT)) ? 1 : 0;

	return enZona;
}

bool cScene::IsCellVisible(int cellx,int celly)//Por no modificar la Visible que ya se utiliza antes.... revisar por si se puede
{
	int idx=(celly*SCENE_AREA)+cellx;
	return TilesMap[idx]->IsVisible() || ( (!TilesMap[idx]->IsVisible()) && TilesMap[idx]->IsVisited());
}

bool cScene::IsVisible(int cellx, int celly)
{
	int idx=(celly*SCENE_AREA)+cellx;
	return TilesMap[idx]->IsVisible();
}

bool cScene::IsWalkeableHero(int cellx, int celly)
{
	int idx=(celly*SCENE_AREA)+cellx;
	return TilesMap[idx]->IsWalkeable();
}

bool cScene::IsCellActive(int CellX, int CellY)
{
	bool bActive = false;

	if(Visible(CellX, CellY))
	{
		int idx = (CellY * SCENE_AREA) + CellX;
		bActive = TilesMap[idx]->IsActive();
	}

	return bActive;
}

bool cScene::IsCellVisited(int cellx, int celly)
{
	bool bVisited = true;
	if(Visible(cellx, celly))
	{
		int idx = (celly*SCENE_AREA)+cellx;
		bVisited = TilesMap[idx]->IsVisited();
	}

	return bVisited;
}

bool cScene::IsFogged(int cellx,int celly)
{
	/*VMH Devuelve si la casilla cx,cy est� actualmente dentro de zona visible.
	*/
	bool bFog = true;

	if(Visible(cellx, celly))
	{
		int idx=(celly*SCENE_AREA)+cellx;
		bFog = (TilesMap[idx]->IsFogged());  
	}

	return bFog;
}

//VMH : devuelve el id de la tile, lo mismo a lo que se acced�a anteriormente en map[]
int cScene::getTileType(int idx)
{
	return TilesMap[idx]->getId();

}//VMH

//VMH: En funci�n del tipo, si es din�mica, etc, devuelve el rect dentro de la textura a pintar.
void cScene::GetRect(int idx,RECT* r)
{
	TilesMap[idx]->GetRect(r);
}

void cScene::GetMiniRect(int idx, RECT* r)
{

	TilesMap[idx]->GetMiniRect(r);
}

void cScene::ResetVisible()
{
	int k = 0;
	for(int i = 0; i < SCENE_AREA; i++)
	{
		for(int j = 0; j < SCENE_AREA; j++)
		{
			TilesMap[k]->setActive(false);
			k++;
		}
	}
}

void cScene::UpdateVisibleZone(int cx,int cy)//VMH: El prota est� aqu�. Cada vez que se mueva, si radio de acci�n debe ponerse como visible.
{
	static int last_cx=0;
	static int last_cy=0;

	if (cx==last_cx && cy==last_cy) //si no han cambiado, nothing to do
		return;

	ResetVisible();

	last_cx=cx;
	last_cy=cy;

	int cxinit=(cx-RADIO_VISIBLE) >=0 ? cx-RADIO_VISIBLE : 0;
	int cxfin= (cx+RADIO_VISIBLE) < SCENE_AREA ? cx+RADIO_VISIBLE : SCENE_AREA-1;
	int cyinit=(cy-RADIO_VISIBLE) >=0 ? cy-RADIO_VISIBLE : 0;
	int cyfin= (cy+RADIO_VISIBLE) < SCENE_AREA ? cy+RADIO_VISIBLE : SCENE_AREA-1;

	for (int fila=cyinit;fila<=cyfin;fila++)
	{
		for(int col=cxinit;col<=cxfin;col++)
		{
			int idx=(fila*SCENE_AREA)+col; //index in tiles array
			TilesMap[idx]->setVisited(true);
			TilesMap[idx]->setFogged(false); //vuelve a ser visible, hasta que vuelva a desaparecer de pantalla.Controlado en Scene::Move
			TilesMap[idx]->setVisible(true);
			TilesMap[idx]->setActive(true);
		}
	}
	
}

void cScene::IncTickCount()
{
	for (int i=0;i<SCENE_AREA*SCENE_AREA;i++)
		TilesMap[i]->IncTickCount();
}


//void cScene::SetAnimateTile(int cx,int cy)
//{
//
//	int idx=cy*SCENE_AREA+cx;
//	TilesMap[idx]->setAnimated(true);
//	TilesMap[idx]->setNumSprites(5);
//	TilesMap[idx]->setActive(true);
//	TilesMap[idx]->setWalkeable(false);
//}

void cScene::SetFireTile(int cx,int cy)
{

	int idx=cy*SCENE_AREA+cx;
	TilesMap[idx]->setAnimated(true);
	TilesMap[idx]->setIdTile(0);//la animaci�n de fuego
	TilesMap[idx]->setNumSprites(4);
	TilesMap[idx]->setActive(true); //ask lha
	TilesMap[idx]->setFired(true);
}

bool cScene::IsCellFired(int cx,int cy)
{
	int idx=cy*SCENE_AREA+cx;
	return TilesMap[idx]->IsFired();
	
}

bool cScene::IsCellAnimated(int cx,int cy)
{
	int idx=cy*SCENE_AREA+cx;
	return TilesMap[idx]->IsAnimated();
	
}


void cScene::CentrarEscenaEnTile(int px, int py)
{
  //Funci�n an�loga a MoveByRadar, pero gen�rica, con nuestros cambios  y comentarios just in case
  int mitad_x=SCENE_WIDTH >>1 ;
  int mitad_y=SCENE_HEIGHT >>1 ;

  if (px > mitad_x)
	  this->cx-=mitad_x;
  else
	  this->cx=0;
  
  if (py > mitad_y)
	  this->cy-=mitad_y;
  else
	  this->cx=0;


}


void cScene::MoveOffset(int dx, int dy)
{
    if(cx+dx >=0 && cx+dx <SCENE_AREA+SCENE_WIDTH)
		
		cx+=dx;

	if(cy+dy >=0 && cy+dy <SCENE_AREA+SCENE_HEIGHT)
		cy+=dy;

}