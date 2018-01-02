#include "main.h"

Base::Utils::CVMTHookManager g_pPanelVMT;

void DrawOutline(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_Draw.FillRGBA(x, y, w, 1, r, g, b, a);
	g_Draw.FillRGBA(x, y, 1, h, r, g, b, a);
	g_Draw.FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
	g_Draw.FillRGBA(x, y + h, w, 1, r, g, b, a);
}

CBaseEntity* pLocalz()
{
	return g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
}

void AngleVectors(const Vector &angles, Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	g_Math.sinCos(DEG2RAD(angles.y), &sy, &cy);
	g_Math.sinCos(DEG2RAD(angles.x), &sp, &cp);

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void DrawRecoilCrosshair()
{
	CBaseEntity *pLocal = pLocalz();
	if (!pLocal)
		return;

	// Get the view with the recoil
	Vector ViewAngles;
	g_Valve.pEngine->GetViewAngles(ViewAngles);

	ViewAngles += pLocal->GetPunchAngle() * 2.f;

	// Build a ray going fowards at that angle
	Vector fowardVec;
	AngleVectors(ViewAngles, &fowardVec);
	fowardVec *= 10000;

	// Get ray start / end
	Vector start = pLocal->GetVecOrigin() + pLocal->GetVecViewOffset();

	Vector end = start + fowardVec, endScreen;

	if (g_Valve.WorldToScreen(end, endScreen) && pLocal->isValidPlayer())
	{
		g_Draw.FillRGBA(endScreen.x - 3, endScreen.y - 3, 6, 6, g_CVARS.CvarList[recoilxhair_r], g_CVARS.CvarList[recoilxhair_g], g_CVARS.CvarList[recoilxhair_b], g_CVARS.CvarList[recoilxhair_a]);
		DrawOutline(endScreen.x - 3, endScreen.y - 3, 6, 6, 0, 0, 0, 255);
	}
}

void __stdcall hkdPaintTraverse(unsigned vguiPanel, bool forceRepaint, bool allowForce)
{
	static DWORD dwOriginPaintTraverse = g_pPanelVMT.dwGetMethodAddress(41);

	__asm
	{
		PUSH allowForce;
		PUSH forceRepaint;
		PUSH vguiPanel;
		CALL dwOriginPaintTraverse;
	}

	static bool bDidOnce = false;

	if (!bDidOnce)
	{
		g_Draw.initFont();
		bDidOnce = true;
	}

	const char* pszPanelName = g_Valve.pPanel->GetName(vguiPanel);
	bool isValidPanel = false;

	if (pszPanelName && pszPanelName[0] == 'M' && pszPanelName[3] == 'S' &&
		pszPanelName[9] == 'T' && pszPanelName[12] == 'P')
		isValidPanel = true;

	if (!isValidPanel)
		return;

	int iWidth, iHeight;
	g_Valve.pEngine->GetScreenSize(iWidth, iHeight);
	int iCenterX = iWidth / 2,
		iCenterY = iHeight / 2;

	if (g_Valve.pEngine->IsInGame() || g_Valve.pEngine->IsConnected())
	{
		if (g_CVARS.CvarList[ESPActive] && bLAN_MODE == false)
			g_Draw.doESP();

		if (g_CVARS.CvarList[Crosshair] && bLAN_MODE == false)
		{
			g_Valve.pSurface->DrawSetColor(g_CVARS.CvarList[crosshair_r], g_CVARS.CvarList[crosshair_g], g_CVARS.CvarList[crosshair_b], g_CVARS.CvarList[crosshair_a]);
			g_Valve.pSurface->DrawLine(iCenterX - 10, iCenterY - 10, iCenterX + 10, iCenterY + 10);
			g_Valve.pSurface->DrawLine(iCenterX + 10, iCenterY - 10, iCenterX - 10, iCenterY + 10);
		}

		if (g_CVARS.CvarList[RecoilCrosshair] && bLAN_MODE == false)
			DrawRecoilCrosshair();
	}

	if (bLAN_MODE == false)
	{
		if (GetAsyncKeyState(/*g_CVARS.CvarList[Key_Menu]*/VK_INSERT) & 1)
		{
			if (g_Mouse.ActiveMouse)
			{
				g_Mouse.ActiveMouse = false;
				g_Valve.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1");
			}
			else if (!g_Mouse.ActiveMouse)
			{
				g_Mouse.ActiveMouse = true;
				g_Valve.pEngine->ClientCmd_Unrestricted("cl_mouseenable 0");
			}
		}

		if (g_Mouse.ActiveMouse)
		{
			g_Menu.DrawMenu();
			g_Mouse.DrawMouse();
			g_Mouse.ClickHandler();

			int copy_x, copy_y;
			int copy_w, copy_h;

			g_Menu.GetMenuPos(copy_x, copy_y);
			g_Menu.GetMenuSize(copy_w, copy_h);

			g_Mouse.Drag(g_Mouse.bDragged[0], !g_Menu.IsHandlingItem(), g_Mouse.LeftClick(copy_x, copy_y, copy_w, copy_h), copy_x, copy_y, g_Mouse.iOldX, g_Mouse.iOldY);

			g_Menu.SetMenuPos(copy_x, copy_y);

			if (g_Menu.IsHandlingItem())
				g_Menu.RemoveMenuFlag(FL_DISABLEDRAG);
		}
	}

	//Not working idk why
	if (g_CVARS.CvarList[Key_AimbotToggle])
	{
		if (GetAsyncKeyState(g_CVARS.CvarList[Key_AimbotToggle]) & 1)
			g_CVARS.CvarList[AimbotActive] != g_CVARS.CvarList[AimbotActive];
	}

	if (g_CVARS.CvarList[Key_Triggerbot_Toggle])
	{
		if (GetAsyncKeyState(g_CVARS.CvarList[Key_Triggerbot_Toggle]) & 1)
			g_CVARS.CvarList[TriggerbotActive] != g_CVARS.CvarList[TriggerbotActive];
	}

	if (g_CVARS.CvarList[Key_EspToggle])
	{
		if (GetAsyncKeyState(g_CVARS.CvarList[Key_EspToggle]) & 1)
			g_CVARS.CvarList[ESPActive] != g_CVARS.CvarList[ESPActive];
	}
}