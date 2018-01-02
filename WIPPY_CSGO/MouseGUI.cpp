#include "main.h"

cMenu g_Menu(300, 200, 445, NULL);
cListItem ListItemArray[NUM_OF_TOTAL_LISTITEMS];

bool bSliderFix[50];

int iSliderIndex = -1;
int iCurrSlider;

//getasynckeystate fixing...
DWORD dwWait;

//55,128,73

//menu colors (format: RGBA)
#define COLOR1 60, 60, 60, 255
#define COLOR2 85, 85, 85, 255
#define COLOR3 0, 0, 0, 255
#define COLOR4 45, 45, 45, 195
#define COLOR5 50, 50, 50, 255
#define COLOR6 100, 100, 100, 255
#define COLOR7 73, 73, 73, 255
#define COLOR8 65, 65, 65, 255
#define COLOR9 140, 0, 0, 255
#define COLOR10 80, 0, 0, 255

#define COLOR_CFG_POINTERS COLOR1
#define COLOR_CFG_POINTERS_BORDER 140, 0, 0, 255

#define TEXTCOLOR1 180, 0, 0, 255

#define LISTITEM_TEXTCOLOR g_CVARS.CvarList[MenuText_r], g_CVARS.CvarList[MenuText_g], g_CVARS.CvarList[MenuText_b], g_CVARS.CvarList[MenuText_a]

#define ELEMENT_SEPERATION 30
#define CHECKBOX_SEPERATION_FROM_TEXT 100
#define CHECKBOX_SIZE 13

#define ADDER_SIZE 12
#define ADDER_SEPERATE_FROM_BOXES 40 

#define DEFAULT_X_TO_ADD (CHECKBOX_SEPERATION_FROM_TEXT + CHECKBOX_SIZE + 40)
#define SLIDER_X_TO_ADD 40

#define DROPDOWN_WIDTH 16 * 5
#define DROPDOWN_HEIGHT 16

#define BUTTON_WIDTH 60
#define BUTTON_HEIGHT 30

cMenu::cMenu(int x, int y, int w, int h)
{
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
}

char *pszChatNames[] = { "Disabled", "Normal", "Random" };
float fChatValues[] = { 0, 1, 2 };

char *pszRadioNames[] = { "Disabled", "Thanks", "Getout" };
float fRadioValues[] = { 0, 1, 2 };

char *pszAAXNames[] = { "Disabled", "Down", "Fake Down", "Emotion", "Angel Down", "Angel Up", "Fake Angel" };
float fAAXValues[] = { 0, 1, 2, 3, 4, 5, 6 };

char *pszAAYNames[] = { "Disabled", "Backward", "Fake Back", "Jtter", "Jitter Synced", "Sideway", "Fake Forward", "Slow Spin", "Fast Spin", "Angel Backward", "Angel Inverse", "Angel Spin", "Angel Fake Spin", "Fake Angel" };
float fAAYValues[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

char *pszConfigNames[] = { "Legit", "Rage", "HackvsHack" };
float fConfigValues[] = { 0, 1, 2 };

char *pszKnifeNames[] = { "Default", "Bayonet", "Butterfly", "FlipKnife", "GutKnife", "Karambit", "M9 Bayonet", "Hunstman", "Falchion", "ShadowD", "BowieKnife" };
float fKnifeValues[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char *pszKnifeNames2[] = { "Vanilla", "Fade", "Damascus", "DopplerPH1", "DopplerPH2", "DopplerPH3", "Doppler Ruby", "Doppler Sapphire", "Doppler Bl. Pearl", "Marble Fade", "Tigertooth", "Ultra Violet", "Crimsom Web", "Slaughter", "Night" };
float fKnifeValues2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

char *pszESPColors[] = { "CT Vis", "CT Not Vis", "T Vis", "T Not Vis" };
float fESPColors[] = { 0, 1, 2, 3 };

char *pszVISUALColors[] = { "Crosshair", "Recoil XHair" };
float fVISUALColors[] = { 0, 1 };

char *pszMENUColors[] = { "Text", "Border", "Background1", "Background2", "Buttons", "Button Hover", "Item Gradient1", "Item Gradient2", "Item Hover Grad1", "Item Hover Grad2", "Slider Dragger", "Seperator" };
float fMenuColors[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

char *pszAWPchanger[] = { "Disabled", "Dragon Lore", "Medusa", "Asiimov" };
float fAWPchanger[] = { 0, 344, 446, 279 };

char *pszAK47changer[] = { "Disabled", "Fire Serpent", "Vulcan", "Aquamarine Revenge" };
float fAK47changer[] = { 0, 180, 302, 474 };



static bool AimbotKey = false;
static bool AimbotKey2 = false;
static bool TriggerKey = false;
static bool TriggerKey2 = false;
static bool ESPKey = false;
static bool MenuKey = false;
static bool PanicKey = false;
static bool AirStuckKey = false;

void SoftOutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	//top
	g_Draw.FillRGBA(x + 2, y, w - 3, 1, r, g, b, a);
	g_Draw.FillRGBA(x + 1, y + 1, 1, 1, r, g, b, a);

	//left
	g_Draw.FillRGBA(x, y + 2, 1, h - 3, r, g, b, a);
	g_Draw.FillRGBA(x + 1, y + h - 1, 1, 1, r, g, b, a);

	//right
	g_Draw.FillRGBA(x + w, y + 2, 1, h - 3, r, g, b, a);
	g_Draw.FillRGBA(x + w - 1, y + 1, 1, 1, r, g, b, a);

	//bottom
	g_Draw.FillRGBA(x + 2, y + h, w - 3, 1, r, g, b, a);
	g_Draw.FillRGBA(x + w - 1, y + h - 1, 1, 1, r, g, b, a);
}

void OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_Draw.FillRGBA(x, y, w, 1, r, g, b, a);
	g_Draw.FillRGBA(x, y, 1, h, r, g, b, a);
	g_Draw.FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
	g_Draw.FillRGBA(x, y + h, w, 1, r, g, b, a);
}

int preview_r, preview_g, preview_b, preview_a;
void cMenu::InitMenuElements()
{
	//all menu sections
	static cMenuSection msAimbot;
	/*static cMenuSection msAimbotSliders;*/

	static cMenuSection msVisuals;
	static cMenuSection msVisualsSliders;

	static cMenuSection msMisc;
	static cMenuSection msMiscSliders;

	static cMenuSection msKeys;
	/*static cMenuSection msKeysSliders;*/

	static cMenuSection msColours;

	int iRowTwo = 140;
	int iRowThree = 140 * 2;
	int iRowFour = 140 * 3;

	//the usual x position for sections/itemlists
	int iUsualX = m_x + 10;
	int iListY = m_y + 75;

	//playerlist stuff
	static bool bDoOnce = true;
	static int iPlayerIndex;
	static float fResetHandle;
	std::string sCurrPlayer;

	//blabla
	iCurrSlider = 0;

	static bool bEmpty;
	static int iEmpty;

	switch (GetTabIndex())
	{
	case AIMBOTTAB:

		msAimbot.ClearSection();
		/*msAimbotSliders.ClearSection();*/

		//----------------------------
		msAimbot.Draw(iUsualX + 5, iListY, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, m_y + 79, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msAimbot.AddElement(ONOFF, 0, "Enable", "", &g_CVARS.CvarList[AimbotActive], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "Auto Fire", "", &g_CVARS.CvarList[AimbotAutoShoot], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "On Key", "", &g_CVARS.CvarList[AimbotOnKey], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "Silent Aim", "", &g_CVARS.CvarList[AimbotSilent], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "Limit Recoil", "", &g_CVARS.CvarList[AimbotLimitRecoil], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "No Recoil", "", &g_CVARS.CvarList[AimbotNoRecoil], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();

		msAimbot.AddElement(ONOFF, iRowTwo, "Recoil Control", "", &g_CVARS.CvarList[AimbotRCS], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Shoot On Key", "", &g_CVARS.CvarList[AimbotShootOnKey], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Auto Scope", "", &g_CVARS.CvarList[AimbotScope], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Team Aim", "", &g_CVARS.CvarList[AimbotTeamAim], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Ignore Jump", "", &g_CVARS.CvarList[AimbotIgnoreJumpers], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Auto AWP", "", &g_CVARS.CvarList[AimbotAutoAWP], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();

		msAimbot.AddElement(ONOFF, iRowThree, "Auto Wall", "", &g_CVARS.CvarList[AimbotWallBang], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "ThirdPerson AA", "", &g_CVARS.CvarList[/*AimbotIgnoreThroughSmoke*/ThirdPerson], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "Multi Spot", "", &g_CVARS.CvarList[AimbotMultiSpot], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "Anti DM", "", &g_CVARS.CvarList[AimbotAntiDM], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "Auto Stop", "", &g_CVARS.CvarList[AimbotAutoStop], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "Auto Crouch", "", &g_CVARS.CvarList[AimbotAutoCrouch], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();



		msAimbot.Draw(iUsualX + 5, iListY + 85 + 69, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 69, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msAimbot.AddElement(ONOFF, 0, "Triggerbot", "", &g_CVARS.CvarList[TriggerbotActive], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, 0, "On Key", "", &g_CVARS.CvarList[TriggerbotOnKey], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();

		msAimbot.AddElement(ONOFF, iRowTwo, "Head Only", "", &g_CVARS.CvarList[TriggerbotHead], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowTwo, "Ignore Limbs", "", &g_CVARS.CvarList[TriggerbotIgnoreArmsLegs], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();

		msAimbot.AddElement(ONOFF, iRowThree, "Only Sniper", "", &g_CVARS.CvarList[TriggerbotSniper], 0, 1, 1, 0, 0, bEmpty);
		msAimbot.AddElement(ONOFF, iRowThree, "Only Scoped", "", &g_CVARS.CvarList[TriggerbotOnlyWhenScoped], 0, 1, 1, 0, 0, bEmpty);

		msAimbot.RestartSection();



		msAimbot.Draw(iUsualX + 5, iListY + 83 + 65 + 69, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 65 + 69, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Field of View", "", &g_CVARS.CvarList[AimbotFOV], 0, 360, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Smoothness", "", &g_CVARS.CvarList[AimbotSmooth], 0, 35, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Min Dist", "", &g_CVARS.CvarList[AimbotMinDist], 0, 500, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Max Dist", "", &g_CVARS.CvarList[AimbotMaxDist], 0, 500, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "RCS Scale", "", &g_CVARS.CvarList[AimbotRCSScale], 0, 100, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "RCS Min Dist", "", &g_CVARS.CvarList[AimbotRCSMinDist], 0, 500, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "RCS Max Dist", "", &g_CVARS.CvarList[AimbotRCSMaxDist], 0, 500, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "M.Spot Length", "", &g_CVARS.CvarList[AimbotMultiSpotLength], 0, 10, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Overburst", "", &g_CVARS.CvarList[TriggerbotOverBurst], 0, 15, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Trigger Delay", "", &g_CVARS.CvarList[TriggerbotDelay], 0, 10, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Limit Recoil Max", "", &g_CVARS.CvarList[LimitRecoilMax], 0, 100, 1, 0, 1, bEmpty);
		msAimbot.SetSlider(iCurrSlider, true);
		msAimbot.AddElement(SLIDER, 0, "Limit R. Delay", "", &g_CVARS.CvarList[LimitRecoilDelay], 0, 10, 1, 0, 1, bEmpty);

		msAimbot.RestartSection();


		m_h = 573;
		g_Draw.FillRGBA(m_x + 10, m_y + m_h - 16, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);


		break;

	case VISUALSTAB:

		msVisuals.ClearSection();
		/*msVisualsSliders.ClearSection();*/

		//----------------------------
		msVisuals.Draw(iUsualX + 5, iListY, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, m_y + 79, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msVisuals.AddElement(ONOFF, 0, "Enable ESP", "", &g_CVARS.CvarList[ESPActive], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, 0, "Name", "", &g_CVARS.CvarList[ESPName], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, 0, "Health", "", &g_CVARS.CvarList[ESPHealth], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, 0, "Weapon", "", &g_CVARS.CvarList[ESPWeapon], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, 0, "Account", "", &g_CVARS.CvarList[ESPCash], 0, 1, 1, 0, 0, bEmpty);

		msVisuals.RestartSection();

		msVisuals.AddElement(ONOFF, iRowTwo, "2D Box", "", &g_CVARS.CvarList[ESPBox], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowTwo, "Distance", "", &g_CVARS.CvarList[ESPDistance], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowTwo, "Head", "", &g_CVARS.CvarList[ESPHead], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowTwo, "Armor", "", &g_CVARS.CvarList[ESPArmor], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowTwo, "Angles", "", &g_CVARS.CvarList[ESPAngles], 0, 1, 1, 0, 0, bEmpty);

		msVisuals.RestartSection();

		msVisuals.AddElement(ONOFF, iRowThree, "Visible Check", "", &g_CVARS.CvarList[ESPVisCheck], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowThree, "When Visible", "", &g_CVARS.CvarList[ESPWhenVis], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowThree, "When Not Vis", "", &g_CVARS.CvarList[ESPWhenNotVis], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowThree, "Enemy Only", "", &g_CVARS.CvarList[ESPEnemyOnly], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, iRowThree, "Entities", "", &g_CVARS.CvarList[ESPChickens], 0, 1, 1, 0, 0, bEmpty);

		msVisuals.RestartSection();


		msVisuals.Draw(iUsualX + 5, iListY + 85 + 46, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 46, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msVisuals.AddElement(ONOFF, 0, "Crosshair", "", &g_CVARS.CvarList[Crosshair], 0, 1, 1, 0, 0, bEmpty);
		msVisuals.AddElement(ONOFF, 0, "Recoil XHair", "", &g_CVARS.CvarList[RecoilCrosshair], 0, 1, 1, 0, 0, bEmpty);

		msVisuals.RestartSection();

		msVisuals.AddElement(ONOFF, iRowTwo, "No Vis Recoil", "", &g_CVARS.CvarList[NoVisualRecoil], 0, 1, 1, 0, 0, bEmpty);

		msVisuals.RestartSection();


		m_h = 300;
		g_Draw.FillRGBA(m_x + 10, m_y + m_h - 16, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);


		break;

	case MISCTAB:

		msMisc.ClearSection();
		/*msMiscSliders.ClearSection();*/

		//----------------------------
		msMisc.Draw(iUsualX + 5, iListY, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, m_y + 79, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msMisc.AddElement(ONOFF, 0, "Auto Bhop", "", &g_CVARS.CvarList[AutoBhop], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, 0, "Auto Strafe", "", &g_CVARS.CvarList[AutoStrafe], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, 0, "Auto Pistol", "", &g_CVARS.CvarList[AutoPistol], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		msMisc.AddElement(ONOFF, iRowTwo, "Anti AUTH", "", &g_CVARS.CvarList[AntiAUTH], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowTwo, "Safe Mode", "", &g_CVARS.CvarList[SafeMode], 0, 1, 1, 0, 0, bEmpty);
		//msMisc.AddElement(ONOFF, iRowTwo, "Circle Strafe(F4)", "", &g_CVARS.CvarList[circlestrafe], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		msMisc.AddElement(ONOFF, iRowThree, "Air Stuck", "", &g_CVARS.CvarList[AirStuck], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowThree, "Spinbot", "", &g_CVARS.CvarList[Spinbot], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowThree, "Name Changer", "", &g_CVARS.CvarList[NameStealer], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		msMisc.Draw(iUsualX + 5, iListY + 85 + 46, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 46, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);
		msMisc.SetValueNames(pszChatNames, fChatValues, 3);
		msMisc.AddElement(DROPDOWN, 0, "Chat Spam", "", &g_CVARS.CvarList[ChatSpam], 0, 0, 1, 0, 1, bEmpty);
		msMisc.SetValueNames(pszRadioNames, fRadioValues, 3);
		msMisc.AddElement(DROPDOWN, 0, "Radio Spam", "", &g_CVARS.CvarList[RadioSpam], 0, 0, 1, 0, 1, bEmpty);
		msMisc.PostSection();

		msMisc.RestartSection();

		msMisc.AddElement(ONOFF, iRowThree, "Slow Mode", "", &g_CVARS.CvarList[SlowChatSpam], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowThree, "Slow Mode", "", &g_CVARS.CvarList[SlowRadioSpam], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		msMisc.Draw(iUsualX + 5, iListY + 85 + 92 + 17, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 92 + 17, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		g_Draw.FillRGBA(m_x + 10, m_y + m_h - 16, m_w - 20, 2, 220, 220, 220, 255);//BOTTOM LINE HERE SO IT GOES UNDER DROPDOWN BOXES VVV

		msMisc.AddElement(ONOFF, 0, "Anti-Aim", "", &g_CVARS.CvarList[AntiAim], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		msMisc.AddElement(ONOFF, iRowTwo, "Follow Targets", "", &g_CVARS.CvarList[AntiAimFollowTarget], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		//msMisc.AddElement(ONOFF, iRowThree, "Static Yaw", "", &g_CVARS.CvarList[AntiAimStatic], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowThree, "Fake-Lag", "", &g_CVARS.CvarList[FakeLag], 0, 1, 1, 0, 0, bEmpty);
		msMisc.AddElement(ONOFF, iRowThree, "pSilent Aim", "", &g_CVARS.CvarList[PerfectSilent], 0, 1, 1, 0, 0, bEmpty);

		msMisc.RestartSection();

		/*msMisc.Draw(iUsualX + 5, iListY + 85 + 92 + 180, 0, 0, "");
		msMisc.AddElement(ONOFF, iRowThree, "Stattrak", "", &g_CVARS.CvarList[KnifeStattrak], 0, 1, 1, 0, 0, bEmpty);*/

		msMisc.RestartSection();


		msMisc.Draw(iUsualX + 5, iListY + 85, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);
		msMisc.SetSlider(iCurrSlider, true);
		msMisc.AddElement(SLIDER, 0, "FOV Changer", "", &g_CVARS.CvarList[FOVChanger], 0, 130, 1, 0, 1, bEmpty);
		/*msMisc.ClearSection();*/

		msMisc.RestartSection();

		msMisc.Draw(iUsualX + 5, iListY + 85 + 92 + 88, 0, 0, "");
		/*g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 92 + 92, m_w - 20, 2, 220, 220, 220, 255);*/
		msMisc.SetSlider(iCurrSlider, true);
		msMisc.AddElement(SLIDER, 0, "Fake-Lag Value", "", &g_CVARS.CvarList[FakeLagValue], 0, 13, 1, 0, 1, bEmpty);

		msMisc.RestartSection();

		msMisc.Draw(iUsualX + 5, iListY + 85 + 92 + 41, 0, 0, "");
		msMisc.SetValueNames(pszAAXNames, fAAXValues, 7);
		msMisc.AddElement(DROPDOWN, 0, "Pitch", "", &g_CVARS.CvarList[AntiAimX], 0, 0, 1, 0, 1, bEmpty);
		msMisc.SetValueNames(pszAAYNames, fAAYValues, 10);
		msMisc.AddElement(DROPDOWN, 0, "Yaw", "", &g_CVARS.CvarList[AntiAimY], 0, 0, 1, 0, 1, bEmpty);
		msMisc.PostSection();

		msMisc.RestartSection();

		//msMisc.Draw(iUsualX + 5, iListY + 85 + 227, 0, 0, "");
		//g_Draw.FillRGBA(m_x + 10, (m_y + 79) + 85 + 227, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);
		//msMisc.SetValueNames(pszConfigNames, fConfigValues, 3);
		//msMisc.AddElement(DROPDOWN, 0, "Select Config", "", &g_CVARS.config_select, 0, 0, 1, 0, 1, bEmpty);
		//msMisc.PostSection();



		//if (g_Mouse.IsOver(iUsualX + 258, iListY + 85 + 242, 73, 16))
		//{
		//	g_Draw.FillRGBA(iUsualX + 258, iListY + 85 + 242, 73, 16, g_CVARS.CvarList[MenuTabhover_r], g_CVARS.CvarList[MenuTabhover_g], g_CVARS.CvarList[MenuTabhover_b], g_CVARS.CvarList[MenuTabhover_a]);
		//	if (g_Mouse.LeftClick(iUsualX + 258, iListY + 85 + 242, 73, 16))
		//		g_Settings.SaveConfig();
		//}
		//else
		//	g_Draw.FillRGBA(iUsualX + 258, iListY + 85 + 242, 73, 16, g_CVARS.CvarList[MenuTabselect_r], g_CVARS.CvarList[MenuTabselect_g], g_CVARS.CvarList[MenuTabselect_b], g_CVARS.CvarList[MenuTabselect_a]);
		//OutlinedRectangle(iUsualX + 258, iListY + 85 + 242, 73, 16, COLOR3);
		//g_Draw.DrawStringA(g_Draw.m_MenuFont, true, iUsualX + 258 + (73 / 2), iListY + 85 + 240, LISTITEM_TEXTCOLOR, "Save");



		//if (g_Mouse.IsOver(iUsualX + 258 + 80, iListY + 85 + 242, 73, 16))
		//{
		//	g_Draw.FillRGBA(iUsualX + 258 + 80, iListY + 85 + 242, 73, 16, g_CVARS.CvarList[MenuTabhover_r], g_CVARS.CvarList[MenuTabhover_g], g_CVARS.CvarList[MenuTabhover_b], g_CVARS.CvarList[MenuTabhover_a]);
		//	if (g_Mouse.LeftClick(iUsualX + 258 + 80, iListY + 85 + 242, 73, 16))
		//		g_Settings.LoadConfig();
		//}
		//else
		//	g_Draw.FillRGBA(iUsualX + 258 + 80, iListY + 85 + 242, 73, 16, g_CVARS.CvarList[MenuTabselect_r], g_CVARS.CvarList[MenuTabselect_g], g_CVARS.CvarList[MenuTabselect_b], g_CVARS.CvarList[MenuTabselect_a]);
		//OutlinedRectangle(iUsualX + 258 + 80, iListY + 85 + 242, 73, 16, COLOR3);
		//g_Draw.DrawStringA(g_Draw.m_MenuFont, true, iUsualX + 258 + 80 + (73 / 2), iListY + 85 + 240, LISTITEM_TEXTCOLOR, "Load");


		//msMisc.RestartSection();

		//msMisc.Draw(iUsualX + 5, iListY + 85 + 92 + 180, 0, 0, "");
		//g_Draw.FillRGBA(iUsualX + 5, iListY + 85 + 92 + 180, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		///*msMisc.SetValueNames(pszKnifeNames, fKnifeValues, 11);
		//msMisc.AddElement(DROPDOWN, 0, "Knife Changer", "", &g_CVARS.CvarList[KnifeChanger], 0, 0, 1, 0, 1, bEmpty);
		//msMisc.SetValueNames(pszKnifeNames2, fKnifeValues2, 14);
		//msMisc.AddElement(DROPDOWN, 0, "Knife Skin", "", &g_CVARS.CvarList[KnifePattern], 0, 0, 1, 0, 1, bEmpty);
		//msMisc.PostSection();

		//msMisc.SetValueNames(pszAWPchanger, fAWPchanger, 4);
		//msMisc.AddElement(DROPDOWN, 0, "AWP Changer", "", &g_CVARS.CvarList[AWPChanger], 0, 0, 1, 0, 1, bEmpty);
		//msMisc.SetValueNames(pszAK47changer, fAK47changer, 4);
		//msMisc.AddElement(DROPDOWN, 0, "AK47 Changer", "", &g_CVARS.CvarList[AK47Changer], 0, 0, 1, 0, 1, bEmpty);*/

		msMisc.PostSection();

		msMisc.RestartSection();


		msMisc.RestartSection();


		msMisc.RestartSection();
		msMisc.PostSection();
		m_h = 400;

		break;

	case KEYBINDS:

		msKeys.ClearSection();
		/*msKeysSliders.ClearSection();*/

		//----------------------------
		msKeys.Draw(iUsualX + 5, iListY, 0, 0, "");
		g_Draw.FillRGBA(m_x + 10, m_y + 79, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		msKeys.AddElement(KEYBIND, 0, "Aimbot Key", "", &g_CVARS.CvarList[Key_Aimbot], 0, 1, 1, 0, 0, AimbotKey);
		msKeys.AddElement(KEYBIND, 0, "Aimbot Toggle Key", "", &g_CVARS.CvarList[Key_AimbotToggle], 0, 1, 1, 0, 0, AimbotKey2);
		msKeys.AddElement(KEYBIND, 0, "Triggerbot Key", "", &g_CVARS.CvarList[Key_Triggerbot], 0, 1, 1, 0, 0, TriggerKey);
		msKeys.AddElement(KEYBIND, 0, "Triggerbot Toggle Key", "", &g_CVARS.CvarList[Key_Triggerbot_Toggle], 0, 1, 1, 0, 0, TriggerKey2);
		msKeys.AddElement(KEYBIND, 0, "ESP Toggle Key", "", &g_CVARS.CvarList[Key_EspToggle], 0, 1, 1, 0, 0, ESPKey);
		msKeys.AddElement(KEYBIND, 0, "Menu Key", "", &g_CVARS.CvarList[Key_Menu], 0, 1, 1, 0, 0, MenuKey);
		msKeys.AddElement(KEYBIND, 0, "Panic Key", "", &g_CVARS.CvarList[key_Panic], 0, 1, 1, 0, 0, PanicKey);
		msKeys.AddElement(KEYBIND, 0, "Air Stuck Key", "", &g_CVARS.CvarList[Key_Airstuck], 0, 1, 1, 0, 0, AirStuckKey);


		msKeys.RestartSection();


		m_h = 310;
		g_Draw.FillRGBA(m_x + 10, m_y + m_h - 16, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		break;

	case COLORTAB:

		msColours.ClearSection();
		g_Draw.FillRGBA(m_x + 10, m_y + 79, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);
		/*msKeysSliders.ClearSection();*/

		int nice = 109;
		int nice2 = (109);
		int nice3 = (109 * 2);
		g_Draw.FillRGBA(iUsualX - 5, iListY + 13, m_w - 10, 20, g_CVARS.CvarList[MenuBackground2_r], g_CVARS.CvarList[MenuBackground2_g], g_CVARS.CvarList[MenuBackground2_b], g_CVARS.CvarList[MenuBackground2_a]);
		DrawTab(COLOR_VISUAL, iColorIndex, iUsualX + 48, iListY + 13, "Visuals");
		DrawTab(COLOR_ESP, iColorIndex, iUsualX + 48 + nice2, iListY + 13, "ESP");
		DrawTab(COLOR_MENUZ, iColorIndex, iUsualX + 48 + nice3, iListY + 13, "Menu");
		OutlinedRectangle(iUsualX - 5, iListY + 13, m_w - 10, 20, 0, 0, 0, 255);

		g_Draw.FillRGBA(iUsualX + 5, iListY + 170, m_w - 30, 70, preview_r, preview_g, preview_b, preview_a);
		OutlinedRectangle(iUsualX + 5, iListY + 170, m_w - 30, 70, 0, 0, 0, 255);

		switch (iColorIndex)
		{
		case COLOR_VISUAL:


			//----------------------------
			msColours.Draw(iUsualX + 5, iListY + 30, 0, 0, "");
			msColours.SetValueNames(pszVISUALColors, fVISUALColors, 2);
			msColours.AddElement(DROPDOWN, 0, "Which Feature", "", &g_CVARS.CvarList[selected_visual_color], 0, 0, 1, 0, 1, bEmpty);
			msColours.RestartSection();

			msColours.Draw(iUsualX + 5, iListY + 55, 0, 0, "");
			if (g_CVARS.CvarList[selected_visual_color] == 0)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[crosshair_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[crosshair_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[crosshair_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[crosshair_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[crosshair_r];
				preview_g = g_CVARS.CvarList[crosshair_g];
				preview_b = g_CVARS.CvarList[crosshair_b];
				preview_a = g_CVARS.CvarList[crosshair_a];
			}
			else if (g_CVARS.CvarList[selected_visual_color] == 1)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[recoilxhair_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[recoilxhair_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[recoilxhair_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[recoilxhair_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[recoilxhair_r];
				preview_g = g_CVARS.CvarList[recoilxhair_g];
				preview_b = g_CVARS.CvarList[recoilxhair_b];
				preview_a = g_CVARS.CvarList[recoilxhair_a];
			}

			msColours.PostSection();

			break;

		case COLOR_ESP:

			msColours.Draw(iUsualX + 5, iListY + 30, 0, 0, "");
			msColours.SetValueNames(pszESPColors, fESPColors, 4);
			msColours.AddElement(DROPDOWN, 0, "Which Feature", "", &g_CVARS.selected_esp_color, 0, 0, 1, 0, 1, bEmpty);

			msColours.Draw(iUsualX + 5, iListY + 55, 0, 0, "");
			if (g_CVARS.selected_esp_color == 0)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[CTvis_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[CTvis_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[CTvis_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[CTvis_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[CTvis_r];
				preview_g = g_CVARS.CvarList[CTvis_g];
				preview_b = g_CVARS.CvarList[CTvis_b];
				preview_a = g_CVARS.CvarList[CTvis_a];
			}
			else if (g_CVARS.selected_esp_color == 1)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[CTnotvis_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[CTnotvis_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[CTnotvis_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[CTnotvis_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[CTnotvis_r];
				preview_g = g_CVARS.CvarList[CTnotvis_g];
				preview_b = g_CVARS.CvarList[CTnotvis_b];
				preview_a = g_CVARS.CvarList[CTnotvis_a];
			}
			else if (g_CVARS.selected_esp_color == 2)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[Tvis_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[Tvis_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[Tvis_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[Tvis_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[Tvis_r];
				preview_g = g_CVARS.CvarList[Tvis_g];
				preview_b = g_CVARS.CvarList[Tvis_b];
				preview_a = g_CVARS.CvarList[Tvis_a];
			}
			else if (g_CVARS.selected_esp_color == 3)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[Tnotvis_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[Tnotvis_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[Tnotvis_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[Tnotvis_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[Tnotvis_r];
				preview_g = g_CVARS.CvarList[Tnotvis_g];
				preview_b = g_CVARS.CvarList[Tnotvis_b];
				preview_a = g_CVARS.CvarList[Tnotvis_a];
			}
			else if (g_CVARS.selected_esp_color == 4)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[Tnotvis_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[Tnotvis_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[Tnotvis_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[Tnotvis_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[Tnotvis_r];
				preview_g = g_CVARS.CvarList[Tnotvis_g];
				preview_b = g_CVARS.CvarList[Tnotvis_b];
				preview_a = g_CVARS.CvarList[Tnotvis_a];
			}

			msColours.PostSection();

			break;

		case COLOR_MENUZ:

			msColours.Draw(iUsualX + 5, iListY + 30, 0, 0, "");
			msColours.SetValueNames(pszMENUColors, fMenuColors, 12);
			msColours.AddElement(DROPDOWN, 0, "Which Part", "", &g_CVARS.selected_esp_color, 0, 0, 1, 0, 1, bEmpty);

			msColours.Draw(iUsualX + 5, iListY + 55, 0, 0, "");
			if (g_CVARS.selected_esp_color == 0)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuText_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuText_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuText_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuText_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuText_r];
				preview_g = g_CVARS.CvarList[MenuText_g];
				preview_b = g_CVARS.CvarList[MenuText_b];
				preview_a = g_CVARS.CvarList[MenuText_a];
			}
			else if (g_CVARS.selected_esp_color == 1)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuBorder_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuBorder_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuBorder_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuBorder_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuBorder_r];
				preview_g = g_CVARS.CvarList[MenuBorder_g];
				preview_b = g_CVARS.CvarList[MenuBorder_b];
				preview_a = g_CVARS.CvarList[MenuBorder_a];
			}
			else if (g_CVARS.selected_esp_color == 2)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuBackground1_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuBackground1_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuBackground1_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuBackground1_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuBackground1_r];
				preview_g = g_CVARS.CvarList[MenuBackground1_g];
				preview_b = g_CVARS.CvarList[MenuBackground1_b];
				preview_a = g_CVARS.CvarList[MenuBackground1_a];
			}
			else if (g_CVARS.selected_esp_color == 3)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuBackground2_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuBackground2_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuBackground2_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuBackground2_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuBackground2_r];
				preview_g = g_CVARS.CvarList[MenuBackground2_g];
				preview_b = g_CVARS.CvarList[MenuBackground2_b];
				preview_a = g_CVARS.CvarList[MenuBackground2_a];
			}
			else if (g_CVARS.selected_esp_color == 4)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuTabselect_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuTabselect_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuTabselect_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuTabselect_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuTabselect_r];
				preview_g = g_CVARS.CvarList[MenuTabselect_g];
				preview_b = g_CVARS.CvarList[MenuTabselect_b];
				preview_a = g_CVARS.CvarList[MenuTabselect_a];
			}
			else if (g_CVARS.selected_esp_color == 5)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuTabhover_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuTabhover_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuTabhover_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuTabhover_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuTabhover_r];
				preview_g = g_CVARS.CvarList[MenuTabhover_g];
				preview_b = g_CVARS.CvarList[MenuTabhover_b];
				preview_a = g_CVARS.CvarList[MenuTabhover_a];
			}
			else if (g_CVARS.selected_esp_color == 6)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuItemGradient1_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuItemGradient1_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuItemGradient1_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuItemGradient1_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuItemGradient1_r];
				preview_g = g_CVARS.CvarList[MenuItemGradient1_g];
				preview_b = g_CVARS.CvarList[MenuItemGradient1_b];
				preview_a = g_CVARS.CvarList[MenuItemGradient1_a];
			}
			else if (g_CVARS.selected_esp_color == 7)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuItemGradient2_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuItemGradient2_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuItemGradient2_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuItemGradient1_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuItemGradient2_r];
				preview_g = g_CVARS.CvarList[MenuItemGradient2_g];
				preview_b = g_CVARS.CvarList[MenuItemGradient2_b];
				preview_a = g_CVARS.CvarList[MenuItemGradient1_a];
			}
			else if (g_CVARS.selected_esp_color == 8)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuItemGradientHover1_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuItemGradientHover1_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuItemGradientHover1_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuItemGradientHover1_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuItemGradientHover1_r];
				preview_g = g_CVARS.CvarList[MenuItemGradientHover1_g];
				preview_b = g_CVARS.CvarList[MenuItemGradientHover1_b];
				preview_a = g_CVARS.CvarList[MenuItemGradientHover1_a];
			}
			else if (g_CVARS.selected_esp_color == 9)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuItemGradientHover2_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuItemGradientHover2_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuItemGradientHover2_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuItemGradientHover1_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuItemGradientHover2_r];
				preview_g = g_CVARS.CvarList[MenuItemGradientHover2_g];
				preview_b = g_CVARS.CvarList[MenuItemGradientHover2_b];
				preview_a = g_CVARS.CvarList[MenuItemGradientHover1_a];
			}
			else if (g_CVARS.selected_esp_color == 10)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuSliderDrag_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuSliderDrag_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuSliderDrag_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuSliderDrag_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuSliderDrag_r];
				preview_g = g_CVARS.CvarList[MenuSliderDrag_g];
				preview_b = g_CVARS.CvarList[MenuSliderDrag_b];
				preview_a = g_CVARS.CvarList[MenuSliderDrag_a];
			}
			else if (g_CVARS.selected_esp_color == 11)
			{
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Red", "", &g_CVARS.CvarList[MenuSeperator_r], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Green", "", &g_CVARS.CvarList[MenuSeperator_g], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Blue", "", &g_CVARS.CvarList[MenuSeperator_b], 0, 255, 1, 0, 1, bEmpty);
				msColours.SetSlider(iCurrSlider, true);
				msColours.AddElement(SLIDER, 0, "Alpha", "", &g_CVARS.CvarList[MenuSeperator_a], 0, 255, 1, 0, 1, bEmpty);
				preview_r = g_CVARS.CvarList[MenuSeperator_r];
				preview_g = g_CVARS.CvarList[MenuSeperator_g];
				preview_b = g_CVARS.CvarList[MenuSeperator_b];
				preview_a = g_CVARS.CvarList[MenuSeperator_a];
			}

			msColours.PostSection();

			break;
		}
		msColours.PostSection();

		m_h = 350;
		g_Draw.FillRGBA(m_x + 10, m_y + m_h - 16, m_w - 20, 2, g_CVARS.CvarList[MenuSeperator_r], g_CVARS.CvarList[MenuSeperator_g], g_CVARS.CvarList[MenuSeperator_b], g_CVARS.CvarList[MenuSeperator_a]);

		break;
	}
}

int iRed, iGreen, iBlue;
void GradientVertical(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2)
{
	y += 1;

	for (int i = 1; i < h; i++)
	{
		iRed = (int)((float)i / h*(r - r2));
		iGreen = (int)((float)i / h*(g - g2));
		iBlue = (int)((float)i / h*(b - b2));
		g_Draw.FillRGBA(x, y + i - 1, w, 1, r - iRed, g - iGreen, b - iBlue, a);
	}
}

void GradientHorizontal(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2)
{
	for (int i = 1; i < w; i++)
	{
		iRed = (int)((float)i / w*(r - r2));
		iGreen = (int)((float)i / w*(g - g2));
		iBlue = (int)((float)i / w*(b - b2));
		g_Draw.FillRGBA(x + i - 1, y, 1, h, r - iRed, g - iGreen, b - iBlue, a);
	}
}

void cMenu::DrawHeaderComment(int e_x, int e_y, const char *pszComment, bool bSlider)
{
	if (g_Mouse.IsOver(e_x, e_y, (bSlider ? 360 : (DEFAULT_X_TO_ADD - 15)), (bSlider ? 18 : 15)))
		g_Draw.DrawStringA(g_Draw.m_ListItemFont, false, m_x + 15, m_y + 7, TEXTCOLOR1, pszComment);
}

int iLoop[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

void cMenu::DrawSmallTab(int index, int &setindex, int x, int y, const char *pszTitle)
{
	static int iWidth = 60;
	static int iHeight = 20;
	bool bOverBack = g_Mouse.IsOver(x, y, iWidth, iHeight);
	bool bSame = setindex == index;
	//55,128,73

	if (bOverBack)
		if (!g_Menu.IsHandlingItem())
			g_Menu.AddMenuFlag(FL_DISABLEDRAG);

	if (!bSame)
	{
		GradientVertical(x, y, iWidth, iHeight, 70, 70, 70, 255, 40, 40, 40);
		OutlinedRectangle(x - 1, y + 1, iWidth + 1, iHeight - 1, COLOR3);
	}
	else
	{
		GradientVertical(x, y, iWidth, iHeight, 55, 128, 73, 255, 15, 88, 33);
	}

	if (g_Mouse.mouse1pressed && (bOverBack))
		setindex = index;

	g_Draw.DrawStringA(g_Draw.m_ESPFont, true, x + iWidth * 0.5, y + 8, LISTITEM_TEXTCOLOR, pszTitle);
}

int iNubLoop[] = { 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

void cMenu::DrawTab(int index, int &setindex, int x, int y, const char *pszTitle)
{
	static int iWidth = 109;
	static int iHeight = 20;
	bool bOverBack = g_Mouse.IsOver(x, y, iWidth, iHeight);
	bool bSame = setindex == index;

	/*if (bOverBack)
		if (!g_Menu.IsHandlingItem())
		g_Menu.AddMenuFlag(FL_DISABLEDRAG);*/

	if (bSame)
		g_Draw.FillRGBA(x, y, iWidth, iHeight, g_CVARS.CvarList[MenuTabselect_r], g_CVARS.CvarList[MenuTabselect_g], g_CVARS.CvarList[MenuTabselect_b], g_CVARS.CvarList[MenuTabselect_a]);
	else
		if (bOverBack)
			g_Draw.FillRGBA(x, y, iWidth, iHeight, g_CVARS.CvarList[MenuTabhover_r], g_CVARS.CvarList[MenuTabhover_g], g_CVARS.CvarList[MenuTabhover_b], g_CVARS.CvarList[MenuTabhover_a]);

	if (g_Mouse.OneLeftClick(x, y, iWidth, iHeight))
		setindex = index;

	g_Draw.DrawStringA(g_Draw.m_MenuFont, true, x + iWidth * 0.5, y + 0, LISTITEM_TEXTCOLOR, pszTitle);
}

void cMenu::DrawAConfig(int index, int cfgidx, int x, int y, std::string sString)
{
	for (int i = 0; i < sString.size(); i++)
	{
		std::string sCopy = sString;

		sCopy = &sCopy[i];
		sCopy[1] = 0;

		g_Draw.DrawStringA(g_Draw.m_MenuFont, false, x, y + (i * 10), TEXTCOLOR1, sCopy.data());
	}

	if (GetConfigIndex(cfgidx) != index)
		SetConfigIndex(index, cfgidx);
}

#define ELEMENT_HEIGHT 15

void cListItem::Draw(int x, int y, int w, int h)
{
	int iNumOfItems = GetNumberOfItems();

	if (iNumOfItems == 0)
	{
		g_Draw.FillRGBA(x + w + 2, y, 8, h, COLOR2);

		OutlinedRectangle(x + w + 2, y, 8, h, COLOR6);

		OutlinedRectangle(x, y, w, h, COLOR2);

		return;
	}

	//we lost some old members probably... so we gotta make sure we still have some kind of selection
	if (iSelectedIndex >= iNumOfItems)
		iSelectedIndex = (iNumOfItems - 1);

	if (iTopIndex >= iNumOfItems)
		iTopIndex = 0;

	DisplayPerPage(((h / ELEMENT_HEIGHT) - 1));

	bScrollingNeeded = true;

	//we can display all items already so we dont have to change our top index
	if (iDisplayPerPage > iNumOfItems)
		bScrollingNeeded = false;

	//counter for items we will display/draw
	int iDisplayed = 0;

	for (int i = iTopIndex; i < iNumOfItems; i++)
	{
		//once display limit reached (if its even reached), we dont wanna display anymore
		if (iDisplayed > iDisplayPerPage)
			break;

		bool bBlackText = false;

		//current draw item
		//int iItemIndex = iTopIndex + i;
		ListItem_t liItem = GetItemFromIndex(i);

		int iDrawIndex = i - iTopIndex;

		//every second-item will have a different color (another optional rule for lists)
		if ((iDrawIndex & 2) == 1)//the leftover when dividing (i) by 2 is zero
			g_Draw.FillRGBA(x, y + iDrawIndex * ELEMENT_HEIGHT, w, ELEMENT_HEIGHT, 255, 255, 255, 255);

		if (g_Mouse.IsOver(x, y + iDrawIndex * ELEMENT_HEIGHT, w, ELEMENT_HEIGHT + 1))
		{
			//mouse is hoovering over our item ????
			g_Draw.FillRGBA(x, y + iDrawIndex * ELEMENT_HEIGHT, w, ELEMENT_HEIGHT, COLOR9);

			//handle selection upon a mouse click
			if (g_Mouse.mouse1pressed)
				this->Select(i);

			bBlackText = true;
		}

		if (iSelectedIndex == i)
		{
			g_Draw.FillRGBA(x, y + iDrawIndex * ELEMENT_HEIGHT, w, ELEMENT_HEIGHT, COLOR9);

			bBlackText = true;
		}

		if (bBlackText)
			g_Draw.DrawStringA(g_Draw.m_ListItemFont, false, x + 5, y + iDrawIndex * ELEMENT_HEIGHT + 1, 0, 0, 0, 255, liItem.szName);
		else
			g_Draw.DrawStringA(g_Draw.m_ListItemFont, false, x + 5, y + iDrawIndex * ELEMENT_HEIGHT + 1, LISTITEM_TEXTCOLOR, liItem.szName);

		//we displayed the current item with the index (i), so lets try and display the next item
		iDisplayed++;
	}

	//is this list in focus aka active
	if (g_Mouse.IsOver(x, y, w, h))
	{
		if (!IsFocused())
			SetFocus(true);
	}
	else
	{
		if (!IsOnlyListOnPage())
			bScrollingNeeded = false;//why would we scroll if we list aint active + this isnt only list on menu page

		if (IsFocused())
			SetFocus(false);
	}

	if (bScrollingNeeded)
	{
		int iHowMany = iNumOfItems - iDisplayPerPage;
		int iScrollBar = (iHowMany * 3.5);
		int iWhen = 0;

		if (iScrollBar > (h - 20))
		{
			iScrollBar = h - 20;

			for (int nab = 0;; nab++)
			{
				int iNew = (nab * 3.5);

				if (iNew > (h - 20))
				{
					iWhen = nab;
					break;
				}
			}
		}

		int iDiff = 0;

		if (iWhen > 0)
			iDiff = abs(iHowMany - iWhen) * 3.5;

		int iScrollBarHai = h + 3.5 - iScrollBar;
		int iScrollYAdd = iTopIndex * 3.5 * ((iWhen > 0) ? ((3.5 / iDiff) * 10 + 0.15) : 1);
		int iScrollYPos = y + iScrollYAdd;
		int iSavedScrollYPos = iScrollYPos;
		int iDummy;

		//g_Mouse.Drag(g_Mouse.bDragged[1], true/*!g_Radar.IsHandlingItem()*/,
		//	g_Mouse.LeftClick(x + w + 2, y, 8, h), iDummy, iScrollYPos, g_Mouse.iDiffX[1], g_Mouse.iDiffY[1]);

		//if (g_Mouse.bDragged[1] && !g_Menu.IsHandlingItem())//make sure we disable menu dragging
		//	g_Menu.AddMenuFlag(FL_DISABLEDRAG);

		if (iScrollYPos != iSavedScrollYPos)//slider was dragged
		{
			int iNewTopIndex = (iScrollYPos - y);
			iNewTopIndex /= 3.5;
			iNewTopIndex /= ((iWhen > 0) ? ((3.5 / iDiff) * 10 + 0.15) : 1);

			//min
			if (iNewTopIndex < 0)
				iNewTopIndex = 0;

			//max
			int iLastPossibleTopIndex = abs(iNumOfItems - iDisplayPerPage) - 1;

			if (iNewTopIndex > iLastPossibleTopIndex)
				iNewTopIndex = iLastPossibleTopIndex;

			//we clamped our new top index now we just gotta clamp our y pos
			iScrollYPos = y + (iNewTopIndex * 3.5 * ((iWhen > 0) ? ((3.5 / iDiff) * 10 + 0.15) : 1));

			//set the top index of the list
			iTopIndex = iNewTopIndex;
		}

		g_Draw.FillRGBA(x + w + 2, iScrollYPos, 8, iScrollBarHai, COLOR2);
	}
	else
		g_Draw.FillRGBA(x + w + 2, y, 8, h, COLOR2);

	OutlinedRectangle(x + w + 2, y, 8, h, COLOR6);

	OutlinedRectangle(x, y, w, h, COLOR2);
}

//SketchFlow Print Normal
void cMenu::DrawMenu()
{
	int iCenterTopX = m_x + 20;
	int iCenterTopY = m_y + 20;

	int MaxTabsWidth = m_w - 10;


	//Background
	g_Draw.FillRGBA(m_x, m_y, m_w, m_h, g_CVARS.CvarList[MenuBorder_r], g_CVARS.CvarList[MenuBorder_g], g_CVARS.CvarList[MenuBorder_b], g_CVARS.CvarList[MenuBorder_a]);
	OutlinedRectangle(m_x, m_y, m_w, m_h, COLOR3);
	g_Draw.DrawStringA(g_Draw.m_MenuFont, false, iCenterTopX, iCenterTopY - 9, LISTITEM_TEXTCOLOR, "ConvaCheats - wippysh4kes menu");
	g_Draw.DrawStringA(g_Draw.m_MenuFont, false, iCenterTopX, iCenterTopY + 1, LISTITEM_TEXTCOLOR, "incorporated by ConvaCheats");



	//Main Background
	g_Draw.FillRGBA(m_x + 5, m_y + 70, MaxTabsWidth, m_h - 70 - 5, g_CVARS.CvarList[MenuBackground2_r], g_CVARS.CvarList[MenuBackground2_g], g_CVARS.CvarList[MenuBackground2_b], g_CVARS.CvarList[MenuBackground2_a]);
	OutlinedRectangle(m_x + 5, m_y + 70, MaxTabsWidth, m_h - 70 - 5, COLOR3);




	g_Draw.FillRGBA(m_x + 5, m_y + 50, MaxTabsWidth, 20, g_CVARS.CvarList[MenuBackground1_r], g_CVARS.CvarList[MenuBackground1_g], g_CVARS.CvarList[MenuBackground1_b], g_CVARS.CvarList[MenuBackground1_a]);

	//Tabs
	int TabWidth = 109;

	DrawTab(AIMBOTTAB, iTabIndex, m_x + 5, m_y + 50, "Aimbot");

	DrawTab(VISUALSTAB, iTabIndex, m_x + 5 + TabWidth, m_y + 50, "Visuals");

	DrawTab(MISCTAB, iTabIndex, m_x + 5 + TabWidth * 2, m_y + 50, "Misc");

	DrawTab(KEYBINDS, iTabIndex, m_x + 5 + TabWidth * 3, m_y + 50, "Keybinds");

	DrawTab(COLORTAB, iTabIndex, m_x + 5 + g_Menu.m_w - 119, m_y + 5, "Colors");



	//Tabs Background
	OutlinedRectangle(m_x + 5, m_y + 50, MaxTabsWidth, 20, COLOR3);

	if (g_Mouse.IsOver(m_x, m_y + 50, m_w, m_h - 50))
		if (!g_Menu.IsHandlingItem())
			g_Menu.AddMenuFlag(FL_DISABLEDRAG);

	InitMenuElements();
}

void cMenuSection::Draw(int x, int y, int w, int h, const char *pszSectionName)
{
	int iWidth = g_Draw.getWidht(g_Draw.m_ListItemFont, pszSectionName);

	/*g_Draw.DrawStringA(g_Draw.m_MenuFont,false,x+20,y-7,LISTITEM_TEXTCOLOR,pszSectionName);

	g_Draw.FillRGBA(x,y,10,1,180,180,180,255);
	g_Draw.FillRGBA(x,y,1,h,180,180,180,255);
	g_Draw.FillRGBA(x,y+h,w,1,180,180,180,255);
	g_Draw.FillRGBA(x+w,y,1,h+1,180,180,180,255);
	g_Draw.FillRGBA(x+30+iWidth,y,w-(30+iWidth),1,180,180,180,255);
	*/
	SetSectionPos(x, y);
}

void cMenuSection::DrawAllDropDowns()
{
	int iNumOfDropDowns = vecDropDowns.size();

	int iWhich = -1;

	//AFTERCLICK FIX
	for (int i2 = (iNumOfDropDowns - 1); i2 >= 0; i2--)
	{
		bool bIsActive = bActiveDropDown[i2];

		if (bIsActive)
		{
			iWhich = i2;

			dwWait = GetTickCount() + 700;
			break;
		}
	}

	for (int i = (iNumOfDropDowns - 1); i >= 0; i--)
	{
		int e_x = vecDropDowns[i].x;
		int e_y = vecDropDowns[i].y;
		int iCount = vecDropDowns[i].iCount;
		int iWidth = vecDropDowns[i].iWidth;

		bool bIsActive = bActiveDropDown[i];

		char **ppszNames = vecDropDowns[i].ppszNames;
		float *fValues = vecDropDowns[i].fValues;
		float *cvar = vecDropDowns[i].cvar;

		if (bIsActive)
		{
			int string_x = e_x;

			for (int ax = 0; ax < iCount; ax++)
			{
				if (g_Mouse.IsOver(e_x + 100, e_y + 15 + (ax * 15), 15 * 9, 15))
				{
					if (GetAsyncKeyState(VK_LBUTTON))
					{
						*cvar = fValues[ax];
						bActiveDropDown[i] = false;
					}

					GradientVertical(e_x + 100, e_y + 15 + (ax * 15), 15 * 9, 16, g_CVARS.CvarList[MenuItemGradientHover1_r], g_CVARS.CvarList[MenuItemGradientHover1_g], g_CVARS.CvarList[MenuItemGradientHover1_b], g_CVARS.CvarList[MenuItemGradientHover1_a], g_CVARS.CvarList[MenuItemGradientHover2_r], g_CVARS.CvarList[MenuItemGradientHover2_g], g_CVARS.CvarList[MenuItemGradientHover2_b]);
				}
				else
				{
					if (GetAsyncKeyState(VK_LBUTTON))
						bActiveDropDown[i] = false;
					g_Draw.FillRGBA(e_x + 100, e_y + 15 + (ax * 15), 15 * 9, 16, 127, 127, 127, 255);
				}

				if (ax == (iCount - 1))
					OutlinedRectangle(e_x + 100, e_y + 1, 15 * 9, (ax + 1) * 15 - 1 + 15, COLOR3);

				g_Draw.DrawStringA(g_Draw.m_MenuFont, true, string_x + 100 + ((15 * 9) / 2), e_y + 15 + (ax * 15) - 1.50, LISTITEM_TEXTCOLOR, ppszNames[ax]);
			}

			for (int ax = 0; ax < iCount; ax++)
			{
				g_Draw.DrawStringA(g_Draw.m_MenuFont, true, string_x + 100 + ((15 * 9) / 2), e_y + 15 + (ax * 15) - 1.50, LISTITEM_TEXTCOLOR, ppszNames[ax]);
			}
		}
		else//drop down not active
		{
			GradientVertical(e_x + 100, e_y + 1, 15 * 9, 15, g_CVARS.CvarList[MenuItemGradient1_r], g_CVARS.CvarList[MenuItemGradient1_g], g_CVARS.CvarList[MenuItemGradient1_b], g_CVARS.CvarList[MenuItemGradient1_a], g_CVARS.CvarList[MenuItemGradient2_r], g_CVARS.CvarList[MenuItemGradient2_g], g_CVARS.CvarList[MenuItemGradient2_b]); // Nice gradient :D
			if (g_Mouse.IsOver(e_x + 100, e_y + 1, 15 * 9, 15))
			{
				GradientVertical(e_x + 100, e_y + 1, 15 * 9, 15, g_CVARS.CvarList[MenuItemGradientHover1_r], g_CVARS.CvarList[MenuItemGradientHover1_g], g_CVARS.CvarList[MenuItemGradientHover1_b], g_CVARS.CvarList[MenuItemGradientHover1_a], g_CVARS.CvarList[MenuItemGradientHover2_r], g_CVARS.CvarList[MenuItemGradientHover2_g], g_CVARS.CvarList[MenuItemGradientHover2_b]); // Nice gradient :D
				if (g_Mouse.bMouseOneHasJustBeenReleased() && (dwWait < GetTickCount() || iWhich == -1))
					bActiveDropDown[i] = true;
			}
			OutlinedRectangle(e_x + 100, e_y + 1, 15 * 9, 15, COLOR3);

			int string_x = e_x;
			int string_y = e_y;

			for (int ax = 0; ax < iCount; ax++)
			{
				if (*cvar == fValues[ax])//we display only the cvar matching the value in the list
				{
					g_Draw.DrawStringA(g_Draw.m_MenuFont, true, string_x + 100 + ((15 * 9) / 2), string_y - 1.50, LISTITEM_TEXTCOLOR, ppszNames[ax]);
				}
			}
		}
	}

	ClearAllElementSpecifics();
}

char* KeyStrings[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

void cMenuSection::AddElement(int iType, int add_to_x, const char *pszElementName, const char *pszComment, float *cvar, float min, float max, float step, float fToValue, int increment, static bool &keybind)
{
	int e_x = s_x + 10 + add_to_x;
	int e_y = iType == SLIDER ? s_y + 15 + (iSection * 10) : s_y + 15 + (iSection * 23);

	if (iType != BUTTON)
		g_Menu.DrawHeaderComment(e_x, e_y, pszComment, (iType == SLIDER));

	bool bDropDownActive = false;

	for (int i2 = 0; i2 < 50; i2++)
	{
		bDropDownActive = bActiveDropDown[i2];

		if (bDropDownActive)
			break;
	}

	if (iType == ONOFF)
	{
		int length = 0;

		if (g_Mouse.OneLeftClick(e_x, e_y + 1, 15, 15) && !bDropDownActive)
			*cvar = !*cvar;

		GradientVertical(e_x, e_y + 1, 15, 15, g_CVARS.CvarList[MenuItemGradient1_r], g_CVARS.CvarList[MenuItemGradient1_g], g_CVARS.CvarList[MenuItemGradient1_b], g_CVARS.CvarList[MenuItemGradient1_a], g_CVARS.CvarList[MenuItemGradient2_r], g_CVARS.CvarList[MenuItemGradient2_g], g_CVARS.CvarList[MenuItemGradient2_b]); // Nice gradient :D
		if (g_Mouse.IsOver(e_x, e_y + 1, 15, 15))
			GradientVertical(e_x, e_y + 1, 15, 15, g_CVARS.CvarList[MenuItemGradientHover1_r], g_CVARS.CvarList[MenuItemGradientHover1_g], g_CVARS.CvarList[MenuItemGradientHover1_b], g_CVARS.CvarList[MenuItemGradientHover1_a], g_CVARS.CvarList[MenuItemGradientHover2_r], g_CVARS.CvarList[MenuItemGradientHover2_g], g_CVARS.CvarList[MenuItemGradientHover2_b]);

		OutlinedRectangle(e_x, e_y + 1, 15, 15, COLOR3);

		if (*cvar)
		{
			g_Draw.DrawStringA(g_Draw.m_MenuFont, true, e_x + 8.75, e_y - 3, LISTITEM_TEXTCOLOR, "x");
		}

		g_Draw.DrawStringA(g_Draw.m_MenuFont, false, e_x + 21, e_y - 1, LISTITEM_TEXTCOLOR, pszElementName);
	}
	if (iType == SLIDER)
	{
		fLength = 275/* + 165*/;

		float Scale = max / fLength;

		bool bOver = false;

		if (bShowValue)
		{
			char szCopy[256];

			strcpy(szCopy, pszElementName);
			sprintf(szCopy, "%s : %2.0f", pszElementName, *cvar);

			g_Draw.DrawStringA(g_Draw.m_MenuFont, false, e_x, e_y, LISTITEM_TEXTCOLOR, szCopy);
		}

		e_y += 5;

		GradientVertical(e_x + 120, e_y + 4, fLength, 5, g_CVARS.CvarList[MenuItemGradient1_r], g_CVARS.CvarList[MenuItemGradient1_g], g_CVARS.CvarList[MenuItemGradient1_b], g_CVARS.CvarList[MenuItemGradient1_a], g_CVARS.CvarList[MenuItemGradient2_r], g_CVARS.CvarList[MenuItemGradient2_g], g_CVARS.CvarList[MenuItemGradient2_b]); // Nice gradient :D
		if (g_Mouse.IsOver(e_x + 120, e_y + 4, fLength, 5))
			GradientVertical(e_x + 120, e_y + 4, fLength, 5, g_CVARS.CvarList[MenuItemGradientHover1_r], g_CVARS.CvarList[MenuItemGradientHover1_g], g_CVARS.CvarList[MenuItemGradientHover1_b], g_CVARS.CvarList[MenuItemGradientHover1_a], g_CVARS.CvarList[MenuItemGradientHover2_r], g_CVARS.CvarList[MenuItemGradientHover2_g], g_CVARS.CvarList[MenuItemGradientHover2_b]);

		OutlinedRectangle(e_x + 120, e_y + 4, fLength, 5, 0, 0, 0, 255);

		int mouse_x, mouse_y;
		mouse_x = g_Mouse.pHackMouse.x;
		mouse_y = g_Mouse.pHackMouse.y;

		if (mouse_x >= ((e_x + 120) - 3) && mouse_x <= (e_x + 120 + fLength + 3) && mouse_y >= (e_y) && mouse_y <= (e_y + 10) && GetAsyncKeyState(VK_LBUTTON) && (iSliderIndex == -1) && dwWait < GetTickCount() && !bSliderFix[iCurrSlider])
		{
			iSliderIndex = iCurrSlider;
			bSliderFix[iCurrSlider] = true;

			if (!g_Menu.IsHandlingItem())
				g_Menu.AddMenuFlag(FL_DISABLEDRAG);
		}

		if (mouse_x >= ((e_x + 120) - 1000) && mouse_x <= ((e_x + 120) + fLength + 1000) && mouse_y >= (e_y - 1000) && mouse_y <= (e_y + 1000) && GetAsyncKeyState(VK_LBUTTON) && !bDropDownActive)
		{
			if (bSliderFix[iCurrSlider])
			{
				*cvar = min + (mouse_x - (e_x + 120)) * Scale;

				bOver = true;

				if (!g_Menu.IsHandlingItem())
					g_Menu.AddMenuFlag(FL_DISABLEDRAG);
			}
		}
		else if (bSliderFix[iCurrSlider])
		{
			iSliderIndex = -1;
			bSliderFix[iCurrSlider] = false;
		}

		if (*cvar > max)
			*cvar = max;

		if (*cvar < min)
			*cvar = min;

		g_Draw.FillRGBA(e_x + 120 + (*cvar / Scale), e_y + 2, 4, 9, g_CVARS.CvarList[MenuSliderDrag_r], g_CVARS.CvarList[MenuSliderDrag_g], g_CVARS.CvarList[MenuSliderDrag_b], g_CVARS.CvarList[MenuSliderDrag_a]);
		OutlinedRectangle(e_x + 120 + (*cvar / Scale), e_y + 2, 4, 9, 0, 0, 0, 255);
	}
	else if (iType == DROPDOWN)
	{
		DropDown_t ddNew;

		ddNew.x = e_x;
		ddNew.y = e_y;
		ddNew.fValues = fValueList;
		ddNew.cvar = cvar;
		ddNew.ppszNames = ppszValueNames;
		ddNew.iCount = iValueCount;

		AddDropDownToDrawList(ddNew);

		g_Draw.DrawStringA(g_Draw.m_MenuFont, false, e_x, e_y, LISTITEM_TEXTCOLOR, pszElementName);

		e_y += 5;
	}
	else if (iType == BUTTON)
	{
		bool bLeftClick = g_Mouse.LeftClick(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT);

		if (fToValue == -1)
		{
			if (*cvar)
				GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR4, 140, 0, 0);
			else
			{
				if (bLeftClick)
					GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR9, 35, 35, 35);
				else
					GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR4, 50, 50, 50);
			}
		}
		else
		{
			if (*cvar == fToValue)
				GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR4, 140, 0, 0);
			else
			{
				if (bLeftClick)
					GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR9, 35, 35, 35);
				else
					GradientVertical(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR4, 50, 50, 50);
			}
		}

		g_Draw.DrawStringA(g_Draw.m_ListItemFont, true, e_x + BUTTON_WIDTH * 0.5, e_y + 2, LISTITEM_TEXTCOLOR, pszElementName);

		if (g_Mouse.IsOver(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT))
		{
			if (!bLeftClick)
				SoftOutlinedRectangle(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR9);
			else
				SoftOutlinedRectangle(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR3);

			if (g_Mouse.mouse1released && !bDropDownActive)
			{
				if (fToValue == -1)
					*cvar = !*cvar;
				else
					*cvar = fToValue;
			}
		}
		else
			SoftOutlinedRectangle(e_x, e_y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR3);
	}
	else if (iType == ADDER)
	{
		g_Draw.DrawStringA(g_Draw.m_ListItemFont, false, e_x, e_y, LISTITEM_TEXTCOLOR, pszElementName);

		e_y += 1;

		e_x += (CHECKBOX_SEPERATION_FROM_TEXT - 20);

		g_Draw.FillRGBA(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR7);

		if (g_Mouse.IsOver(e_x, e_y, ADDER_SIZE, ADDER_SIZE))
		{
			OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR9);

			if (g_Mouse.mouse1released && !bDropDownActive)
				*cvar -= step;

			if (g_Mouse.mouse2hold && !bDropDownActive)
				*cvar -= 20;
		}
		else
			OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR4);

		static std::string sLeft = "<";

		g_Draw.DrawStringA(g_Draw.m_ListItemFont, true, e_x + ADDER_SIZE * 0.5, e_y - 3, COLOR10, sLeft.data());

		static std::string sValue = "%2.0f";

		g_Draw.DrawStringA(g_Draw.m_ListItemFont, true, e_x - 6 + ADDER_SIZE + ADDER_SEPERATE_FROM_BOXES * 0.5, e_y - 2, LISTITEM_TEXTCOLOR, sValue.data(), *cvar);

		e_x += ADDER_SEPERATE_FROM_BOXES;

		g_Draw.FillRGBA(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR7);

		if (g_Mouse.IsOver(e_x, e_y, ADDER_SIZE, ADDER_SIZE))
		{
			OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR9);

			if (g_Mouse.mouse1released && !bDropDownActive)
				*cvar += step;

			if (g_Mouse.mouse2hold && !bDropDownActive)
				*cvar += 20;
		}
		else
			OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR4);

		static std::string sRight = ">";

		g_Draw.DrawStringA(g_Draw.m_ListItemFont, true, e_x + ADDER_SIZE * 0.5, e_y - 3, COLOR10, sRight.data());

		//clamp but go to min,max instead of not allowing to increase/decrease
		if (*cvar < min)
			*cvar = max;

		if (*cvar > max)
			*cvar = min;
	}
	else if (iType == KEYBIND)
	{
		if (g_Mouse.OneLeftClick(g_Menu.m_x + g_Menu.m_w - 158, e_y + 1, 135, 15) && !bDropDownActive)
		{
			keybind = true;
			*cvar = 0;
		}

		if (keybind)
		{
			for (int i = 1; i <= 255; i++)
			{
				if (GetAsyncKeyState(i) & 1)
				{
					if (i == VK_ESCAPE)
						*cvar = 0;
					else
						*cvar = i;
					keybind = false; g_Mouse.ClickHandler();
				}
			}
		}

		GradientVertical(g_Menu.m_x + g_Menu.m_w - 158, e_y + 1, 135, 15, g_CVARS.CvarList[MenuItemGradient1_r], g_CVARS.CvarList[MenuItemGradient1_g], g_CVARS.CvarList[MenuItemGradient1_b], g_CVARS.CvarList[MenuItemGradient1_a], g_CVARS.CvarList[MenuItemGradient2_r], g_CVARS.CvarList[MenuItemGradient2_g], g_CVARS.CvarList[MenuItemGradient2_b]); // Nice gradient :D
		if (g_Mouse.IsOver(g_Menu.m_x + g_Menu.m_w - 158, e_y + 1, 135, 15))
			GradientVertical(g_Menu.m_x + g_Menu.m_w - 158, e_y + 1, 135, 15, g_CVARS.CvarList[MenuItemGradientHover1_r], g_CVARS.CvarList[MenuItemGradientHover1_g], g_CVARS.CvarList[MenuItemGradientHover1_b], g_CVARS.CvarList[MenuItemGradientHover1_a], g_CVARS.CvarList[MenuItemGradientHover2_r], g_CVARS.CvarList[MenuItemGradientHover2_g], g_CVARS.CvarList[MenuItemGradientHover2_b]);
		OutlinedRectangle(g_Menu.m_x + g_Menu.m_w - 158, e_y + 1, 135, 15, COLOR3);

		char* keyname = "no key";

		if (keybind)
			g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_Menu.m_x + g_Menu.m_w - 150, e_y - 2, LISTITEM_TEXTCOLOR, "<press a key>");
		else
		{
			if (*cvar)
			{
				keyname = KeyStrings[(int)*cvar];
				g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_Menu.m_x + g_Menu.m_w - 150, e_y - 2, LISTITEM_TEXTCOLOR, "%s", keyname);
			}
			else
				g_Draw.DrawStringA(g_Draw.m_MenuFont, false, g_Menu.m_x + g_Menu.m_w - 150, e_y - 2, LISTITEM_TEXTCOLOR, "no key");
		}

		g_Draw.DrawStringA(g_Draw.m_MenuFont, false, e_x, e_y - 1, LISTITEM_TEXTCOLOR, pszElementName);
	}

	PostElement((iType == SLIDER ? 2 : 1));
}