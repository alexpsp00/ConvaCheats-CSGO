#pragma once

#define MAX_CVARS 158

enum
{
	AimbotActive,//
	AimbotAutoShoot,//
	AimbotHitbox,
	AimbotFOV,//
	AimbotSmooth,//
	AimbotRCS,//
	AimbotRCSMaxDist,//
	AimbotRCSMinDist,//
	AimbotRCSScale,//
	AimbotScope,//
	AimbotOnKey,//
	AimbotShootOnKey,//
	AimbotMinDist,//
	AimbotMaxDist,//
	AimbotWallBang,//
	AimbotMultiSpot,//
	AimbotMultiSpotLength,//
	AimbotIgnoreThroughSmoke,//
	AimbotSilent,//
	AimbotTeamAim,//
	AimbotAntiDM,
	AimbotLimitRecoil,
	AimbotIgnoreJumpers,
	AimbotAutoStop,
	AimbotAutoCrouch,
	AimbotNoRecoil,
	AimbotAutoAWP,
	LimitRecoilMax,
	LimitRecoilDelay,
	AimbotTargetSelection,

	TriggerbotActive,//
	TriggerbotOverBurst,//
	TriggerbotSniper,//
	TriggerbotOnlyWhenScoped,//
	TriggerbotHead,//
	TriggerbotIgnoreArmsLegs,//
	TriggerbotOnKey,//
	TriggerbotDelay,//

	ESPActive,
	ESPBox,
	ESPName,
	ESPDistance,
	ESPHealth,
	ESPHead,
	ESPWeapon,
	ESPArmor,
	ESPCash,
	ESPAngles,
	ESPChickens,
	ESPEnemyOnly,
	ESPVisCheck,
	ESPWhenVis,
	ESPWhenNotVis,

	Crosshair,
	RecoilCrosshair,
	NoVisualRecoil,

	AutoBhop,
	AutoStrafe,
	AutoPistol,
	AntiAUTH,
	SafeMode,
	AirStuck,
	Spinbot,//
	FOVChanger,
	ChatSpam,
	SlowChatSpam,
	RadioSpam,
	SlowRadioSpam,
	AntiAim,//
	AntiAimFollowTarget,//
	AntiAimStatic,
	PerfectSilent,
	AntiAimX,
	AntiAimY,
	FakeLag,//
	FakeLagValue,//
	NameStealer,
	ThirdPerson,

	KnifeChanger,
	KnifePattern,
	KnifeStattrak,

	AWPChanger,
	AK47Changer,

	/*AWPChanger,*/
	ApplySkin,


	Key_Aimbot,
	Key_AimbotToggle,
	Key_Triggerbot,
	Key_Triggerbot_Toggle,
	Key_EspToggle,
	Key_Menu,
	key_Panic,
	Key_Airstuck,


	/*config_select,*/
	/*config1_save,
	config1_load,*/

	/*silent_mode,
	MenuX,
	MenuY,*/




	selected_visual_color,

	crosshair_r, crosshair_g, crosshair_b, crosshair_a,
	recoilxhair_r, recoilxhair_g, recoilxhair_b, recoilxhair_a,


	CTvis_r, CTvis_g, CTvis_b, CTvis_a,
	CTnotvis_r, CTnotvis_g, CTnotvis_b, CTnotvis_a,
	Tvis_r, Tvis_g, Tvis_b, Tvis_a,
	Tnotvis_r, Tnotvis_g, Tnotvis_b, Tnotvis_a,


	MenuText_r, MenuText_g, MenuText_b, MenuText_a,
	MenuBorder_r, MenuBorder_g, MenuBorder_b, MenuBorder_a,
	MenuBackground1_r, MenuBackground1_g, MenuBackground1_b, MenuBackground1_a,
	MenuBackground2_r, MenuBackground2_g, MenuBackground2_b, MenuBackground2_a,
	MenuTabselect_r, MenuTabselect_g, MenuTabselect_b, MenuTabselect_a,
	MenuTabhover_r, MenuTabhover_g, MenuTabhover_b, MenuTabhover_a,

	MenuItemGradient1_r, MenuItemGradient1_g, MenuItemGradient1_b, MenuItemGradient1_a,
	MenuItemGradient2_r, MenuItemGradient2_g, MenuItemGradient2_b,

	MenuItemGradientHover1_r, MenuItemGradientHover1_g, MenuItemGradientHover1_b, MenuItemGradientHover1_a,
	MenuItemGradientHover2_r, MenuItemGradientHover2_g, MenuItemGradientHover2_b,

	MenuSliderDrag_r, MenuSliderDrag_g, MenuSliderDrag_b, MenuSliderDrag_a,

	MenuSeperator_r, MenuSeperator_g, MenuSeperator_b, MenuSeperator_a,

	circlestrafe,
};

enum
{
	SaveConfig,
	LoadConfig,
};

class cCVARS
{
public:

	void HandleConfig(const char *pszConfigName, int iType);

	void Init(HMODULE hinstDLL);

	float CvarList[MAX_CVARS];

	bool Configzzz;

	bool PanicButton;

	float config_select;
	float selected_esp_color;

	void DefaultConfig()
	{
		this->CvarList[crosshair_r] = 0; this->CvarList[crosshair_g] = 255; this->CvarList[crosshair_b] = 255; this->CvarList[crosshair_a] = 255;
		this->CvarList[recoilxhair_r] = 255; this->CvarList[recoilxhair_g] = 255; this->CvarList[recoilxhair_b] = 255; this->CvarList[recoilxhair_a] = 255;

		this->CvarList[CTvis_r] = 255; this->CvarList[CTvis_g] = 0; this->CvarList[CTvis_b] = 255; this->CvarList[CTvis_a] = 255;
		this->CvarList[CTnotvis_r] = 255; this->CvarList[CTnotvis_g] = 255; this->CvarList[CTnotvis_b] = 255; this->CvarList[CTnotvis_a] = 255;
		this->CvarList[Tvis_r] = 255; this->CvarList[Tvis_g] = 0; this->CvarList[Tvis_b] = 255; this->CvarList[Tvis_a] = 255;
		this->CvarList[Tnotvis_r] = 255; this->CvarList[Tnotvis_g] = 255; this->CvarList[Tnotvis_b] = 255; this->CvarList[Tnotvis_a] = 255;

		this->CvarList[MenuText_r] = 255; this->CvarList[MenuText_g] = 255; this->CvarList[MenuText_b] = 255; this->CvarList[MenuText_a] = 255;
		this->CvarList[MenuBorder_r] = 46; this->CvarList[MenuBorder_g] = 46; this->CvarList[MenuBorder_b] = 46; this->CvarList[MenuBorder_a] = 255;
		this->CvarList[MenuBackground1_r] = 74; this->CvarList[MenuBackground1_g] = 74; this->CvarList[MenuBackground1_b] = 74; this->CvarList[MenuBackground1_a] = 255;
		this->CvarList[MenuBackground2_r] = 127; this->CvarList[MenuBackground2_g] = 127; this->CvarList[MenuBackground2_b] = 127; this->CvarList[MenuBackground2_a] = 255;

		this->CvarList[MenuTabselect_r] = 0; this->CvarList[MenuTabselect_g] = 126; this->CvarList[MenuTabselect_b] = 253; this->CvarList[MenuTabselect_a] = 255;
		this->CvarList[MenuTabhover_r] = 100; this->CvarList[MenuTabhover_g] = 177; this->CvarList[MenuTabhover_b] = 255; this->CvarList[MenuTabhover_a] = 255;

		this->CvarList[MenuItemGradient1_r] = 100; this->CvarList[MenuItemGradient1_g] = 100; this->CvarList[MenuItemGradient1_b] = 100; this->CvarList[MenuItemGradient1_a] = 255;
		this->CvarList[MenuItemGradient2_r] = 130; this->CvarList[MenuItemGradient2_g] = 130; this->CvarList[MenuItemGradient2_b] = 130;

		this->CvarList[MenuItemGradientHover1_r] = 130; this->CvarList[MenuItemGradientHover1_g] = 130; this->CvarList[MenuItemGradientHover1_b] = 130; this->CvarList[MenuItemGradientHover1_a] = 255;
		this->CvarList[MenuItemGradientHover2_r] = 100; this->CvarList[MenuItemGradientHover2_g] = 100; this->CvarList[MenuItemGradientHover2_b] = 100;

		this->CvarList[MenuSliderDrag_r] = 230; this->CvarList[MenuSliderDrag_g] = 230; this->CvarList[MenuSliderDrag_b] = 230; this->CvarList[MenuSliderDrag_a] = 255;

		this->CvarList[MenuSeperator_r] = 230; this->CvarList[MenuSeperator_g] = 230; this->CvarList[MenuSeperator_b] = 230; this->CvarList[MenuSeperator_a] = 255;

		this->CvarList[SafeMode] = 1;


		this->CvarList[ESPActive] = 1;
		this->CvarList[ESPBox] = 1;
		this->CvarList[ESPName] = 1;
		this->CvarList[ESPDistance] = 1;
		this->CvarList[ESPHealth] = 1;
		this->CvarList[ESPHead] = 1;
		this->CvarList[ESPWeapon] = 1;
		this->CvarList[ESPArmor] = 1;
		this->CvarList[ESPCash] = 1;
		this->CvarList[ESPAngles] = 1;
		this->CvarList[ESPChickens] = 1;
		this->CvarList[ESPEnemyOnly] = 1;
		this->CvarList[ESPVisCheck] = 1;
		this->CvarList[ESPWhenVis] = 1;
		this->CvarList[ESPWhenNotVis] = 1;

		


		this->CvarList[AimbotActive] = 1;
		this->CvarList[AimbotAutoShoot] = 1;
		this->CvarList[AimbotSilent] = 1;
		this->CvarList[AimbotNoRecoil] = 1;
		this->CvarList[AimbotAntiDM] = 1;
		this->CvarList[AimbotFOV] = 360;
		this->CvarList[AimbotMaxDist] = 500;

		this->CvarList[NoVisualRecoil] = 1;
		this->CvarList[Crosshair] = 1;
		this->CvarList[RecoilCrosshair] = 1;

		this->CvarList[AutoBhop] = 1;
		this->CvarList[AutoStrafe] = 1;
		this->CvarList[AutoPistol] = 1;
	}

private:

	char szIniFilePath[2048];
};

extern cCVARS g_CVARS;