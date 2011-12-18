#include "cEnemy.h"



cEnemy::cEnemy(int pcx,int pcy,WalkingTypes wtype,StrategyTypes stype) //en funci�n del tipo de walkability, crea el Functor correspondiente
{


	seq=0;
	delay=0;
	
	cxHome=pcx;
	cyHome=pcy;
	
	
	SetPosition(pcx*32,pcy*32);
	cx=pcx;
	cy=pcy;

	
	
	switch (wtype)
	{
	
		case FLALLING:
			pWalkabilityFunctor=new cWalkabilityFunctorFlalling();
			break;
	
		case FLISKINS:
			pWalkabilityFunctor=NULL;
			break;
	
		case GRIJANDER:
			pWalkabilityFunctor=NULL;
			break;
	}

	switch(stype)
	{
	case PATROL:
		pStrategyFunctor = new cStrategyPatrol();
		break;
	case FOLOU:
		pStrategyFunctor = new cStrategyFolouDeCritter();
		
	}

	this->Trajectory=new cPath(pWalkabilityFunctor);
	
	//this->Trajectory->xf=this->cxHome;
	//this->Trajectory->yf=this->cyHome;
	//this->Trajectory->Done();

}



cEnemy::~cEnemy()
{

}

void cEnemy::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	/*VMH:
	Primero calculamos coord. de pantalla, restando a nuestra x,y, la x,y origen, que ser� la de la primera tile visible (cx*32,cy*32)
	Tenemos en cuenta adem�s el offset en pantalla por el margen Scene_Xo,Scene_Yo*/

	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	/*VMH Y luego, en funci�n de para d�nde miramos, y la secuencia en la animaci�n, devolvemos el rect�ngulo dentro del bitmap que representa el gr�fico
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

	/*VMH Si sigue movi�ndose, esperamos 4 tics para que no vaya muy r�pido, y aumentamos el �ndice que marca la secuencia de animaci�n del bichejo*/
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
	static int ticks=0; //VMH guarrada para hacerlos m�s lentos


	if(!Trajectory->IsDone())
	{

		mov=Trajectory->NextStep(&x,&y,&cx,&cy,1); //Lo hacemos m�s lento...

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


bool cEnemy::HasDetectedPlayer(int x, int y)
{
	return pStrategyFunctor->IsPlayerDetected(cx, cy, x, y);
}
void cEnemy::GoHome()
{
	if (cx != cxHome || cy != cyHome)
	{
		cx=cxHome;
		cy=cyHome;
		x=cx*32;
		y=cy*32; //Actualizamos tambi�n la posici�n gr�fica.
		Trajectory->Done(); //Al recalcular su objetivo, se asignar� el nuevo objetivo
	}
}


bool cEnemy::GetDestinyCell(int* pcx, int* pcy)
{
	
	bool result=Trajectory!=NULL;

	if (Trajectory )
	{
		*pcx=Trajectory->nxf;
		*pcy=Trajectory->nyf;
		
		if (*pcx==-1 && *pcy ==-1)
			result=false;
	}
	
	return result;

}

bool cEnemy::NextTarget(int CritterX, int CritterY,int* newx,int* newy)
{
	return pStrategyFunctor->GoToNextTarget(CritterX, CritterY,cx,cy,newx,newy);
}