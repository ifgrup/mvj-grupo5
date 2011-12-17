#include "cEnemy.h"



cEnemy::cEnemy(WalkingTypes wtype) //en función del tipo de walkability, crea el Functor correspondiente
{
	
	SetPosition(8*32,1*32);
	SetCell(8,1);

	seq=0;
	delay=0;
	
	switch (wtype)
	{
	
		case FLALLING:
			pWalkabilityFunctor=new cWalkabilityFunctorFlalling();
			break;
	
		case PATROL:
			pWalkabilityFunctor=NULL;
			break;
	
		case SQUADRON:
			pWalkabilityFunctor=NULL;
			break;
	}

	this->Trajectory=new cPath(pWalkabilityFunctor);
}


cEnemy::cEnemy()
{
	//SetPosition(8*32,1*32);
	//SetCell(8,1);


	//seq=0;
	//delay=0;

	////CPath must be created, with it's own walkability function
	////this->Trajectory=new cPath(&(cEnemy::IsThisTileWalkeableForMe));
	//this->Trajectory=new cPath(pWalkabilityFunctor);
	//
}
cEnemy::~cEnemy()
{

}

void cEnemy::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	/*VMH:
	Primero calculamos coord. de pantalla, restando a nuestra x,y, la x,y origen, que será la de la primera tile visible (cx*32,cy*32)
	Tenemos en cuenta además el offset en pantalla por el margen Scene_Xo,Scene_Yo*/

	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	/*VMH Y luego, en función de para dónde miramos, y la secuencia en la animación, devolvemos el rectángulo dentro del bitmap que representa el gráfico
	actual a pintar del bichejo*/
	int yInicial=3*32; //La tercera fila en el png de animaciones

	switch(Trajectory->Faced())
	{
		case STOP:	SetRect(rc,256,yInicial,288,yInicial+32);						break;

		case N:		SetRect(rc,((12+seq)<<5),yInicial,((12+seq+1)<<5),yInicial+32);	break;
		case S:		SetRect(rc,(( 8+seq)<<5),yInicial,(( 8+seq+1)<<5),yInicial+32);	break;
		case SE:
		case NE:
		case E:		SetRect(rc,(( 7-seq)<<5),yInicial,(( 7-seq+1)<<5),yInicial+32);	break;
		case SO:
		case NO:
		case O:		SetRect(rc,     (seq<<5),yInicial,   ((seq+1)<<5),yInicial+32);	break;
	}

	/*VMH Si sigue moviéndose, esperamos 4 tics para que no vaya muy rápido, y aumentamos el índice que marca la secuencia de animación del bichejo*/
	if(!Trajectory->IsDone())
	{
		delay++;
		if(delay>=4)
		{
			seq++;
			if(seq>3) seq=0;
			delay=0;
		}
	}
}

void cEnemy::GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	//Life dependency not implemented
	SetRect(rc,0,32,32,64);
}


void cEnemy::GetRectRadar(RECT *rc,int *posx,int *posy)
{
	*posx = RADAR_Xo + ( cx << 2 );
	*posy = RADAR_Yo + ( cy << 2 );

	SetRect(rc,80,32,84,36);
}

void cEnemy::GoToCell(CTile2D **map,int destcx,int destcy)
{
	// Go
	if(Trajectory->IsDone())	
	{
		//cLog::Instance()->Msg("Enemy antes Make\n");
		Trajectory->Make(map,cx,cy,destcx,destcy);
		//cLog::Instance()->Msg("Enemy after Make\n");
	}
	else
	{
		Trajectory->ReMake(map,destcx,destcy);
	}
}

void cEnemy::Move()
{
	int mov;
	static int ticks=0; //VMH guarrada para hacerlos más lentos


	if(!Trajectory->IsDone())
	{

		mov=Trajectory->NextStep(&x,&y,&cx,&cy,1); //Lo hacemos más lento...

		if(mov==ARRIVE)
		{
			Trajectory->Done();
			seq=0;
		}
		else if(mov==CONTINUE)
		{
		}
	}
}

void cEnemy::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cEnemy::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cEnemy::SetCell(int cellx,int celly)
{
	cx = cellx;
	cy = celly;
}
void cEnemy::GetCell(int *cellx,int *celly)
{
	*cellx = cx;
	*celly = cy;
}


bool cEnemy::IsThisTileWalkeableForMe(CTile2D* pTile)
{
	//Beep(1000,100);
	return true; //por defecto siempre walkeable
}

void cEnemy::GetNextTarget(int* newcx,int*newcy)
{
  //returns the next tile that the enemy must go to
	*newcx=15;
	*newcy=18;
}

