#pragma once;

#include "main.h"

class cMouse
{

public:
	cMouse();
	bool ActiveMouse;
	bool HideMouse;

	bool mouse1pressed;
	bool mouse1released;
	bool mouse2pressed;
	bool mouse2released;
	bool mousescrollpressed;
	bool mousescrollreleased;

	bool mouse1press;
	bool mouse1hold;
	bool mouse2press;
	bool mouse2hold;

	void DrawMouse();
	void ClickHandler();
	bool LeftClick(int x, int y, int w, int h);
	bool OneLeftClick(int x, int y, int w, int h);
	bool RightClick(int x, int y, int w, int h);
	bool OneRightClick(int x, int y, int w, int h);
	bool IsOver(int x, int y, int w, int h);
	bool CheckMouse(bool Key, int x, int y, int w, int h);
	bool CheckMouse(int x, int y, int w, int h);
	void Drag(bool& bDrag, bool bCheck, bool bDragCheck, int& x, int& y, int& xdif, int& ydif);

	bool bDragged[3];

	POINT pHackMouse;
	int iOldX;
	int iOldY;

	bool bMouseOneHasJustBeenReleased()
	{
		return mouse1released;
	}
};

extern cMouse g_Mouse;