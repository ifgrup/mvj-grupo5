
#include "cCritter.h"


cCritter::cCritter()
{
	SetPosition(32,32);
	SetCell(1,1);
	SetSelected(true);

	Lives = CRITTER_LIVES;

	seq=0;
	delay=0;

	attack=false;
	shoot=false;
	shoot_seq=0;
	shoot_delay=0;
	//Creamos la trayectoria, y el WalkabilityFunctor por defecto
	cWalkabilityFunctor* pWalk=new cWalkabilityFunctor();

	this->Trajectory=new cPath(pWalk);

}
cCritter::~cCritter()
{

}

void cCritter::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	/*VMH:
	Primero calculamos coord. de pantalla, restando a nuestra x,y, la x,y origen, que ser� la de la primera tile visible (cx*32,cy*32)
	Tenemos en cuenta adem�s el offset en pantalla por el margen Scene_Xo,Scene_Yo*/

	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	/*VMH Y luego, en funci�n de para d�nde miramos, y la secuencia en la animaci�n, devolvemos el rect�ngulo dentro del bitmap que representa el gr�fico
	actual a pintar del bichejo*/

	switch(Trajectory->Faced())
	{
		case STOP:	SetRect(rc,256,0,288,32);						break;

		case N:		SetRect(rc,((12+seq)<<5),0,((12+seq+1)<<5),32);	break;
		case S:		SetRect(rc,(( 8+seq)<<5),0,(( 8+seq+1)<<5),32);	break;
		case SE:
		case NE:
		case E:		SetRect(rc,(( 7-seq)<<5),0,(( 7-seq+1)<<5),32);	break;
		case SO:
		case NO:
		case O:		SetRect(rc,     (seq<<5),0,   ((seq+1)<<5),32);	break;
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

void cCritter::GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	//Life dependency not implemented
	SetRect(rc,0,32,32,64);
}

void cCritter::GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	SetRect(rc,shoot_seq<<5,64,(shoot_seq+1)<<5,96);
	switch(shoot_seq)
	{
		case 0:	*posx+=5;	break;
		case 1:	*posx-=2;	break;
		case 2: *posx-=8;	break;
		case 3: *posx-=16;	break;
		case 4: *posx-=24;	break;
		case 5:	*posx-=32;	break;
		case 6: *posx-=32;	break;
		case 7: *posx-=32;	break;
	}
	
	shoot_delay++;
	if(shoot_delay==4)
	{
		shoot_seq++;
		if(shoot_seq==16) shoot_seq=0;
		shoot_delay=0;
	}
}

void cCritter::GetRectRadar(RECT *rc,int *posx,int *posy)
{
	*posx = RADAR_Xo + ( cx << 2 );
	*posy = RADAR_Yo + ( cy << 2 );

	SetRect(rc,80,32,84,36);
}

void cCritter::GoToCell(CTile2D **map,int destcx,int destcy)
{
	// "leave all we're doing"
	attack=false;
	shoot=false;

	// Go
	if(Trajectory->IsDone())	Trajectory->Make(map,cx,cy,destcx,destcy);
	else					Trajectory->ReMake(map,destcx,destcy);
}

void cCritter::GoToEnemy(CTile2D **map,int destcx,int destcy)
{
	//(Only implemented attack right to left)
	GoToCell(map,destcx+1,destcy);

	attack=true;
	shoot=false;
}
void cCritter::Move()
{
	int mov;

	if(!Trajectory->IsDone())
	{
		mov=Trajectory->NextStep(&x,&y,&cx,&cy);

		if(mov==ARRIVE)
		{
			Trajectory->Done();
			seq=0;
			move=false;
		}
		else if(mov==CONTINUE)
		{
			move=true;
		}
	}
	else
	{
		//Moved for attack?
		if(attack)
		{
			shoot=true;
			shoot_seq=0;
			shoot_delay=0;
			attack=false;
		}
	}
}

void cCritter::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cCritter::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cCritter::SetCell(int cellx,int celly)
{
	cx = cellx;
	cy = celly;
}
void cCritter::GetCell(int *cellx,int *celly)
{
	*cellx = cx;
	*celly = cy;
}
void cCritter::SetSelected(bool sel)
{
	selected = sel;
}
bool cCritter::GetSelected()
{
	return selected;
}
bool cCritter::GetShooting()
{
	return shoot;
}
bool cCritter::IsFiring()
{
	return (shoot_seq<8);
}
bool cCritter::IsMoving()
{

	return move;
}

bool cCritter::AlAtaquue(){

return attack;
}

void cCritter::Damage()
{
	//restar� vida, y si es cero, muerto
   Lives--;
}

bool cCritter::IsAlive()
{  //devuelve si est� vivo o no el critter
   //	return vida!=0;
  return Lives != 0;
}

int cCritter::GetLives()
{
	return Lives;
}