#include "cDialog.h"


// Constructor
cDialog::cDialog(void)
{
	// Inicializamos variables
	PosX = 0;
	PosY = 0;
	PosXFin = 0;
	PosYFin = 0;
	sText = NULL;
	PosXButton = 0;
	PosYButton = 0;
	DialogState = DIALOG_STATE_HIDE;
}

cDialog::~cDialog(void)
{
	if(sText)
		delete sText;
}

void cDialog::setPos(int X, int Y)
{
	PosX = X;
	PosY = Y;
}

void cDialog::setSize(int X, int Y)
{
	PosXFin = X;
	PosYFin = Y;
}

void cDialog::setText(char* s)
{
	int len = strlen(s);

	sText = (char*)malloc(len);
	strcpy(sText, s);
}

char* cDialog::getText()
{
	return sText;
}

void cDialog::setButtonPos(int X, int Y)
{
	PosXButton = X;
	PosYButton = Y;
}

void cDialog::Show()
{
	DialogState = DIALOG_STATE_SHOW;
}

void cDialog::Hide()
{
	DialogState = DIALOG_STATE_HIDE;
}

int cDialog::getState()
{
	return DialogState;
}

int cDialog::OnButtonPressed()
{
	this->Hide();
	return DialogState;
}

void cDialog::getPos(int* x, int* y)
{
	*x = PosX;
	*y = PosY;
}

void cDialog::getSize(int* x, int* y)
{
	*x = PosXFin;
	*y = PosYFin;
}

void cDialog::getButtonPos(int* x, int* y)
{
	*x = PosXButton + PosX;
	*y = PosYButton + PosY;
}