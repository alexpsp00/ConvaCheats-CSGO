#include "mouse.h"
#include <windowsx.h> //lParam

cMouse g_Mouse;

cMouse::cMouse()
{
	this->mouse1pressed = false;
	this->mouse1released = false;
	this->mouse2pressed = false;
	this->mouse2released = false;
	this->mousescrollpressed = false;
	this->mousescrollreleased = false;
}

void cMouse::DrawMouse()
{
	if (this->ActiveMouse)
	{
		g_Draw.FillRGBA(pHackMouse.x + 1, pHackMouse.y + 2, 1, 13, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 2, pHackMouse.y + 3, 1, 11, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 3, pHackMouse.y + 4, 1, 9, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 4, pHackMouse.y + 5, 1, 7, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 5, pHackMouse.y + 6, 1, 8, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 6, pHackMouse.y + 7, 1, 9, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 7, pHackMouse.y + 8, 1, 10, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 8, pHackMouse.y + 9, 1, 2, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 9, pHackMouse.y + 10, 1, 1, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 8, pHackMouse.y + 16, 1, 4, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x + 9, pHackMouse.y + 18, 1, 2, 255, 255, 255, 255);
		g_Draw.FillRGBA(pHackMouse.x, pHackMouse.y, 1, 17, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 1, pHackMouse.y + 15, 1, 1, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 2, pHackMouse.y + 14, 1, 1, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 3, pHackMouse.y + 13, 2, 1, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 4, pHackMouse.y + 12, 1, 1, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 5, pHackMouse.y + 14, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 6, pHackMouse.y + 16, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 7, pHackMouse.y + 18, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 8, pHackMouse.y + 20, 2, 1, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 8, pHackMouse.y + 14, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 9, pHackMouse.y + 16, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 10, pHackMouse.y + 18, 1, 2, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 7, pHackMouse.y + 11, 1, 3, 0, 0, 0, 255);
		g_Draw.FillRGBA(pHackMouse.x + 8, pHackMouse.y + 11, 4, 1, 0, 0, 0, 255);
		for (int a = 0; a < 11; a++)
			g_Draw.FillRGBA(pHackMouse.x + a, pHackMouse.y + a, 1, 1, 0, 0, 0, 255);
		GetCursorPos(&pHackMouse);
	}
}

void cMouse::ClickHandler()
{
	if (this->ActiveMouse)
	{
		//handle mouse1
		if (GetAsyncKeyState(VK_LBUTTON))
			mouse1pressed = true;
		else if (!GetAsyncKeyState(VK_LBUTTON))
		{
			if (mouse1pressed)
				mouse1released = true;
			else
				mouse1released = false;

			mouse1pressed = false;
		}

		//handle mouse2
		if (GetAsyncKeyState(VK_RBUTTON))
			mouse2pressed = true;
		else if (!GetAsyncKeyState(VK_RBUTTON))
		{
			if (mouse2pressed)
				mouse2released = true;
			else
				mouse2released = false;

			mouse2pressed = false;
		}
	}
}

bool cMouse::LeftClick(int x, int y, int w, int h)
{
	if (g_Mouse.IsOver(x, y, w, h) && GetAsyncKeyState(VK_LBUTTON))
		return true;
	else
		return false;
}

bool cMouse::OneLeftClick(int x, int y, int w, int h)
{
	if (g_Mouse.IsOver(x, y, w, h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		return true;
	else
		return false;
}

bool cMouse::RightClick(int x, int y, int w, int h)
{
	if (g_Mouse.IsOver(x, y, w, h) && GetAsyncKeyState(VK_RBUTTON))
		return true;
	else
		return false;
}

bool cMouse::OneRightClick(int x, int y, int w, int h)
{
	if (g_Mouse.IsOver(x, y, w, h) && GetAsyncKeyState(VK_RBUTTON) & 1)
		return true;
	else
		return false;
}

bool cMouse::IsOver(int x, int y, int w, int h)
{
	if (pHackMouse.x > x &&
		pHackMouse.x < x + w &&
		pHackMouse.y > y &&
		pHackMouse.y < y + h)
		return true;
	else
		return false;
}


bool cMouse::CheckMouse(bool key, int x, int y, int w, int h)
{
	return (key && pHackMouse.x > x && w + x > pHackMouse.x && pHackMouse.y > y && h + y > pHackMouse.y);
}

bool cMouse::CheckMouse(int x, int y, int w, int h)
{
	return (pHackMouse.x > x && w + x > pHackMouse.x && pHackMouse.y > y && h + y > pHackMouse.y);
}

void cMouse::Drag(bool& bDrag, bool bCheck, bool bDragCheck, int& x, int& y, int& xdif, int& ydif)
{
	if (bCheck)
	{
		if (bDragCheck || (this->mouse1pressed && bDrag))
		{
			if (!bDrag)
				bDrag = true;

			if (xdif == -1 || ydif == -1)
			{
				xdif = pHackMouse.x - x;
				ydif = pHackMouse.y - y;
			}

			x += pHackMouse.x - (xdif + x);
			y += pHackMouse.y - (ydif + y);
		}
		else
		{
			if (bDrag)
				bDrag = false;

			xdif = -1;
			ydif = -1;
		}
	}
}