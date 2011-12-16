#pragma once

#include <windows.h>

#define BUTTON_SIZE_HORIZONTAL  70
#define BUTTON_SIZE_VERTICAL    30

#define DIALOG_STATE_SHOW       1
#define DIALOG_STATE_HIDE       0

#define DIALOG_IMG_SIZE         43
#define DIALOG_IMG_UL_X         0
#define DIALOG_IMG_UL_Y         7
#define DIALOG_IMG_UR_X         44
#define DIALOG_IMG_UR_Y         7
#define DIALOG_IMG_BL_X         0
#define DIALOG_IMG_BL_Y         50
#define DIALOG_IMG_BR_X         44
#define DIALOG_IMG_BR_Y         50

#define DIALOG_IMG_HOR_X        0
#define DIALOG_IMG_HOR_Y        0
#define DIALOG_IMG_HOR_SIZE     5

#define DIALOG_IMG_VERT_X       95
#define DIALOG_IMG_VERT_Y       0
#define DIALOG_IMG_VERT_SIZE    5

#define DIALOG_IMG_BKG_X        81
#define DIALOG_IMG_BKG_Y        0
#define DIALOG_IMG_BKG_SIZE     1

#define DIALOG_BOX_OFFSET       11

class cDialog
{
public:
	cDialog(void);
	~cDialog(void);

	void setPos(int X, int Y);
	void setSize(int X, int Y);
	void getPos(int* x, int* y);
	void getSize(int* x, int* y);

	void getButtonPos(int* x, int* y);

	void setText(char* s);
	void setButtonPos(int X, int Y);

	char* getText();

	void Show();
	void Hide();

	int getState();

	int OnButtonPressed();

private:
	// Posición de la esquina superior izquierda
	int PosX; 
	int PosY;
	// Posición de la esquina inferior derecha
	int PosXFin;
	int PosYFin;

	// Texto que mostrará el diálogo
	char* sText;

	// Posición de los botones;
	int PosXButton;
	int PosYButton;

	// Estado del Dialog
	int DialogState;
	
};

