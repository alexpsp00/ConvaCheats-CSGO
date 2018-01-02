#include "main.h"
#include "Client.h"
#include "SDK.h"

Base::Utils::CVMTHookManager g_pFrameStageNotify;

#define KNIFE_DEFAULTT  59;
#define KNIFE_DEFAULTCT 42;
#define KNIFE_KARAMBIT  507;
#define KNIFE_BAYONET   500;
#define KNIFE_HUNTSMAN  509;
#define KNIFE_GUTKNIFE  506;
#define KNIFE_SHADOWD   516;
#define KNIFE_BUTTERFLY 515;
#define KNIFE_FLIPKNIFE 505;
#define KNIFE_M9BAYONET 508;
#define KNIFE_FALCHION  512;
#define KNIFE_BOWIE     514;

#define KNIFE_PATTERN_FADE 38;
#define KNIFE_PATTERN_DAMASCUSSTEEL 410;
#define KNIFE_PATTERN_DOPPLER_PHASE1 418;
#define KNIFE_PATTERN_DOPPLER_PHASE2 419;
#define KNIFE_PATTERN_DOPPLER_PHASE3 420;
#define KNIFE_PATTERN_DOPPLER_RUBY 415;
#define KNIFE_PATTERN_DOPPLER_SAPPHIRE 416;
#define KNIFE_PATTERN_DOPPLER_BLACKPEARL 417;
#define KNIFE_PATTERN_DOPPLER_MARBLEFADE 413;
#define KNIFE_PATTERN_DOPPLER_TIGERTOOTH 409;
#define KNIFE_PATTERN_DOPPLER_ULTRAVIOLET 98;
#define KNIFE_PATTERN_DOPPLER_CRIMSOMWEB 12;
#define KNIFE_PATTERN_DOPPLER_SLAUGHTER 59;
#define KNIFE_PATTERN_DOPPLER_NIGHT 40;
namespace Global				   
{
	Vector visualangle;
}
void Hooked_RecvProxy_Viewmodel(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	int iDefaultT = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	int iDefaultCT = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_default_ct.mdl");

	int iBayonet = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	int iButterfly = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	int iFlip = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_flip.mdl");
	/*int iGunGame = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_gg.mdl");*/
	int iGut = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_gut.mdl");
	int iKarambit = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_karam.mdl");
	int iM9Bayonet = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	int iHuntsman = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	int iFalchion = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	int iDagger = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_push.mdl");
	int iBowie = g_Valve.g_pModel->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

	if (*(int*)((DWORD)pData + 0x8) == iDefaultT
		|| *(int*)((DWORD)pData + 0x8) == iDefaultCT)
	{
		if (g_CVARS.CvarList[KnifeChanger] > 0)
		{
			if (g_CVARS.CvarList[KnifeChanger] == 1)
				*(int*)((DWORD)pData + 0x8) = iBayonet;
			if (g_CVARS.CvarList[KnifeChanger] == 2)
				*(int*)((DWORD)pData + 0x8) = iButterfly;
			if (g_CVARS.CvarList[KnifeChanger] == 3)
				*(int*)((DWORD)pData + 0x8) = iFlip;
			if (g_CVARS.CvarList[KnifeChanger] == 4)
				*(int*)((DWORD)pData + 0x8) = iGut;
			if (g_CVARS.CvarList[KnifeChanger] == 5)
				*(int*)((DWORD)pData + 0x8) = iKarambit;
			if (g_CVARS.CvarList[KnifeChanger] == 6)
				*(int*)((DWORD)pData + 0x8) = iM9Bayonet;
			if (g_CVARS.CvarList[KnifeChanger] == 7)
				*(int*)((DWORD)pData + 0x8) = iHuntsman;
			if (g_CVARS.CvarList[KnifeChanger] == 8)
				*(int*)((DWORD)pData + 0x8) = iFalchion;
			if (g_CVARS.CvarList[KnifeChanger] == 9)
				*(int*)((DWORD)pData + 0x8) = iDagger;
			if (g_CVARS.CvarList[KnifeChanger] == 10)
				*(int*)((DWORD)pData + 0x8) = iBowie;
		}
	}

	*(int*)((DWORD)pOut) = *(int*)((DWORD)pData + 0x8);
}

void __stdcall new_FrameStageNotify(ClientFrameStage_t curStage)
{
	static DWORD dwFrameStage = g_pFrameStageNotify.dwGetMethodAddress(36);

	_asm
	{
		PUSH curStage;
		CALL dwFrameStage;
	}

	static Vector qOldPunch;
	static Vector qOldPunch2;
	static int tpa = g_NetworkedVariableManager.GetOffset("DT_BasePlayer", "pl") + g_NetworkedVariableManager.GetOffset("DT_PlayerState", "deadflag") + 0x8;
	static int iAimPunchOffset = g_NetworkedVariableManager.GetOffset("DT_CSPlayer", "m_aimPunchAngle");
	static int iViewPunchOffset = g_NetworkedVariableManager.GetOffset("DT_CSPlayer", "m_viewPunchAngle");
	if (g_CVARS.CvarList[NoVisualRecoil] && g_Valve.pEngine->IsInGame() && curStage == FRAME_RENDER_START)
	{

		CBaseEntity* pMe = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());

		Vector *qPunch = (Vector*)((DWORD)pMe + iAimPunchOffset);
		Vector *qPunch2 = (Vector*)((DWORD)pMe + iViewPunchOffset);




		if (*(bool*)((DWORD)g_Valve.pInput + 0xA5))
		{
			*(Vector*)((DWORD)g_Valve.pInput + g_NetworkedVariableManager.GetOffset("DT_CSPlayer", "deadflag") + 4) = Global::visualangle;
		}



		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && g_Valve.pEngine->GetLocalPlayer() > 0)
		{
			if (g_Valve.pEngine->IsInGame())
			{
				CBaseEntity* pLocal = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
				if (pLocal)
				{
					ValveSDK::CBaseCombatWeapon* pWeapon = pLocal->GetActiveBaseCombatWeapon();
					if (pWeapon)
					{
						if ((GetAsyncKeyState(VK_END) & 1))
						{
							static uintptr_t pClientState = **(uintptr_t**)(Base::Utils::PatternSearch("engine.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x8A\xF9", "xx????xx", NULL, 0x438000) + 2);

							static uintptr_t dwAddr1 = Base::Utils::PatternSearch("engine.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00", "x????x????x????xx????????", NULL, 0x438000);

							static uintptr_t dwRelAddr = *(uintptr_t*)(dwAddr1 + 1);
							static uintptr_t sub_B5E60 = ((dwAddr1 + 5) + dwRelAddr);

							__asm
							{
								pushad
									mov edi, pClientState
									lea ecx, dword ptr[edi + 0x8]
									call sub_B5E60
									mov dword ptr[edi + 0x164], 0xFFFFFFFF
									popad

							}
						}


						if (g_CVARS.CvarList[FOVChanger] > 00)
							pLocal->SetFov(g_CVARS.CvarList[FOVChanger]);

						if (!(pLocal->GetActiveBaseCombatWeapon()->IsKnife()))
						{
							if (pLocal->GetActiveBaseCombatWeapon()->GetWeaponID() == awp || pLocal->GetActiveBaseCombatWeapon()->GetWeaponID() == ak)
							{
								*(PINT)((DWORD)pWeapon + 0x3158) = 0; //m_OriginalOwnerXuidLow
								*(PINT)((DWORD)pWeapon + 0x315C) = 0; //m_OriginalOwnerXuidHigh
								//*(PINT)((DWORD)pWeapon + 0x31C0) = 0; //m_hOwner
								*(PINT)((DWORD)pWeapon + 0x3164) = 1; //m_nFallbackSeed
								//todo: add m_iEntityQuality

								if (pLocal->GetActiveBaseCombatWeapon()->GetWeaponID() == awp && g_CVARS.CvarList[AWPChanger] > 0)
									*(PINT)((DWORD)pWeapon + 0x3160) = g_CVARS.CvarList[AWPChanger];
								if (pLocal->GetActiveBaseCombatWeapon()->GetWeaponID() == ak && g_CVARS.CvarList[AK47Changer] > 0)
									*(PINT)((DWORD)pWeapon + 0x3160) = g_CVARS.CvarList[AK47Changer];

								*(PFLOAT)((DWORD)pWeapon + 0x3168) = 0.99f - (98 / 100.0f); //m_flFallbackWear
								*(PINT)((DWORD)pWeapon + 0x316C) = (true ? 1337 : -1); //m_nFallbackStatTrak
								//*(PINT)((DWORD)pWeapon + 0x2FA0) = 1; //account id //1E8 //1EC //1F0 //0x2F98
								*(PINT)((DWORD)pWeapon + 0x2F98) = 1;
								*(PINT)((DWORD)pWeapon + 0x2F9C) = 0;//0 //geniue //high //low
								//*(PINT)((DWORD)pWeapon + 0x2F84) = 2; //test
								*(PINT)((DWORD)pWeapon + 0x2F84) = 9; //m_iEntityQuality
								char customName[64] = "ConvaCheats CSGO";
								strcpy((char*)pWeapon + 0x3014, customName); //custom nametag
								//*(PINT)((DWORD)pWeapon + 0x3158) = 0; //XUID Low
								//*(PINT)((DWORD)pWeapon + 0x2FA0) = 0; //m_iAccountID skal være det samme brug netvars til alle og find ud af navne til offsets
							}
						}
						else if (pLocal->GetActiveBaseCombatWeapon()->IsKnife())
						{
							char customName[64] = "ConvaCheats CSGO";
							*(PINT)((DWORD)pWeapon + 0x3158) = 0; //m_OriginalOwnerXuidLow
							*(PINT)((DWORD)pWeapon + 0x315C) = 0; //m_OriginalOwnerXuidHigh
							//*(PINT)((DWORD)pWeapon + 0x3164) = 1; //m_nFallbackSeed
							if (g_CVARS.CvarList[KnifePattern] == 1)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_FADE;
							if (g_CVARS.CvarList[KnifePattern] == 2)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DAMASCUSSTEEL;
							if (g_CVARS.CvarList[KnifePattern] == 3)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_PHASE1;
							if (g_CVARS.CvarList[KnifePattern] == 4)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_PHASE2;
							if (g_CVARS.CvarList[KnifePattern] == 5)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_PHASE3;
							if (g_CVARS.CvarList[KnifePattern] == 6)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_RUBY;
							if (g_CVARS.CvarList[KnifePattern] == 7)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_SAPPHIRE;
							if (g_CVARS.CvarList[KnifePattern] == 8)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_BLACKPEARL;
							if (g_CVARS.CvarList[KnifePattern] == 9)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_MARBLEFADE;
							if (g_CVARS.CvarList[KnifePattern] == 10)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_TIGERTOOTH;
							if (g_CVARS.CvarList[KnifePattern] == 11)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_ULTRAVIOLET;
							if (g_CVARS.CvarList[KnifePattern] == 12)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_CRIMSOMWEB;
							if (g_CVARS.CvarList[KnifePattern] == 13)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_SLAUGHTER;
							if (g_CVARS.CvarList[KnifePattern] == 14)
								*(PINT)((DWORD)pWeapon + 0x3160) = KNIFE_PATTERN_DOPPLER_NIGHT;
							*(PFLOAT)((DWORD)pWeapon + 0x3168) = 0.99f - (98 / 100.0f); //m_flFallbackWear
							if (g_CVARS.CvarList[KnifeStattrak] == 1)
								*(PINT)((DWORD)pWeapon + 0x316C) = (true ? 1337 : -1); //m_nFallbackStatTrak
							//*(PINT)((DWORD)pWeapon + 0x2FA0) = 1; //m_iAccountID (AttributeManager + Item + AccountID = 2FA0, calculated in HEX)
							*(PINT)((DWORD)pWeapon + 0x2F98) = 1; //m_iItemIDHigh (AttributeManager + Item + ItemIDHigh = 2F98, calculated in HEX)
							*(PINT)((DWORD)pWeapon + 0x2F9C) = 0;//m_iItemIDLow (AttributeManager + Item + ItemIDLow = 2F9C, calculated in HEX)
							*(PINT)((DWORD)pWeapon + 0x2F84) = 3; //m_iEntityQuality
							strcpy((char*)pWeapon + 0x3014, customName); //m_szCustomName
						}
					}
				}
			}

			CBaseEntity* pLocal = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
			if (pLocal)
			{
				if (pLocal->GetLifeState() == LIFE_ALIVE)
				{
					ValveSDK::CBaseCombatWeapon* pWeapon = pWeapon = pLocal->GetActiveBaseCombatWeapon();
					if (pWeapon)
					{
						/*ValveSDK::ClientClass *pClass = g_Valve.pClient->GetAllClasses();
						while (pClass)
						{
						const char *pszName = pClass->GetTable()->GetName();
						if (!strcmp(pszName, "DT_BaseViewModel"))
						{
						for (int i = 0; i < pClass->GetTable()->GetNumProps(); i++)
						{
						RecvProp *pProp = pClass->GetTable()->GetPropA(i);

						if (!strcmp(pProp->GetName(), "m_nModelIndex"))
						{
						if (pLocal->GetActiveBaseCombatWeapon()->IsKnife())
						{
						pProp->SetProxyFn(Hooked_RecvProxy_Viewmodel);

						if (g_CVARS.CvarList[KnifeChanger] == 1)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_BAYONET;
						if (g_CVARS.CvarList[KnifeChanger] == 2)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_BUTTERFLY;
						if (g_CVARS.CvarList[KnifeChanger] == 3)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_FLIPKNIFE;
						if (g_CVARS.CvarList[KnifeChanger] == 4)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_GUTKNIFE;
						if (g_CVARS.CvarList[KnifeChanger] == 5)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_KARAMBIT;
						if (g_CVARS.CvarList[KnifeChanger] == 6)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_M9BAYONET;
						if (g_CVARS.CvarList[KnifeChanger] == 7)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_HUNTSMAN;
						if (g_CVARS.CvarList[KnifeChanger] == 8)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_FALCHION;
						if (g_CVARS.CvarList[KnifeChanger] == 9)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_SHADOWD;
						if (g_CVARS.CvarList[KnifeChanger] == 10)
						*(int*)((DWORD)pWeapon + 0x2D70 + 0x40 + 0x1D0) = KNIFE_BOWIE;
						}
						}
						}
						}
						pClass = pClass->NextClass();
						}
						}*/
					}
				}
			}
		}
	}