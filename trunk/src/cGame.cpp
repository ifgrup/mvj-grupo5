#include "cGame.h"
#include "cLog.h"

cGame::cGame() {}
cGame::~cGame(){}

#define N_EFECTOS_PANTALLA 4

bool cGame::Init(HWND hWnd,HINSTANCE hInst,bool exclusive)
{
	bool res;
	cLog *Log = cLog::Instance();

	res = Graphics.Init(hWnd);
	if(!res)
	{
		Log->Msg("Error initializing Graphics!");
		return false;
	}

	res = Input.Init(hInst,hWnd,exclusive,USE_MOUSE|USE_KEYBOARD);
	if(!res)
	{
		Log->Msg("Error initializing Input!");
		return false;
	}
	Input.SetMousePosition(SCREEN_RES_X >> 1,SCREEN_RES_Y >> 1);

	Graphics.LoadData();

	Scene.LoadMap("map2.txt");

	//sound 

	//Sound.Init();
	Sound.LoadData();
	
	pDialog = new cDialog();
	pDialog->setPos(200, 100);
	pDialog->setSize(400, 300);
	//pDialog->setButtonPos(180, 290);
	pDialog->setText("ESCAPE FROM ARKHAM!!!\n\nENCUENTRA EL CAMINO A CASA \nHUYENDO DE LOS ENEMIGOS!!\n\nMVJ UPC 2011-2012\n\nGRUPO 5\nLuis Hidalgo\nRoberto Rodriguez\nVictor Martin\n");
	pDialog->Show();

	//Enemies:
	LoadEnemies();

	boton_derecho_nunca_pulsado=true;

	return true;
}

void cGame::Finalize()
{
	Graphics.UnLoadData();
	Graphics.Finalize();
	Input.UnacquireAll();
	Input.Finalize();
}

bool cGame::Loop()
{
	bool res;

	//Input
	res = LoopInput();
	//if(!res) return false;
	
	//Process
	res = LoopProcess();
	if(!res) return false;

	//Output
	res = LoopOutput();
	//if(!res) return false;
	
	return true;
}

bool cGame::LoopInput()
{
	bool res;
	cLog *Log = cLog::Instance();

	res = Input.Read();
	if(!res)
	{
		Log->Msg("Error reading Input!");
		return false;
	}
	return true;
}

bool cGame::LoopProcess()
{
	cMouse *Mouse;
	Mouse = Input.GetMouse();

	switch(state)
	{
		case STATE_MAIN:
		{
			if(Mouse->ButtonDown(LEFT))
			{
				//Play button
				if(Mouse->In(156,488,335,522))
				{
					state = STATE_GAME;
				}
				//Exit button
				else if(Mouse->In(463,488,642,522))
				{
					return false;
				}
			}
			break;
		}
		case STATE_GAME:
		{
			if(pDialog->getState() == DIALOG_STATE_SHOW)
			{
				int x, y;
				pDialog->getButtonPos(&x, &y);
				if(Mouse->In(x, y, x + DIALOG_BUTTON_BR_X, y + DIALOG_BUTTON_BR_Y))
				{
					if(Mouse->ButtonDown(LEFT))
					{
						if(pDialog->OnButtonPressed() == DIALOG_STATE_EXIT)
							PostQuitMessage(0);
					}
				}
			}
			else
			{
				Critter.Move();
				ActualizarIA();
		
				
				//Update Scene //VMH:
				ProcessOrder();
				UpdateScene();
			}
			break;
		}
	}
	return true;
}

bool cGame::LoopOutput()
{
	bool res;
	res = Render();
		res=SoundSistem();
	return res;
}

bool cGame::Render()
{
	bool res;
	res = Graphics.Render(state,Input.GetMouse(),&Scene,&Critter,listEnemies, pDialog);
	return res;
}

bool cGame::SoundSistem()
{
	bool res;
	res=Sound.PlaySoundA(state);
	res=Sound.SoundEffectsUnit(&Critter);
		return res;

}

void cGame::ProcessOrder()
{
	cMouse *Mouse;
	int mx,my,msx,msy,p,cx,cy,x,y;
	int s=10; //marge for directional pointers
	int xo,xf,yo,yf;
	int b4pointer;
	static int release_and_press;
	static int release_and_pressbr;
	int cmx, cmy;

	Mouse = Input.GetMouse();
	b4pointer = Mouse->GetPointer();
	Mouse->GetPosition(&mx,&my);

	if(Mouse->ButtonDown(LEFT))
	{
		Mouse->SetPointer(NORMAL);
		
		if(Mouse->In(SCENE_Xo,SCENE_Yo,SCENE_Xf-s,SCENE_Yf))
		{
			if(Mouse->GetSelection()!=SELECT_SCENE)
			{
				//Select movement/attack
				if(Critter.GetSelected())
				{
					if(release_and_press)
					{
						//Movement
						Mouse->GetCell(&cx,&cy);
						Critter.GoToCell(Scene.getTilesMap(),Scene.cx+cx,Scene.cy+cy);
					}
				}
				//Begin selection
				else
				{
					Mouse->SetSelection(SELECT_SCENE);
					Mouse->SetSelectionPoint(mx,my);
				}
			}
		}
		
		if(Mouse->In(RADAR_Xo,RADAR_Yo,RADAR_Xf,RADAR_Yf))
		{
			if(Critter.GetSelected())
			{
				if(release_and_press)
				{
					int radar_cell_x = (mx-RADAR_Xo) >> 2, //[672..799]/4=[0..31]
						radar_cell_y = (my-RADAR_Yo) >> 2; //[ 60..187]/4=[0..31]

					Critter.GoToCell(Scene.getTilesMap(),radar_cell_x,radar_cell_y);
				}
			}
			else
			{
				Mouse->SetSelection(SELECT_RADAR);
				Scene.MoveByRadar(mx,my);
			}
		}
		release_and_press = false;
	}
	else if(Mouse->ButtonUp(LEFT))
	{
		release_and_press = true;

		if(Mouse->GetSelection()==SELECT_SCENE)
		{
			Mouse->GetSelectionPoint(&msx,&msy);

			xo = min(msx,mx)+(Scene.cx<<5)-SCENE_Xo;
			xf = max(msx,mx)+(Scene.cx<<5)-SCENE_Xo;
			yo = min(msy,my)+(Scene.cy<<5)-SCENE_Yo,
			yf = max(msy,my)+(Scene.cy<<5)-SCENE_Yo;
			
			Critter.GetPosition(&x,&y);
			if((xo<(x+32))&&(xf>=x)&&(yo<(y+32))&&(yf>=y))
				Critter.SetSelected(true);
		}
		Mouse->SetSelection(SELECT_NOTHING);

		//Mouse over Critter
		Critter.GetCell(&cx,&cy);
		if(Mouse->InCell(&Scene,cx,cy))
		{
			Mouse->SetPointer(SELECT);
			return;
		}

		//Mouse
		if(Mouse->In(s,SCENE_Yo+s,SCENE_Xf-s,SCENE_Yf-s))
		{
			//Critter selected pointing, where to move
			if(Critter.GetSelected())	Mouse->SetPointer(MOVE);
			//Critter selected but mouse out map
			else						Mouse->SetPointer(NORMAL);
		}
		else if(Mouse->In(RADAR_Xo,RADAR_Yo,RADAR_Xf,RADAR_Yf))
		{
			//Critter selected pointing, where to move trough radar
			if(Critter.GetSelected())	Mouse->SetPointer(MOVE);
		}
		else
		{	
			//Arrow mouse pointers to move through scene
			if	   (Mouse->In(             s,             s,SCREEN_RES_X-s,SCREEN_RES_Y-s)) Mouse->SetPointer(NORMAL);
			else if(Mouse->In(             s,             0,SCREEN_RES_X-s,             s)) Mouse->SetPointer(MN);
			else if(Mouse->In(             s,SCREEN_RES_Y-s,SCREEN_RES_X-s,  SCREEN_RES_Y)) Mouse->SetPointer(MS);
			else if(Mouse->In(SCREEN_RES_X-s,             s,  SCREEN_RES_X,SCREEN_RES_Y-s)) Mouse->SetPointer(ME);
			else if(Mouse->In(             0,             s,             s,SCREEN_RES_Y-s)) Mouse->SetPointer(MO);
			else if(Mouse->In(             0,             0,             s,             s)) Mouse->SetPointer(MNO);
			else if(Mouse->In(             0,SCREEN_RES_Y-s,             s,  SCREEN_RES_Y)) Mouse->SetPointer(MSO);
			else if(Mouse->In(SCREEN_RES_X-s,             0,  SCREEN_RES_X,             s)) Mouse->SetPointer(MNE);
			else if(Mouse->In(SCREEN_RES_X-s,SCREEN_RES_Y-s,  SCREEN_RES_X,  SCREEN_RES_Y)) Mouse->SetPointer(MSE);
			else																			Mouse->SetPointer(NORMAL);

			p = Mouse->GetPointer();
			if((p>=MN)&&(p<=MSO))	Scene.Move(p);
		}
	}

	if(Mouse->ButtonUp(RIGHT))
	{
		release_and_pressbr=true;
	}
	
	if(Mouse->ButtonDown(RIGHT) && (Critter.GetSelected())) //TILE ARDIENDO
	{
		Mouse->GetCell(&cmx, &cmy);

		if((Scene.IsCellActive(Scene.cx+cmx, Scene.cy+cmy))&&(Scene.IsWalkeableHero(Scene.cx+cmx, Scene.cy+cmy)))
		{
			
			if (boton_derecho_nunca_pulsado)
			{	
				pDialog->setText("\n\nCON EL BOTÓN DERECHO, PRENDES FUEGO\n LA CASILLA!\n\nPERO OJO!NO DURA PARA SIEMPRE!!!\n\nY NO TODOS LOS ENEMIGOS LE TEMEN!!");
				pDialog->Show();
				boton_derecho_nunca_pulsado=false;
			}
			
			Mouse->SetPointer(ATTACK);
			if(release_and_pressbr)
			{
				Sound.Playeffects(1);
				release_and_pressbr=false;
				//Se marca el tile como animado, con el fuego, y además se marca a false el flag de walkability
				Scene.SetFireTile(Scene.cx+cmx,Scene.cy+cmy);
			}
		}
	}

	if(b4pointer!=Mouse->GetPointer()) Mouse->InitAnim();
}


void cGame::UpdateScene()
{
	int cx,cy;
    Critter.GetCell(&cx,&cy);
	Scene.UpdateVisibleZone(cx,cy);
	Scene.IncTickCount();

}
void cGame::UpdateEnemiesTarget(int cx, int cy)
{   //cx, cy are the tiles where the main character is
	//Enemies:
	for (int i=0;i<num_enemies;i++)
	{
		listEnemies[i]->GoToCell(Scene.getTilesMap(),cx,cy); //En lugar de esto,llamar a función de cEnemy, por lectura de mapa tener puntos de control, y que
		//de desplacen al punto de control más cercano respecto al tío no?....
	}
}

void cGame::EfectoPantalla(int idEfecto)
{   
	switch(idEfecto)
	{
		case 1:
			this->Graphics.EfectoTilt();
			break;
	}
}


void cGame::ActualizarIA()
{

	for (int i=0;i<num_enemies;i++)
	{
		int ecx,ecy;//celdas del enemigo
		int ccx,ccy;//celdas del critter
		cEnemy* bicho=listEnemies[i];

		bicho->GetCell(&ecx,&ecy);
		Critter.GetCell(&ccx,&ccy);

		bool bMapaRecargado=false;

		//Reevaluamos estrategia
		int nuevax=-7,nuevay=-7;
		bool nuevo_destino=bicho->NextTarget(ccx, ccy,&nuevax,&nuevay);
		if(nuevo_destino)
			bicho->GoToCell(Scene.getTilesMap(),nuevax,nuevay);


		//Actualizamos Mapas de las trajectorias re-evaluando las walkabilitys
		bicho->RecargaWalkability();
		

		//Control de colisión
		if (ecx==ccx && ecy==ccy)
		{
			listEnemies[i]->GoHome(); //vuelve a su posición inicial
			Critter.Damage(); //Hacer daño al critter
			int i=rand()%N_EFECTOS_PANTALLA;
			EfectoPantalla(1);
			Sound.Playeffects(3);
			if(!Critter.IsAlive())
			{
				pDialog->setText("\n\n\n\\tNO LO CONSEGUISTE!!\n\n\n\t\tGAME OVER!!");
				pDialog->Die();
				pDialog->Show();
			}
		}

		{
			//Se puede mover? sólo si no hay fuego/hielo
			if(!Scene.IsCellFired(ecx,ecy)) //si está en fuego/hielo, se queda parao
				listEnemies[i]->Move();
		}

	}//for enemies
			

}

void cGame::LoadEnemies()
{
	
	//VMH: Reservamos memoria para el resto de info del mapa, sólo para los punteros, el contenido se creará dinámicamente
	
	FILE *f;
	f=fopen("enemies.txt","r");
	int nenemigos=0;
    fscanf(f,"%d",&nenemigos);
	this->num_enemies=nenemigos;
	this->listEnemies=(cEnemy**)new cEnemy*[num_enemies];

	for (int i=0;i<nenemigos;i++)
	{
		int cx,cy,wtipo,stipo;
	    fscanf(f,"%d %d %d %d\n",&cx,&cy,&wtipo,&stipo);
		listEnemies[i]=new cEnemy(cx,cy,(WalkingTypes)wtipo,(StrategyTypes)stipo);
	}

	fclose(f);
}