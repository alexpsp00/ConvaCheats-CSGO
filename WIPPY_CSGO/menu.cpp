//#include "menu.h"
//
//cMenu new_Menu("");
//
//void OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
//{
//	g_Draw.FillRGBA(x, y, w, 1, r, g, b, a);
//	g_Draw.FillRGBA(x, y, 1, h, r, g, b, a);
//	g_Draw.FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
//	g_Draw.FillRGBA(x, y + h, w, 1, r, g, b, a);
//}
//
//Position::Position()
//{
//	Init(0, 0);
//	m_flPos[0] = PosX;
//	m_flPos[1] = PosY;
//}
//
//void Position::Init(float x, float y)
//{
//	PosX = x;
//	PosY = y;
//	m_flPos[0] = PosX;
//	m_flPos[1] = PosY;
//}
//
//void Position::PositionCopy(Position src, Position dest)
//{
//	src = dest;
//}
//
//void Position::PositionAdd(Position src, Position add)
//{
//	src.PosX += add.PosX;
//	src.PosY += add.PosY;
//}
//
//cMenu::cMenu(char* Menu_name)
//{
//	bMenuopen = false;
//	pMenuPos.Init(350.0f, 100.0f);
//}
//
//int cMenu::AddEntry(int type, int i, char title[100], float* cvar, float max, float min, float step, char info[100])
//{
//	Item[i].type = type;
//	strcpy(Item[i].title, title);
//	Item[i].cvar = cvar;
//	Item[i].min = min;
//	Item[i].max = max;
//	Item[i].step = step;
//	strcpy(Item[i].info, info);
//	return (i + 1);
//}
//
//int iRed, iGreen, iBlue;
//void GradientVertical(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2)
//{
//	y += 1;
//
//	for (int i = 1; i < h; i++)
//	{
//		iRed = (int)((float)i / h*(r - r2));
//		iGreen = (int)((float)i / h*(g - g2));
//		iBlue = (int)((float)i / h*(b - b2));
//		g_Draw.FillRGBA(x, y + i - 1, w, 1, r - iRed, g - iGreen, b - iBlue, a);
//	}
//}
//
//void GradientHorizontal(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2)
//{
//	for (int i = 1; i < w; i++)
//	{
//		iRed = (int)((float)i / w*(r - r2));
//		iGreen = (int)((float)i / w*(g - g2));
//		iBlue = (int)((float)i / w*(b - b2));
//		g_Draw.FillRGBA(x + i - 1, y, 1, h, r - iRed, g - iGreen, b - iBlue, a);
//	}
//}
//
//void cMenu::InitMenuItems()
//{
//	int i = 0;
//
//	int ScreenW;
//	int ScreenH;
//	g_Valve.pEngine->GetScreenSize(ScreenW, ScreenH);
//
//	if (!Menusection.aimbot_sect)
//	{
//		i = AddEntry(2, i, "[+] Aimbot Settings", &Menusection.aimbot_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.aimbot_sect)
//	{
//		i = AddEntry(2, i, "[-] Aimbot Settings", &Menusection.aimbot_sect, 1, 0, 1, "");
//		i = AddEntry(1, i, "      Enable (0-1)", &g_CVARS.CvarList[AimbotActive], 1, 0, 1, "Enables Master Aimbot");
//		i = AddEntry(1, i, "      Autoshoot (0-1)", &g_CVARS.CvarList[AimbotAutoShoot], 1, 0, 1, "Automatically Fires");
//		i = AddEntry(1, i, "      FOV (0-90)", &g_CVARS.CvarList[AimbotFOV], 90, 0, 1, "Only Target Enemies in this FOV");
//
//		i = AddEntry(1, i, "      Smoothness (0-30)", &g_CVARS.CvarList[AimbotSmooth], 30, 0, 1, "Smoothness of the Aimbot");
//
//		i = AddEntry(1, i, "      RCS (0-2)", &g_CVARS.CvarList[AimbotRCS], 2, 0, 1, "Recoil Control System (2: Enable for Y Angle)");
//		if (g_CVARS.CvarList[AimbotRCS] > 0)
//		{
//			i = AddEntry(1, i, "            RCS Min Distance (0-250)", &g_CVARS.CvarList[AimbotRCSMinDist], 250, 0, 5, "Minimum Distance the RCS will Activate");
//			i = AddEntry(1, i, "            RCS Max Distance (0-250)", &g_CVARS.CvarList[AimbotRCSMaxDist], 250, 0, 5, "Maximum Distance the RCS will Activate");
//
//			i = AddEntry(1, i, "            RCS Scale (0-100)", &g_CVARS.CvarList[AimbotRCSScale], 100, 0, 1, "Scale of the Recoil the RCS will Control (Percentage)");
//		}
//
//		i = AddEntry(1, i, "      Auto Scope (0-1)", &g_CVARS.CvarList[AimbotScope], 1, 0, 1, "Automatically Snopes for Snipers");
//		i = AddEntry(1, i, "      Aimbot On Key (0-163)", &g_CVARS.CvarList[AimbotOnKey], 163, 0, 1, "Activate Aimbot On This Key (For Full Key List : pastebin.com/dc24rLC4)");
//		if (g_CVARS.CvarList[AimbotOnKey] > 1)
//			i = AddEntry(1, i, "            Shoot on Key (0-1)", &g_CVARS.CvarList[AimbotShootOnKey], 1, 0, 1, "Shoot on Aimbot Key");
//
//		i = AddEntry(1, i, "      Min Distance (0-250)", &g_CVARS.CvarList[AimbotMinDist], 250, 0, 5, "Minimum Distance the Aimbot will Activate");
//		i = AddEntry(1, i, "      Max Distance (0-250)", &g_CVARS.CvarList[AimbotMaxDist], 250, 0, 5, "Maximum Distance the Aimbot will Activate");
//		i = AddEntry(1, i, "      WallBang (0-1)", &g_CVARS.CvarList[AimbotWallBang], 1, 0, 1, "Will WallBang Enemies when Possible");
//		i = AddEntry(1, i, "      MultiSpot (0-1)", &g_CVARS.CvarList[AimbotMultiSpot], 1, 0, 1, "Aim At Multiple Spots of the Target Hitbox");
//		if (g_CVARS.CvarList[AimbotMultiSpot] == 1)
//			i = AddEntry(1, i, "                Length (0-15)", &g_CVARS.CvarList[AimbotMultiSpotLength], 15, 0, 1, "Randomized Length of MultiSpot");
//
//		i = AddEntry(1, i, "      Ignore Through Smoke (0-1)", &g_CVARS.CvarList[AimbotIgnoreThroughSmoke], 1, 0, 1, "Will not target Enemies behind Smokegrenades");
//		i = AddEntry(1, i, "      Delay (0-30)", &g_CVARS.CvarList[AimbotDelay], 30, 0, 1, "Delay Before Targetting (Ticks)");
//	}
//
//
//	if (!Menusection.trigger_sect)
//	{
//		i = AddEntry(2, i, "[+] Triggerbot Settings", &Menusection.trigger_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.trigger_sect)
//	{
//		i = AddEntry(2, i, "[-] Triggerbot Settings", &Menusection.trigger_sect, 1, 0, 1, "");
//		i = AddEntry(1, i, "      Enable (0-1)", &g_CVARS.CvarList[TriggerbotActive], 1, 0, 1, "Enables Master Triggerbot");
//		i = AddEntry(1, i, "      Only for Snipers (0-1)", &g_CVARS.CvarList[TriggerbotSniper], 1, 0, 1, "Enable Triggerbot With Snipers Only");
//		i = AddEntry(1, i, "            Only When Scoped (0-1)", &g_CVARS.CvarList[TriggerbotOnlyWhenScoped], 1, 0, 1, "Only Triggerbot When Scoped");
//
//		i = AddEntry(1, i, "      Overburst(0-7)", &g_CVARS.CvarList[TriggerbotOverBurst], 7, 0, 1, "Amount of Shots to Overshoot");
//		i = AddEntry(1, i, "      Trigger On Key (0-163)", &g_CVARS.CvarList[TriggerbotOnKey], 163, 0, 1, "Activate Triggerbot On This Key (For Full Key List : pastebin.com/dc24rLC4)");
//
//		i = AddEntry(1, i, "      Head Only (0-1)", &g_CVARS.CvarList[TriggerbotHead], 1, 0, 1, "Only Enable Triggerbot for Head Hitgroup");
//		i = AddEntry(1, i, "      Ignore Arms and Legs (0-1)", &g_CVARS.CvarList[TriggerbotIgnoreArmsLegs], 1, 0, 1, "Ignores Legs and Arms Hitgroups");
//		i = AddEntry(1, i, "      Delay (0-30)", &g_CVARS.CvarList[TriggerbotDelay], 30, 0, 1, "Delay Before Shooting (Ticks)");
//	}
//
//
//	if (!Menusection.visual_sect)
//	{
//		i = AddEntry(2, i, "[+] Visual Settings", &Menusection.visual_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.visual_sect)
//	{
//		i = AddEntry(2, i, "[-] Visual Settings", &Menusection.visual_sect, 1, 0, 1, "");
//
//		if (!Menusection.visual_esp_sect)
//			i = AddEntry(2, i, "      [+] ESP", &Menusection.visual_esp_sect, 1, 0, 1, "");
//		else if (Menusection.visual_esp_sect)
//		{
//			i = AddEntry(2, i, "      [-] ESP", &Menusection.visual_esp_sect, 1, 0, 1, "");
//			i = AddEntry(1, i, "            Enable (0-1)", &g_CVARS.CvarList[ESPActive], 1, 0, 1, "Enables Master ESP");
//			i = AddEntry(1, i, "            Box (0-1)", &g_CVARS.CvarList[ESPBox], 1, 0, 1, "Displays a 2D Box around Players");
//			i = AddEntry(1, i, "            Name (0-1)", &g_CVARS.CvarList[ESPName], 1, 0, 1, "Displays Player's Names");
//			i = AddEntry(1, i, "            Health (0-1)", &g_CVARS.CvarList[ESPHealth], 1, 0, 1, "Displays Player's Health");
//			i = AddEntry(1, i, "            Distance (0-1)", &g_CVARS.CvarList[ESPDistance], 1, 0, 1, "Displays How far Enemies are Away from You");
//			i = AddEntry(1, i, "            Head (0-1)", &g_CVARS.CvarList[ESPHead], 1, 0, 1, "Displays a '+' over Player's Heads");
//			i = AddEntry(1, i, "            Enemy Only (0-1)", &g_CVARS.CvarList[ESPEnemyOnly], 1, 0, 1, "Only show ESP for Enemies");
//			i = AddEntry(1, i, "            Vis Checks (0-1)", &g_CVARS.CvarList[ESPVisCheck], 1, 0, 1, "Displays Different Colours for Vis/NonVis Players");
//			i = AddEntry(1, i, "            When Vis (0-1)", &g_CVARS.CvarList[ESPWhenVis], 1, 0, 1, "Display ESP when Players are Visible");
//			i = AddEntry(1, i, "            When Not Vis (0-1)", &g_CVARS.CvarList[ESPWhenNotVis], 1, 0, 1, "Display ESP when Players are Not Vis");
//			i = AddEntry(1, i, "            When Behind Smoke (0-1)", &g_CVARS.CvarList[ESPWhenBehindSmoke], 1, 0, 1, "Display ESP when Players are Behind Smoke");
//		}
//		i = AddEntry(1, i, "      Crosshair (0-1)", &g_CVARS.CvarList[Crosshair], 1, 0, 1, "Displays a 'Recoil Square' Crosshair");
//	}
//
//
//	if (!Menusection.others_sect)
//	{
//		i = AddEntry(2, i, "[+] Other Settings", &Menusection.others_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.others_sect)
//	{
//		i = AddEntry(2, i, "[-] Other Settings", &Menusection.others_sect, 1, 0, 1, "");
//		i = AddEntry(1, i, "      Auto Bhop (0-1)", &g_CVARS.CvarList[AutoBhop], 1, 0, 1, "Automatically Bhop");
//		i = AddEntry(1, i, "      Auto Strafe (0-1)", &g_CVARS.CvarList[AutoStrafe], 1, 0, 1, "Automatically Strafes");
//		i = AddEntry(1, i, "      Auto Pistol (0-1)", &g_CVARS.CvarList[AutoPistol], 1, 0, 1, "Makes Pistols Automatic");
//		i = AddEntry(1, i, "      Fov Changer (90-165)", &g_CVARS.CvarList[FOVChanger], 150, 90, 1, "Changes your ingame FOV");
//	}
//
//
//
//	if (!Menusection.skins_sect)
//	{
//		i = AddEntry(2, i, "[+] Skin Changer Settings", &Menusection.skins_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.skins_sect)
//	{
//		i = AddEntry(2, i, "[-] Skin Changer Settings", &Menusection.skins_sect, 1, 0, 1, "");
//		i = AddEntry(1, i, "      Knife (0-9)", &g_CVARS.CvarList[KnifeChanger], 10, 0, 1, "Which Type of Knife");
//		/*if (g_CVARS.CvarList[KnifeChanger] > 0)
//			i = AddEntry(1, i, "            Pattern (0-14)", &g_CVARS.CvarList[KnifePattern], 14, 0, 1, "Which Knife Pattern");*/
//
//		/*i = AddEntry(1, i, "      AWP (0-3)", &g_CVARS.CvarList[AWPChanger], 3, 0, 1, "Which AWP Pattern");*/
//		/*i = AddEntry(5, i, "      Apply Knife", &g_CVARS.CvarList[ApplySkin], 1, 0, 1, "Apply Selected Knife Settings");*/
//	}
//
//
//	if (!Menusection.config_sect)
//	{
//		i = AddEntry(2, i, "[+] Config Settings", &Menusection.config_sect, 1, 0, 1, "");
//	}
//	else if (Menusection.config_sect)
//	{
//		i = AddEntry(2, i, "[-] Config Settings", &Menusection.config_sect, 1, 0, 1, "");
//		i = AddEntry(4, i, "      Save Config", &g_CVARS.CvarList[config1_save], 1, 0, 1, "Save this Configuration");
//		i = AddEntry(3, i, "      Load Config", &g_CVARS.CvarList[config1_load], 1, 0, 1, "Load Saved Configuration");
//	}
//
//	i = AddEntry(1, i, "Autoboot LAN Mode (0-1)", &g_CVARS.CvarList[silent_mode], 1, 0, 1, "Disables ALL Visuals when Re-Injected (Disable this by going into your Config.cfg)");
//
//	i = AddEntry(1, i, "Menu X", &g_CVARS.CvarList[MenuX], ScreenW, 0, 1, "Menu X Position");
//	i = AddEntry(1, i, "Menu Y", &g_CVARS.CvarList[MenuY], ScreenH, 0, 1, "Menu Y Position");
//
//	nMenuitems = i;
//}
//
//void cMenu::DrawMenu()
//{
//	/*if (GetAsyncKeyState(VK_INSERT) & 1)
//		bMenuopen = !bMenuopen;*/
//
//	if (!bMenuopen)
//		return;
//
//	/*if (bMenuopen)*/
//	//KeyHandle();
//
//	int i = nMenuitems;
//
//	int Width = 370;
//
//	GradientVertical(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY] - 15, Width + 1, 15, 30, 90, 120, 255, 30, 100, 150);
//	/*g_Draw.FillRGBA(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY] - 15, Width, 15, 30, 90, 120, 255);*/
//	OutlinedRectangle(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY] - 15, Width, 15, 0, 0, 0, 255);
//
//	g_Draw.DrawStringA(g_Draw.m_MenuFont, true, g_CVARS.CvarList[MenuX] + (Width / 2), g_CVARS.CvarList[MenuY] - 17.50, 245, 155, 23, 255, /*CS:GO Private Hack - ConvaCheats CSGO*/XorStr<0x22, 30, 0xAF6EAC45>("\x61\x70\x1E\x62\x69\x07\x78\x5B\x43\x5D\x4D\x59\x4B\x0F\x78\x50\x51\x58\x14\x18\x16\x60\x71\x69\x6A\x62\x78\x72\x79" + 0xAF6EAC45).s);
//
//	//===============//
//
//	GradientHorizontal(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY], Width + 1, (15 * i), 71, 74, 79, 255, 51, 54, 59);
//	//g_Draw.FillRGBA(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY], Width, (15 * i), 71, 74, 79, 255);
//	OutlinedRectangle(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY], Width, (15 * i), 0, 0, 0, 255);
//
//	for (int i = 0; i < nMenuitems; i++)
//	{
//		if (i == nMenuindex)
//		{
//			g_Draw.FillRGBA(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY] + (15 * i), Width, 15, 20, 50, 110, 255);
//			OutlinedRectangle(g_CVARS.CvarList[MenuX], g_CVARS.CvarList[MenuY] + (15 * i), Width, 15, 0, 0, 0, 255);
//
//			if (!(strcmp(Item[i].info, "") == 0))
//			{
//				int infoWidth = g_Draw.getWidht(g_Draw.m_MenuFont, Item[i].info) + 1;
//				g_Draw.FillRGBA(g_CVARS.CvarList[MenuX] + Width + 2, g_CVARS.CvarList[MenuY] + (15 * i), infoWidth, 15, 0, 0, 0, 165);
//				OutlinedRectangle(g_CVARS.CvarList[MenuX] + Width + 2, g_CVARS.CvarList[MenuY] + (15 * i), infoWidth, 15, 0, 0, 0, 255);
//				g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width + 3, g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 255, 255, 255, Item[i].info);
//			}
//		}
//
//		// type 1 is ON/OFF
//		// type 2 is for sections
//		// type 3/4 is LOAD(D)/SAVE(D)
//
//		if (Item[i].type == 2)
//			g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + 5, g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 255, 120, 255, Item[i].title);
//		else
//			g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + 5, g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 255, 255, 255, Item[i].title);
//
//		if (Item[i].type != 2)
//		{
//			std::string cON = /*ON*/XorStr<0x5A, 3, 0xE1EC7DBF>("\x15\x15" + 0xE1EC7DBF).s;
//			std::string cOFF = /*OFF*/XorStr<0x1F, 4, 0x782EE301>("\x50\x66\x67" + 0x782EE301).s;
//			int ON_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cON.data()) + 5;
//			int OFF_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cOFF.data()) + 5;
//
//			std::string cLOAD = /*LOAD*/XorStr<0x83, 5, 0xE021E510>("\xCF\xCB\xC4\xC2" + 0xE021E510).s;
//			std::string cLOADED = /*LOADED*/XorStr<0xA7, 7, 0x30F552EB>("\xEB\xE7\xE8\xEE\xEE\xE8" + 0x30F552EB).s;
//			std::string cSAVE = /*SAVE*/XorStr<0xC7, 5, 0x558A8AB7>("\x94\x89\x9F\x8F" + 0x558A8AB7).s;
//			std::string cSAVED = /*SAVED*/XorStr<0xAD, 6, 0x9C0AE524>("\xFE\xEF\xF9\xF5\xF5" + 0x9C0AE524).s;
//			int LOAD_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cLOAD.data()) + 5;
//			int LOADED_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cLOADED.data()) + 5;
//			int SAVE_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cSAVE.data()) + 5;
//			int SAVED_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cSAVED.data()) + 5;
//
//			std::string cAPPLY = "APPLY";
//			std::string cAPPLIED = "APPLIED";
//			int APPLY_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cAPPLY.data()) + 5;
//			int APPLIED_Width = g_Draw.getWidht(g_Draw.m_MenuFont, cAPPLIED.data()) + 5;
//
//			if (Item[i].max == 1)
//			{
//				if (Item[i].type == 1)
//				{
//					if (Item[i].cvar[0] == 1)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (ON_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 120, 255, 120, 255, cON.data());
//					else if (Item[i].cvar[0] == 0)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (OFF_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 120, 120, 255, cOFF.data());
//				}
//				else if (Item[i].type == 3)
//				{
//					if (Item[i].cvar[0] == 1)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (LOADED_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 120, 255, 120, 255, cLOADED.data());
//					else if (Item[i].cvar[0] == 0)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (LOAD_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 120, 120, 255, cLOAD.data());
//				}
//				else if (Item[i].type == 4)
//				{
//					if (Item[i].cvar[0] == 1)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (SAVED_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 120, 255, 120, 255, cSAVED.data());
//					else if (Item[i].cvar[0] == 0)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (SAVE_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 120, 120, 255, cSAVE.data());
//				}
//				else if (Item[i].type == 5)
//				{
//					if (Item[i].cvar[0] == 1)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (APPLIED_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 120, 120, 255, 255, cAPPLIED.data());
//					else if (Item[i].cvar[0] == 0)
//						g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (APPLY_Width), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 120, 255, 255, 255, cAPPLY.data());
//				}
//			}
//			else if (Item[i].max > 1)
//			{
//				int valueWidth;
//				//Benny Fixed this
//				if (Item[i].cvar[0] < 10)
//					valueWidth = g_Draw.getWidht(g_Draw.m_MenuFont, /*88*/XorStr<0x43, 3, 0xA8E91589>("\x7B\x7C" + 0xA8E91589).s) + 5;
//				else if (Item[i].cvar[0] >= 10 && Item[i].cvar[0] < 100)
//					valueWidth = g_Draw.getWidht(g_Draw.m_MenuFont, /*88*/XorStr<0xD1, 3, 0x62EA71FA>("\xE9\xEA" + 0x62EA71FA).s) + 5;
//				else if (Item[i].cvar[0] >= 100 && Item[i].cvar[0] < 1000)
//					valueWidth = g_Draw.getWidht(g_Draw.m_MenuFont, /*888*/XorStr<0xC9, 4, 0x9D972AED>("\xF1\xF2\xF3" + 0x9D972AED).s) + 5;
//
//				g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_CVARS.CvarList[MenuX] + Width - (valueWidth), g_CVARS.CvarList[MenuY] + (15 * i) - 4, 255, 255, 255, 255, /*%2.0f*/XorStr<0x16, 6, 0x144B339C>("\x33\x25\x36\x29\x7C" + 0x144B339C).s, Item[i].cvar[0]);
//			}
//		}
//	}
//}
//
//BOOL cMenu::KeyHandle()
//{
//	if (GetAsyncKeyState(VK_UP) & 1)
//	{
//		if (nMenuindex > 0) nMenuindex--;
//		else nMenuindex = nMenuitems - 1;
//		return FALSE;
//	}
//	else if (GetAsyncKeyState(VK_DOWN) & 1)
//	{
//		if (nMenuindex < nMenuitems - 1) nMenuindex++;
//		else nMenuindex = 0;
//		return FALSE;
//	}
//	else if (GetAsyncKeyState(VK_LEFT) & 1)
//	{
//		if (Item[nMenuindex].cvar)
//		{
//			Item[nMenuindex].cvar[0] -= Item[nMenuindex].step;
//			if (Item[nMenuindex].cvar[0] < Item[nMenuindex].min)
//				Item[nMenuindex].cvar[0] = Item[nMenuindex].max;
//		}
//		return FALSE;
//	}
//	else if (GetAsyncKeyState(VK_RIGHT) & 1)
//	{
//		if (Item[nMenuindex].cvar)
//		{
//			Item[nMenuindex].cvar[0] += Item[nMenuindex].step;
//			if (Item[nMenuindex].cvar[0] > Item[nMenuindex].max)
//				Item[nMenuindex].cvar[0] = Item[nMenuindex].min;
//		}
//		return FALSE;
//	}
//
//	return TRUE;
//}