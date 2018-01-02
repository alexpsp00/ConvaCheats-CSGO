#include "main.h"

Base::Utils::CVMTHookManager g_pClientVMT;
Vector savedangle;

void sayUnrestricted(const char *text)
{
	char buffer[250];
	sprintf_s(buffer, "say \"%s\"", text);
	g_Valve.pEngine->ClientCmd_Unrestricted(buffer);
}

void ChatSpamRegular()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < (g_CVARS.CvarList[SlowChatSpam] ? 1.5 : 0.5))
		return;

	int index = rand() % 15;
	char* msg = "";
	char* nrml = "ConvaCheats Beta ~ rage edition";

	if (index == 1)
		msg = "ROLLING RETARDS LIKE AMERICAN POLICE ROLL NIGGERS";
	if (index == 2)
		msg = "~~~~~ 1tap ~ laff ~~~~~~~~~~~~";
	if (index == 3)
		msg = "dw man im pro if you die to me its allg";
	if (index == 4)
		msg = "where did my walls go?";
	if (index == 5)
		msg = "The victor will never be asked if he told the truth.";
	if (index == 6)
		msg = "damn how do you get so bad? its impressive";
	if (index == 7)
		msg = "wow you paid for that?";
	if (index == 8)
		msg = "you sound hot, i dig fat chicks.";
	if (index == 9)
		msg = "not hacking just good crosshair placement";
	if (index == 10)
		msg = "You Are A Stupid Fucking Cunt.";
	if (index == 11)
		msg = "HAHAHAHAHAHAHHAHAHAHAHAHAHAHAHAHAHAHHAHAHAHAHAHAHHAHAHAHAHAHAHAHAHAHHAHAHAHAHAHAHHAHAHAHAHAHHAHAHAHAHAHHAHAHAHAHAHAHAHAHAHAHHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHHAHAHAHAHAHAHHAHAHAHAHHAHAHA";
	if (index == 12)
		msg = "Interwebz? More like Intergayz.";
	if (index == 13)
		msg = "Aimwhere?.net";
	if (index == 14)
		msg = "valve has detekt haqker in srver xDD";

	if (g_CVARS.CvarList[ChatSpam] == 1)
		sayUnrestricted(nrml);
	if (g_CVARS.CvarList[ChatSpam] == 2)
		sayUnrestricted(msg);

	start_t = clock();
}

void RadioSpamRegular()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < (g_CVARS.CvarList[SlowRadioSpam] ? 1.5 : 0.5))
		return;

	char* msg = "";
	if (g_CVARS.CvarList[RadioSpam] == 1)
		msg = "thanks";
	if (g_CVARS.CvarList[RadioSpam] == 2)
		msg = "getout";

	if (g_CVARS.CvarList[RadioSpam])
	{
		g_Valve.pEngine->ClientCmd_Unrestricted(msg);
	}
	start_t = clock();
}

void namestealer()
{
	static ValveSDK::ConVar* bitch = g_Valve.pCVar->FindVar("name");
	*(int*)((DWORD)&bitch->fnChangeCallback + 0xC) = NULL;

	static bool bean = false;
	if (bean == true) bean = false;
	else bean = true;

	char chCommand[50];
	if (bean) sprintf(chCommand, "name ***ConvaCheats CSGO***\n");
	else sprintf(chCommand, "name ****ConvaCheats CSGO****\n");

	g_Valve.pEngine->ClientCmd_Unrestricted(chCommand);
}


#include "Fakelag Fix/TimeSimulator.h"
void movePacket(int sequence_number, bool &SendPacket)
{
	ValveSDK::CInput::CUserCmd *pUserCmd = &(*(ValveSDK::CInput::CUserCmd**)((DWORD)g_Valve.pInput + USERCMDOFFSET))[sequence_number % MULTIPLAYER_BACKUP];
	ValveSDK::CInput::CVerifiedUserCmd *pVerifiedCmd = &(*(ValveSDK::CInput::CVerifiedUserCmd**)((DWORD)g_Valve.pInput + VERIFIEDCMDOFFSET))[sequence_number % MULTIPLAYER_BACKUP];

	CBaseEntity* pMe = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());

	if (g_CVARS.CvarList[ChatSpam])
	{
		ChatSpamRegular();
	}

	if (g_CVARS.CvarList[RadioSpam])
	{
		RadioSpamRegular();
	}

	if (g_CVARS.CvarList[NameStealer])
	{
		namestealer();
	}

	if (g_Mouse.ActiveMouse)
		pUserCmd->buttons &= ~IN_ATTACK;

	bool bOnGround = pMe->GetFlags() & FL_ONGROUND;
	if (g_CVARS.CvarList[AutoBhop])
	{
		if (pUserCmd->buttons & IN_JUMP)
		{
			int iFlags = pMe->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				pUserCmd->buttons &= ~IN_JUMP;

			/*if (pMe->GetVecVelocity().Length() <= 50)
			{
			pUserCmd->forwardmove = 450.f;
			}*/
		}
	}

	Vector AutoStrafeView = pUserCmd->viewangles;
	if (g_CVARS.CvarList[AutoStrafe] && !(pMe->GetFlags() & FL_ONGROUND))
	{
		static bool bDirection = true;

		float flYawBhop = 0.f;
		if (pMe->GetVecVelocity().Length() > 50.f)
		{
			float x = 30.f, y = pMe->GetVecVelocity().Length(), z = 0.f, a = 0.f;

			z = x / y;
			z = fabsf(z);

			a = x * z;

			flYawBhop = a;
		}

		if (GetAsyncKeyState(VK_SPACE) && !(pMe->GetFlags() & FL_ONGROUND))
		{
			if (bDirection)
			{
				AutoStrafeView.y -= flYawBhop;
				g_Aimbot.NormalizeVector(AutoStrafeView);
				pUserCmd->sidemove = 450.f;
				bDirection = false;
			}
			else
			{
				AutoStrafeView.y += flYawBhop;
				g_Aimbot.NormalizeVector(AutoStrafeView);
				pUserCmd->sidemove = -450.f;
				bDirection = true;
			}

			if (pUserCmd->mousedx < 0.0f)
				pUserCmd->sidemove = -450.f;

			if (pUserCmd->mousedx > 0.0f)
				pUserCmd->sidemove = 450.f;
		}

		g_Aimbot.StrafeCorrection(pUserCmd, pUserCmd->viewangles, AutoStrafeView);
	}

	ValveSDK::CBaseCombatWeapon* pWeapon = pMe->GetActiveBaseCombatWeapon();

	static int iChokedCommands;
	int iMaxChokedCommands = 13;

	if (pWeapon)
	{
		if (g_CVARS.CvarList[TriggerbotActive])
		{
			if (pMe->GetLifeState() == LIFE_ALIVE && !pMe->GetActiveBaseCombatWeapon()->IsMiscWeapon() && !pMe->GetActiveBaseCombatWeapon()->Clip1() == 0)
			{
				static int iTime = 0;

				if (g_CVARS.CvarList[TriggerbotOnKey] > 0)
				{
					if (GetAsyncKeyState(g_CVARS.CvarList[Key_Triggerbot]))
					{
						if (g_Aimbot.Triggerbot(pWeapon, pMe, pUserCmd))
							iTime++;
						else
							iTime = 0;

						if (iTime > g_CVARS.CvarList[TriggerbotDelay])
							pUserCmd->buttons |= IN_ATTACK;
					}
				}
				else
				{
					if (g_Aimbot.Triggerbot(pWeapon, pMe, pUserCmd))
						iTime++;
					else
						iTime = 0;

					if (iTime > g_CVARS.CvarList[TriggerbotDelay])
						pUserCmd->buttons |= IN_ATTACK;
				}
			}
		}

		if (g_CVARS.CvarList[AimbotActive])
		{
			if (pMe->GetLifeState() == LIFE_ALIVE && !pMe->GetActiveBaseCombatWeapon()->IsMiscWeapon() && !pMe->GetActiveBaseCombatWeapon()->Clip1() == 0)
			{
				if (g_CVARS.CvarList[AimbotOnKey] > 0)
				{
					if (GetAsyncKeyState(g_CVARS.CvarList[Key_Aimbot]))
						g_Aimbot.doAim(pUserCmd, SendPacket, pWeapon);
				}
				else
					g_Aimbot.doAim(pUserCmd, SendPacket, pWeapon);

				//yes this supposed to work.
				CTimeSimulator::Get()->Cache();

				if (g_Aimbot.m_pTarget)
					CTimeSimulator::Get()->ProcessCmd(g_Aimbot.m_pTarget->GetIndex(), pUserCmd);


				if (g_CVARS.CvarList[AimbotNoRecoil])
				{
					pUserCmd->viewangles.x -= pMe->GetPunchAngle().x * 2.0f;
					pUserCmd->viewangles.y -= pMe->GetPunchAngle().y * 2.0f;
				}
			}
		}

		float flCurTime = pMe->GetTickBase() * g_Valve.pGlobalVars->interval_per_tick;

		if (g_CVARS.CvarList[AutoPistol])
		{
			if (!pWeapon->IsMiscWeapon())
			{
				if (pWeapon->GetNextPrimaryAttack() >= flCurTime)
					pUserCmd->buttons &= ~IN_ATTACK;
			}
		}

		if (g_CVARS.CvarList[AntiAim] || g_CVARS.CvarList[Spinbot] || g_CVARS.CvarList[FakeLag])
		{
			if (!pWeapon->IsMiscWeapon())
			{
				if (!(flCurTime >= pWeapon->GetNextPrimaryAttack()) || !(pUserCmd->buttons & IN_ATTACK))
					g_Antiaim.doAntiaim(pMe, pUserCmd, SendPacket);
			}
		}

		if (g_CVARS.CvarList[PerfectSilent])
		{
			if ((flCurTime >= pWeapon->GetNextPrimaryAttack()) && (pUserCmd->buttons & IN_ATTACK))
			{
				SendPacket = false;
				iChokedCommands++;
			}
		}
	}

	/*if (pUserCmd->viewangles.z != 0.0f)*/
	if (g_CVARS.CvarList[SafeMode])
		pUserCmd->viewangles.z = 0.0f;

	g_Aimbot.NormalizeVector(pUserCmd->viewangles);
	g_Aimbot.ClampAngles(pUserCmd->viewangles);

	if (g_CVARS.CvarList[AirStuck])
	{
		if (GetAsyncKeyState(g_CVARS.CvarList[Key_Airstuck]))
		{
			if (!(pUserCmd->buttons & IN_ATTACK))
				pUserCmd->tick_count = 0xFFFFF;
		}
	}

	if (iChokedCommands > iMaxChokedCommands)
		SendPacket = true;

	if (SendPacket)
		iChokedCommands = 0;

	if (SendPacket)
	{
		savedangle = pUserCmd->viewangles;
		Global::visualangle.x = pUserCmd->viewangles.x;
		Global::visualangle.y = pUserCmd->viewangles.y;
	}

	pVerifiedCmd->m_cmd = *pUserCmd;
	pVerifiedCmd->m_crc = pUserCmd->GetChecksum();
}

DWORD dwOriginCreateMove;
bool bSendThisPacket;
void __declspec(naked) __stdcall hkdCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	dwOriginCreateMove = g_pClientVMT.dwGetMethodAddress(21);

	__asm
	{
		MOV bSendThisPacket, BL
			PUSH EBP
			MOV EBP, ESP
			SUB ESP, 8
			PUSHAD
			PUSH active
			PUSH input_sample_frametime
			PUSH sequence_number
			CALL dwOriginCreateMove
	}

	movePacket(sequence_number, bSendThisPacket);

	__asm
	{
		POPAD
			MOV BL, bSendThisPacket
			MOV ESP, EBP
			POP EBP
			RETN 0x0C
	}
}

void AAARotateProxy(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	float p = pData->m_Value.m_Float;

	if (p > 179.0f)
		p -= 360.0f;
	if (p < -179.0f)
		p += 360.0f;


	if (p > 90.0f || p < -90.0f)
	{
		p = 90.0f;
	}

	*(float*)pOut = p;
}

void __stdcall hkdHudUpdate(bool active)
{
	static DWORD dwHudUpdateVMT = g_pClientVMT.dwGetMethodAddress(11);
	__asm
	{
		PUSH active
			call dwHudUpdateVMT
	}

	g_NetworkedVariableManager.HookProp("DT_CSPlayer", "m_angEyeAngles[0]", AAARotateProxy);
}