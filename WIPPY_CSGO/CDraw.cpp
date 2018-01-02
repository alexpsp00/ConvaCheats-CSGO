#define INDEX_PLAYERGLOW 0x1DCC  //1DB8
#define INDEX_DYNAMICPROPGLOW 0xD68
#define INDEX_WEAPONGLOW 0x1648
#define INDEX_C4GLOW 0xD7C
#define INDEX_GRENADE 0xD64
#define M_PI 3.14159265358979323846f

#include "main.h"

CDraw g_Draw;

VOID CDraw::initFont()
{
	g_pSurface = g_Valve.pSurface;

	m_ESPFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_ESPFont, "Courier New", 14.5, FW_DONTCARE, 0, 0, 0x200);

	m_WatermarkFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_WatermarkFont, "Tahoma", 12, FW_BOLD, 0, 0, 0x200 | 0x080);

	m_MenuFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_MenuFont, "Tahoma", 13, FW_BOLD, 0, 0, 0x200 | 0x080);

	m_ListItemFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_ListItemFont, "Visitor TT2 BRK", 13, 500, 0, 0, 0x010);
}

VOID CDraw::DrawString(unsigned long font, int x, int y, int r, int g, int b, const wchar_t *pszText)
{
	if (pszText == NULL)
		return;

	g_Valve.pSurface->DrawSetTextPos(x, y);
	g_Valve.pSurface->DrawSetTextFont(font);
	g_Valve.pSurface->DrawSetTextColor(r, g, b, 255);
	g_Valve.pSurface->DrawPrintText(pszText, wcslen(pszText));
}

std::wstring CDraw::stringToWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

int CDraw::getWidht(unsigned long font, const char* input, ...)
{
	INT iWide = 0;
	INT iTall = 0;
	INT iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

	wchar_t* pszUnicode = new wchar_t[iBufSize];

	MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

	g_Valve.pSurface->GetTextSize(m_MenuFont, pszUnicode, iWide, iTall);

	delete[] pszUnicode;

	return iWide;
}

VOID CDraw::DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	CHAR szBuffer[MAX_PATH];

	if (!input)
		return;

	vsprintf(szBuffer, input, (char*)&input + _INTSIZEOF(input));

	if (center)
		x -= getWidht(font, szBuffer) / 2;

	y += 4;

	g_Valve.pSurface->DrawSetTextColor(r, g, b, a);
	g_Valve.pSurface->DrawSetTextFont(font);
	g_Valve.pSurface->DrawSetTextPos(x, y);
	std::wstring wide = stringToWide(std::string(szBuffer));
	g_Valve.pSurface->DrawPrintText(wide.c_str(), wide.length());
}

void CDraw::FillRGBA(float x, float y, float w, float h, int r, int g, int b, int a)
{
	g_Valve.pSurface->DrawSetColor(r, g, b, a);
	g_Valve.pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void Outline(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_Draw.FillRGBA(x, y, w, 1, r, g, b, a);
	g_Draw.FillRGBA(x, y, 1, h, r, g, b, a);
	g_Draw.FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
	g_Draw.FillRGBA(x, y + h, w, 1, r, g, b, a);
}

char* GetWeaponName(ValveSDK::CBaseCombatWeapon *pWeapon)
{
	int ID = pWeapon->GetWeaponID();

	if (ID == deagle)
		return "deagle";
	else if (ID == p2000)
		return "p2000";
	else if (ID == fiveseven)
		return "fiveseven";
	else if (ID == glock)
		return "glock";
	else if (ID == dualelites)
		return "dualelites";
	else if (ID == ak)
		return "ak47";
	else if (ID == aug)
		return "aug";
	else if (ID == awp)
		return "awp";
	else if (ID == famas)
		return "famas";
	else if (ID == g3sg1)
		return "g3sg1";
	else if (ID == galil)
		return "galil";
	else if (ID == p250)
		return "p250";
	else if (ID == tec9)
		return "tec9";
	else if (ID == m249)
		return "m249";
	else if (ID == m4)
		return "m4a4";
	else if (ID == m4a1s)
		return "m4a1-s";
	else if (ID == mac10)
		return "mac10";
	else if (ID == p90)
		return "p90";
	else if (ID == ump45)
		return "ump45";
	else if (ID == ppbizon)
		return "ppbizon";
	else if (ID == negev)
		return "negev";
	else if (ID == mp7)
		return "mp7";
	else if (ID == mp9)
		return "mp9";
	else if (ID == scar30)
		return "scar20";
	else if (ID == sg553)
		return "sg553";
	else if (ID == ssg08)
		return "scout";
	else if (ID == flashgren)
		return "flashbang";
	else if (ID == hegren)
		return "hegrenade";
	else if (ID == smoke)
		return "smokegrenade";
	else if (ID == molotov)
		return "molotov";
	else if (ID == incendiary)
		return "incendiary";
	else if (ID == decoygren)
		return "decoygrenade";
	else if (ID == bomb)
		return "c4";
	else if (ID == nova)
		return "nova";
	else if (ID == xm1014)
		return "xm1014";
	else if (ID == sawedoff)
		return "sawedoff";
	else if (ID == mag7)
		return "mag7";
	else if (ID == zeus)
		return "zeus";
	else if (ID == usp_s)
		return "usp-s";
	else if (ID == 59)
		return "t knife";
	else if (ID == 42)
		return "ct knife";
	else if (ID == 507)
		return "karambit";
	else if (ID == 500)
		return "bayonet";
	else if (ID == 509)
		return "huntsman";
	else if (ID == 506)
		return "gutknife";
	else if (ID == 516)
		return "shadowdaggers";
	else if (ID == 515)
		return "butterfly";
	else if (ID == 505)
		return "flipknife";
	else if (ID == 508)
		return "m9 bayonet";
	else if (ID == 512)
		return "falchion";
	else if (ID == 514)
		return "bowieknife";
	else
		return "null";
}

VOID DrawESP(CBaseEntity* pLocalEntity, CBaseEntity* pBaseEntity, ValveSDK::CEngineClient::player_info_t pInfo, int r, int g, int b, int a)
{
	Vector vecFootScreen, vFoot;
	if (!g_Valve.WorldToScreen(pBaseEntity->GetAbsOrigin(), vecFootScreen))
		return;

	Vector vHead = pBaseEntity->GetAbsOrigin() + Vector(0, 0, 72.0f);
	if (pBaseEntity->GetFlags() & FL_DUCKING)
		vHead = pBaseEntity->GetAbsOrigin() + Vector(0, 0, 52.0f);

	Vector vHeadScreen;
	if (!g_Valve.WorldToScreen(vHead, vHeadScreen))
		return;

	float h = vecFootScreen.y - vHeadScreen.y;
	float w = (h / 4.0f) * 2.0f;
	float x = vHeadScreen.x - w / 2.0f;
	float y = vHeadScreen.y;

	if (g_CVARS.CvarList[ESPBox])
	{
		Outline(x, y, w, h, r, g, b, a);
		Outline(x - 1, y - 1, w + 2, h + 2, 0, 0, 0, a);
		Outline(x + 1, y + 1, w - 2, h - 2, 0, 0, 0, a);
	}

	int textY = y;
	int above = y - 17;
	if (g_CVARS.CvarList[ESPName])
	{
		g_Draw.DrawStringA(g_Draw.m_WatermarkFont, true, x + w / 2, y - 17, r, g, b, a, pInfo.name);
		above -= 12;
	}
	if (g_CVARS.CvarList[ESPAngles])
	{
		int iX = pBaseEntity->GetEyeAngles().x;
		int iY = pBaseEntity->GetEyeAngles().y;
		g_Draw.DrawStringA(g_Draw.m_WatermarkFont, true, x + w / 2, above, r, g, b, a, "X: %i, Y: %i", iX, iY);
	}

	if (g_CVARS.CvarList[ESPWeapon])
	{
		ValveSDK::CBaseCombatWeapon* pWeapon = pBaseEntity->GetActiveBaseCombatWeapon();
		if (pWeapon)
			g_Draw.DrawStringA(g_Draw.m_WatermarkFont, true, x + w / 2, y + h - 2, r, g, b, a, GetWeaponName(pWeapon));
	}

	if (g_CVARS.CvarList[ESPDistance])
	{
		float flDist = g_Aimbot.GetDistance(pLocalEntity->GetAbsOrigin(), pBaseEntity->GetAbsOrigin());
		g_Draw.DrawStringA(g_Draw.m_WatermarkFont, false, x + w + 4, textY - 5, r, g, b, a, "%2.2fm", flDist);
		textY += 13;
	}
	if (g_CVARS.CvarList[ESPCash])
	{
		g_Draw.DrawStringA(g_Draw.m_WatermarkFont, false, x + w + 4, textY - 5, r, g, b, a, "%i$", pBaseEntity->GetCash());
		textY += 13;
	}


	int nicePos = x - 6;
	if (g_CVARS.CvarList[ESPHealth])
	{
		int CurHealth = pBaseEntity->GetHealth();
		if (CurHealth > 100) CurHealth = 100;

		if (CurHealth >= 1)
		{
			int iHealthHeight = (CurHealth * (h * 0.5 * 0.1) * 0.2);

			g_Draw.FillRGBA(x - 6, y - 1, 3, h + 2, 0, 0, 0, a);
			g_Draw.FillRGBA(x - 6, y - 1, 3, iHealthHeight + 2, r, g, b, a);
			Outline(x - 6, y - 1, 3, h + 2, 0, 0, 0, a);
		}

		nicePos -= 5;
	}

	if (g_CVARS.CvarList[ESPArmor])
	{
		int CurArmor = pBaseEntity->GetArmor();
		if (CurArmor > 100) CurArmor = 100;
		if (CurArmor >= 1)
		{
			int iHealthHeight = (CurArmor * (h * 0.5 * 0.1) * 0.2);

			g_Draw.FillRGBA(nicePos, y - 1, 3, h + 2, 0, 0, 0, 255);
			g_Draw.FillRGBA(nicePos, y - 1, 3, iHealthHeight + 2, 255, 255, 255, 255);
			Outline(nicePos, y - 1, 3, h + 2, 0, 0, 0, 255);
		}

		nicePos -= 5;
	}
}

int r, g, b, a;
VOID CDraw::doESP(void)
{
	Vector vChickenScreen;
	Vector vWeaponScreen;
	for (int i = 0; i < g_Valve.pEntList->GetHighestEntityIndex(); i++)
	{
		if (i == g_Valve.pEngine->GetLocalPlayer())
			continue;

		CBaseEntity* pEntity = g_Valve.pEntList->GetClientEntity(i);

		if (!pEntity
			|| pEntity->IsDormant())
			continue;

		const char* modelName = g_Valve.g_pModel->GetModelName(pEntity->GetModel());

		if (!modelName)
			continue;

		/*if (strstr(modelName, "chicken"))
		{
			if (g_Valve.WorldToScreen(pEntity->GetVecOrigin(), vChickenScreen))
			{
				if (g_CVARS.CvarList[ESPChickens])
					g_Draw.DrawStringA(g_Draw.m_WatermarkFont, true, vChickenScreen.x, vChickenScreen.y, g_CVARS.CvarList[espText_r], g_CVARS.CvarList[espText_g], g_CVARS.CvarList[espText_b], g_CVARS.CvarList[espText_a], "chicken");
			}
		}
		else if (strstr(modelName, "w_"))
		{
			if (g_Valve.WorldToScreen(pEntity->GetVecOrigin(), vWeaponScreen))
			{
				if (g_CVARS.CvarList[ESPChickens])
					g_Draw.DrawStringA(g_Draw.m_WatermarkFont, true, vWeaponScreen.x, vWeaponScreen.y, g_CVARS.CvarList[espText_r], g_CVARS.CvarList[espText_g], g_CVARS.CvarList[espText_b], g_CVARS.CvarList[espText_a], modelName);
			}
		}*/
	}

	if (!g_Valve.pEngine->IsConnected() || !g_Valve.pEngine->IsInGame())
		return;

	CBaseEntity* pLocalEntity = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
	if (!pLocalEntity)
		return;

	for (int i = 1; i < g_Valve.pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pBaseEntity = g_Valve.pEntList->GetClientEntity(i);

		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->isValidPlayer())
			continue;

		if (pBaseEntity->GetIndex() == pLocalEntity->GetIndex())
			continue;

		if (g_CVARS.CvarList[ESPEnemyOnly] && pBaseEntity->GetTeam() == pLocalEntity->GetTeam())
			continue;

		if (!g_CVARS.CvarList[ESPWhenVis] && g_Valve.g_pEngineTraceClient->IsVisible(pLocalEntity, pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition(), pBaseEntity))
			continue;

		if (!g_CVARS.CvarList[ESPWhenNotVis] && !g_Valve.g_pEngineTraceClient->IsVisible(pLocalEntity, pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition(), pBaseEntity))
			continue;

		if (!g_CVARS.CvarList[ESPWhenNotVis] && g_Aimbot.LineGoesThroughSmoke(pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition()))
			continue;

		ValveSDK::CEngineClient::player_info_t info;
		if (!g_Valve.pEngine->GetPlayerInfo(i, &info))
			continue;

		bool bVis = g_Valve.g_pEngineTraceClient->IsVisible(pLocalEntity, pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition(), pBaseEntity);
		if (bVis && g_CVARS.CvarList[ESPVisCheck])
		{
			if (pBaseEntity->GetTeam() == 2)
			{
				r = g_CVARS.CvarList[Tvis_r]; g = g_CVARS.CvarList[Tvis_g]; b = g_CVARS.CvarList[Tvis_b]; a = g_CVARS.CvarList[Tvis_a];
			}
			else if (pBaseEntity->GetTeam() == 3)
			{
				r = g_CVARS.CvarList[CTvis_r]; g = g_CVARS.CvarList[CTvis_g]; b = g_CVARS.CvarList[CTvis_b]; a = g_CVARS.CvarList[CTvis_a];
			}

			if (g_Aimbot.LineGoesThroughSmoke(pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition()))
			{
				if (pBaseEntity->GetTeam() == 2)
				{
					r = g_CVARS.CvarList[Tnotvis_r]; g = g_CVARS.CvarList[Tnotvis_g]; b = g_CVARS.CvarList[Tnotvis_b]; a = g_CVARS.CvarList[Tnotvis_a];
				}
				else if (pBaseEntity->GetTeam() == 3)
				{
					r = g_CVARS.CvarList[CTnotvis_r]; g = g_CVARS.CvarList[CTnotvis_g]; b = g_CVARS.CvarList[CTnotvis_b]; a = g_CVARS.CvarList[CTnotvis_a];
				}
			}
		}
		else
		{
			if (pBaseEntity->GetTeam() == 2)
			{
				r = g_CVARS.CvarList[Tnotvis_r]; g = g_CVARS.CvarList[Tnotvis_g]; b = g_CVARS.CvarList[Tnotvis_b]; a = g_CVARS.CvarList[Tnotvis_a];
			}
			else if (pBaseEntity->GetTeam() == 3)
			{
				r = g_CVARS.CvarList[CTnotvis_r]; g = g_CVARS.CvarList[CTnotvis_g]; b = g_CVARS.CvarList[CTnotvis_b]; a = g_CVARS.CvarList[CTnotvis_a];
			}
		}

		if (g_CVARS.CvarList[ESPHead])
		{
			Vector vBones[19];
			for (int iBone = 0; iBone < 15; iBone++)
			{
				Vector vPlayer;
				g_Aimbot.GetHitbox(vPlayer, iBone, i);
				g_Valve.WorldToScreen(vPlayer, vBones[iBone]);
			}
			g_Draw.FillRGBA(vBones[10].x - 3, vBones[10].y - 3, 6, 6, r, g, b, a);
			Outline(vBones[10].x - 3, vBones[10].y - 3, 6, 6, 0, 0, 0, a);
		}

		if (g_CVARS.CvarList[ESPActive])
			DrawESP(pLocalEntity, pBaseEntity, info, r, g, b, a);
	}
}