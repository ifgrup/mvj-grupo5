
#include "cGraphicsLayer.h"
#include "cGame.h"
#include "cLog.h"
#include <stdio.h>


cGraphicsLayer::cGraphicsLayer()
{
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
	g_pSprite = NULL;
}

cGraphicsLayer::~cGraphicsLayer(){}

bool cGraphicsLayer::Init(HWND hWnd)
{
	cLog *Log = cLog::Instance();
	HRESULT hr;

	D3DVIEWPORT9 viewPort = { 0, 0, SCREEN_RES_X, SCREEN_RES_Y, 0.0f, 1.0f };

	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if(g_pD3D==NULL)
	{
		Log->Msg("Error creating Direct3D object");
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;	//Efficient page flipping
	d3dpp.BackBufferWidth        = SCREEN_RES_X;
    d3dpp.BackBufferHeight       = SCREEN_RES_Y;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;

	hr = g_pD3D->CreateDevice(	D3DADAPTER_DEFAULT, 
								D3DDEVTYPE_HAL, 
								hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&d3dpp, 
								&g_pD3DDevice );
	if(FAILED(hr))
	{
		Log->Error(hr,"Creating Direct3D device");
		return false;
	}

	// Configure for 2d operations
    hr = g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    hr = g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	hr = g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	if(FAILED(hr))
	{
		Log->Error(hr,"Setting render state");
		return false;
	}

	hr = g_pD3DDevice->SetViewport(&viewPort);
	if(FAILED(hr))
	{
		Log->Error(hr,"Setting viewport");
		return false;
	}

	return true;
}

void cGraphicsLayer::Finalize()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

void cGraphicsLayer::LoadData()
{
	D3DXCreateSprite( g_pD3DDevice, &g_pSprite ); 

	//Main menu
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"main2.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								NULL,NULL,NULL,&texMain);
	//GUI game
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"interfaz.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0xffffffff,NULL,NULL,&texGame);
	//Tiles
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"tiles.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texTiles);
	//Characters
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"characters.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texCharacters);
	//Mouse pointers
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"mouse.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texMouse);
	//Fog of war
	D3DXCreateTextureFromFileEx(g_pD3DDevice, "niebla.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0xffffffff,NULL,NULL,&texFog);
	//Fog of war 2
	D3DXCreateTextureFromFileEx(g_pD3DDevice, "niebla2.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0xffffffff,NULL,NULL,&texVisited);
}

void cGraphicsLayer::UnLoadData()
{
	if(texMain)
	{
		texMain->Release();
		texMain = NULL;
	}
	if(texGame)
	{
		texGame->Release();
		texGame = NULL;
	}
	if(texTiles)
	{
		texTiles->Release();
		texTiles = NULL;
	}
	if(texCharacters)
	{
		texCharacters->Release();
		texCharacters = NULL;
	}
	if(texMouse)
	{
		texMouse->Release();
		texMouse = NULL;
	}
	if(texFog)
	{
		texFog->Release();
		texFog = NULL;
	}
	if(texVisited)
	{
		texVisited->Release();
		texVisited = NULL;
	}
	if(g_pSprite)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}
}

bool cGraphicsLayer::Render(int state,cMouse *Mouse,cScene *Scene,cCritter *Critter,cSkeleton *Skeleton,cEnemy** Enemies)
{
	//HRESULT Draw( LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect,
	//				CONST D3DXVECTOR3 *pCenter,  CONST D3DXVECTOR3 *pPosition,
	//				D3DCOLOR Color);

	g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0 );
	g_pD3DDevice->BeginScene();

		//--- SPRITES ---
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

			switch(state)
			{
				case STATE_MAIN:
								g_pSprite->Draw(texMain,NULL,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF);
								break;

				case STATE_GAME:
								DrawScene(Scene);
								DrawUnits(Scene,Critter,Skeleton,Enemies);
								DrawVisibility(Scene, Critter);
								//Graphic User Interface
								g_pSprite->Draw(texGame,NULL,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF);
								DrawRadar(Scene);
								break;
			}

		g_pSprite->End();

		DrawMouse(Mouse);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

	return true;
}

bool cGraphicsLayer::DrawRadar(cScene *Scene)
{
	RECT rc;
	int x,y,fx,fy;
		//pantx,panty;

	//Tile based map
	fx=Scene->cx+SCENE_WIDTH;
	fy=Scene->cy+SCENE_HEIGHT;

	for(x = 0; x < SCENE_AREA; x++)
	{
		for(y = 0; y < SCENE_AREA; y++)
		{
			int idxTile=(y<<5) + x;
			Scene->GetMiniRect(idxTile, &rc);
			g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3((float)(x * 4 + RADAR_Xo), (float)(y * 4 + RADAR_Yo), 0.0f), 0xFFFFFFFF);
		}
	}

	//Draw radar
	x = RADAR_Xo + (Scene->cx << 2);
	y = RADAR_Yo + (Scene->cy << 2);
	fx = (SCENE_WIDTH<<2) + (RADAR_Xo + (Scene->cx<<2));
	fy = (SCENE_HEIGHT<<2) + (RADAR_Yo + (Scene->cy<<2));


	SetRect(&rc,0,32,4,36); //un cuadrado de 4+4 blanco, para dibujar el rectángulo en el radar

	for(int i = x; i < fx; i++)
	{
		g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3(float(i), float(y), 0.0f), 0xFFFFFFFF);
		g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3(float(i), float(fy), 0.0f), 0xFFFFFFFF);
	}

	for(int j = y; j < fy; j++)
	{
		g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3(float(x), float(j), 0.0f), 0xFFFFFFFF);
		g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3(float(fx), float(j), 0.0f), 0xFFFFFFFF);
	}
	
	return true;
}

bool cGraphicsLayer::DrawScene(cScene *Scene)
{
	RECT rc;
	int x,y,//n,
		fx,fy,
		pantx,panty;

	int miniMapaX = 672;
	int miniMapaY = 60;

	//Tile based map
	fx=Scene->cx+SCENE_WIDTH;
	fy=Scene->cy+SCENE_HEIGHT;

	for(y=Scene->cy;y<fy;y++)
	{
		panty = SCENE_Yo + ((y-Scene->cy)<<5);

		for(x=Scene->cx;x<fx;x++)
		{
			pantx = SCENE_Xo + ((x-Scene->cx)<<5);

			//n = Scene->map[(y<<5)+x]; /*VMH Utilizamos la info del mapa, no la de visibilidad*/
			/***VMH*/
			int idxTile=(y<<5)+x;

			//n=Scene->getTileType(idxTile); //VMH new version
			Scene->GetRect(idxTile,&rc);

			g_pSprite->Draw(texTiles,&rc,NULL, 
						&D3DXVECTOR3(float(pantx),float(panty),0.0f), 
						0xFFFFFFFF);
		}
	}

		for(x = 0; x < SCENE_AREA; x++)
		{
			for(y = 0; y < SCENE_AREA; y++)
			{
				int idxTile=(y<<5) + x;
				Scene->GetMiniRect(idxTile, &rc);
				g_pSprite->Draw(texTiles, &rc, NULL, &D3DXVECTOR3((float)(x * 4 + RADAR_Xo), (float)(y * 4 + RADAR_Yo), 0.0f), 0xFFFFFFFF);
			}
		}

	//Draw radar
	x=RADAR_Xo+(Scene->cx<<2);
	y=RADAR_Yo+(Scene->cy<<2);
	SetRect(&rc,0,32,80,100);
	g_pSprite->Draw(texTiles,&rc,NULL, 
					&D3DXVECTOR3(float(x),float(y),0.0f), 
					0xFFFFFFFF);
	return true;
}

bool cGraphicsLayer::DrawVisibility(cScene *Scene, cCritter *Critter)
{
	RECT rcScene, rcVisible;
	int x,y,//n,
		fx,fy,
		pantx,panty;
	int critPosX, critPosY;
	bool bPintar = true;
	int cxinit   = 0;
	int cxfin    = 0;
	int cyinit   = 0;
	int cyfin    = 0;

	//Tile based map
	fx = Scene->cx + SCENE_WIDTH;
	fy = Scene->cy + SCENE_HEIGHT;
	
	SetRect(&rcVisible, 32, 32, 64, 64);

	for(y = Scene->cy; y < fy; y++)
	{
		panty = SCENE_Yo + ((y-Scene->cy)<<5);

		for(x=Scene->cx;x<fx;x++)
		{
			pantx = SCENE_Xo + ((x-Scene->cx)<<5);
			int idxTile=(y<<5)+x;

			Scene->GetRect(idxTile,&rcScene);
			
			if(Scene->IsCellVisited(x,y))
			{
				bPintar = true;
				
				Critter->GetCell(&critPosX, &critPosY);

				cxinit = (critPosX - RADIO_VISIBLE) >= 0 ? critPosX - RADIO_VISIBLE : 0;
				cxfin  = (critPosX + RADIO_VISIBLE) < SCENE_AREA ? critPosX + RADIO_VISIBLE : SCENE_AREA - 1;
				cyinit = (critPosY - RADIO_VISIBLE) >= 0 ? critPosY - RADIO_VISIBLE : 0;
				cyfin  = (critPosY + RADIO_VISIBLE) < SCENE_AREA ? critPosY + RADIO_VISIBLE : SCENE_AREA - 1;

				for(int fila = cyinit; fila <= cyfin; fila++)
				{
					for(int col = cxinit; col <= cxfin; col++)
					{
						if(y == fila && x == col)
						{
							bPintar = false;
							break;
						}
					}
					if(!bPintar)
						break;
				}

				if(bPintar)
				{
					g_pSprite->Draw(texVisited,&rcVisible,NULL, 
							&D3DXVECTOR3(float(pantx),float(panty),0.0f), 
							0xFFFFFFFF);
				}
			}

			// LHA
			if(Scene->IsFogged(x, y))
			{
				SetRect(&rcScene, 0, 0, 64, 64);
				g_pSprite->Draw(texVisited,&rcVisible,NULL, 
							&D3DXVECTOR3(float(pantx),float(panty),0.0f), 
							0xFFFFFFFF);
				g_pSprite->Draw(texFog,&rcScene,NULL, 
							&D3DXVECTOR3(float(pantx-16),float(panty-16),0.0f), 
							0xFFFFFFFF);
			}
		}
	}

	return true;
}

bool cGraphicsLayer::DrawUnits(cScene *Scene,cCritter *Critter,cSkeleton *Skeleton,cEnemy** Enemies)
{
	int cx,cy,posx,posy;
	RECT rc;

	//Draw Critter
	Critter->GetCell(&cx,&cy);
	//VMH: Update visibility in the map. Will be drawn next tic.

	if(Scene->Visible(cx,cy))
	{
		Critter->GetRect(&rc,&posx,&posy,Scene); /*Obtiene del critter, la posición EN PANTALLA donde pintar, y el rectángulo dentro del bitmap que pintar*/
		g_pSprite->Draw(texCharacters,&rc,NULL, 
						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
						0xFFFFFFFF);
		if(Critter->GetSelected())
		{
			Critter->GetRectLife(&rc,&posx,&posy,Scene);
			g_pSprite->Draw(texMouse,&rc,NULL, 
							&D3DXVECTOR3(float(posx),float(posy),0.0f), 
							0xFFFFFFFF);
		}
	}
	Critter->GetRectRadar(&rc,&posx,&posy);
	g_pSprite->Draw(texTiles,&rc,NULL, 
					&D3DXVECTOR3(float(posx),float(posy),0.0f), 
					0xFFFFFFFF);
	//Draw Enemies:
	for (int i=0;i<4;i++)
	{
		cEnemy* bicho=Enemies[i];
		bicho->GetCell(&cx,&cy);
		if(Scene->Visible(cx,cy))
		{
			bicho->GetRect(&rc,&posx,&posy,Scene); /*Obtiene del critter, la posición EN PANTALLA donde pintar, y el rectángulo dentro del bitmap que pintar*/
			g_pSprite->Draw(texCharacters,&rc,NULL, 
						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
						0xFFFFFFFF);
		}
	}
	
	//Draw Skeleton
	Skeleton->GetCell(&cx,&cy);
	if(Scene->IsVisible(cx,cy))
	{
		if(Scene->IsCellActive(cx, cy))
		{
			Skeleton->GetRect(&rc,&posx,&posy,Scene);
			g_pSprite->Draw(texCharacters,&rc,NULL, 
						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
						0xFFFFFFFF);
		}
	}
	Skeleton->GetRectRadar(&rc,&posx,&posy);
	g_pSprite->Draw(texTiles,&rc,NULL, 
					&D3DXVECTOR3(float(posx),float(posy),0.0f), 
					0xFFFFFFFF);
	//Draw Fire
	if(Critter->GetShooting())
	{
		if(Critter->IsFiring())
		{
			//Advance animation & draw
			Critter->GetRectShoot(&rc,&posx,&posy,Scene);
			g_pSprite->Draw(texCharacters,&rc,NULL, 
							&D3DXVECTOR3(float(posx),float(posy),0.0f), 
							0xFFFFFFFF);
		}
		else
		{
			//Advance animation
			Critter->GetRectShoot(&rc,&posx,&posy,Scene);
		}
	}
	return true;
}

bool cGraphicsLayer::DrawMouse(cMouse *Mouse)
{
	RECT rc;
	int mx,my,posx,posy;

	//Mouse selection box
	Mouse->GetPosition(&mx,&my);

	if(Mouse->GetSelection()==SELECT_SCENE)
	{
		int sx,sy;
		Mouse->GetSelectionPoint(&sx,&sy);
		SetRect(&rc,sx,sy,mx,my);
		DrawRect(rc,0x0000ff00);
	}

	//Mouse
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		Mouse->GetRect(&rc,&posx,&posy);
		HRESULT hr = g_pSprite->Draw(texMouse,&rc,NULL,&D3DXVECTOR3(float(mx+posx),float(my+posy),0.0f),0xFFFFFFFF);
		if(FAILED(hr))
		{
			cLog *Log = cLog::Instance();
			Log->Error(hr,"mouse pointer");
			return false;
		}

	g_pSprite->End();

	return true;
}

bool cGraphicsLayer::DrawRect(RECT rc, D3DCOLOR color)
{
	RECT rect;
	int xo,yo,xf,yf;

	if((rc.left==rc.right)&&(rc.top==rc.bottom)) return false;

	if(rc.left < rc.right)
	{
		xo = rc.left;	xf = rc.right;
	}
	else
	{
		xo = rc.right;	xf = rc.left;
	}
	if(rc.top < rc.bottom)
	{
		yo = rc.top;	yf = rc.bottom;
	}
	else
	{
		yo = rc.bottom;	yf = rc.top;
	}

	//Top
	SetRect(&rect,xo,yo,xf+1,yo+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Bottom
	SetRect(&rect,xo,yf,xf,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Left
	SetRect(&rect,xo,yo,xo+1,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Right
	SetRect(&rect,xf,yo,xf+1,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	
	return true;
}