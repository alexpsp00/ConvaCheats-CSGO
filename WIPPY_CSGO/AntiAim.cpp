#include "main.h"
#define M_PI	3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )

CAntiaim g_Antiaim;

void CalcAngle(Vector &vSource, Vector &vDestination, Vector &qAngle)
{
	Vector vDelta = vSource - vDestination;

	float fHyp = (vDelta.x * vDelta.x) + (vDelta.y * vDelta.y);

	float fRoot;

	__asm
	{
		sqrtss xmm0, fHyp
			movss fRoot, xmm0
	}

	qAngle.x = RAD2DEG(atan(vDelta.z / fRoot));
	qAngle.y = RAD2DEG(atan(vDelta.y / vDelta.x));

	if (vDelta.x >= 0.0f) qAngle.y += 180.0f;

	g_Aimbot.NormalizeVector(qAngle);
}

void CAntiaim::AtTarget(ValveSDK::CInput::CUserCmd* Cmd, CBaseEntity* LocalPlayer)
{
	if (!LocalPlayer)
		return;

	Vector EyePos = LocalPlayer->GetEyePosition();

	for (int i = 1; i <= g_Valve.pGlobalVars->maxclients; ++i)
	{
		CBaseEntity* pBaseEntity = g_Valve.pEntList->GetClientEntity(i);

		if (!pBaseEntity
			|| !pBaseEntity->isValidPlayer()
			|| pBaseEntity == LocalPlayer
			|| (g_CVARS.CvarList[AimbotAntiDM] && pBaseEntity->IsSpawnProtected()) // Spawn Protection
			|| (!g_CVARS.CvarList[AimbotTeamAim] && pBaseEntity->GetTeam() == LocalPlayer->GetTeam())) // Team Aim
			continue;

		CalcAngle(EyePos, g_Aimbot.vTargetDest, vNewAim);
	}
}

void CAntiaim::FakeLags(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket)
{
	int iFakeLagTickLimit = 9 + 4;
	if (iFakeLag > iFakeLagTickLimit)
		iFakeLag = 1;
	else
		iFakeLag = iFakeLag + 1;

	if (4 >= iFakeLag)
		SendPacket = true;
	else
		SendPacket = false;
}

void CAntiaim::Main(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket)
{
	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vMove2;
	Vector vRealView(cmd->viewangles);
	wippyhack_anglestuff::VectorAngles3D(vMove, vMove2);

	if (g_CVARS.CvarList[AntiAim])
	{
		if (g_CVARS.CvarList[AntiAimX] == 1)
		{
			cmd->viewangles.x = 89.000000;
		}
		else if (g_CVARS.CvarList[AntiAimX] == 2)
		{
			cmd->viewangles.x = 36000088.000000;
		}
		else if (g_CVARS.CvarList[AntiAimX] == 3)
		{
			cmd->viewangles.x = 89.000000;
		}
		else if (g_CVARS.CvarList[AntiAimX] == 4)
		{
			cmd->viewangles.x = 35999912.000000;
		}
		else if (g_CVARS.CvarList[AntiAimX] == 5)
		{
			cmd->viewangles.x = 0;
		}


		//============================================================================================//


		if (g_CVARS.CvarList[AntiAimY] == 1)
		{
			cmd->viewangles.y += 180;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 2)
		{
			if (!(cmd->command_number % 2))
			{
				cmd->viewangles += 180.0;
			}
		}
		else if (g_CVARS.CvarList[AntiAimY] == 3)
		{
			int v36 = cmd->command_number % 3;
			if (v36 == 1)
			{
				cmd->viewangles.y -= 160.0;
			}
			else if (v36 == 2)
			{
				cmd->viewangles.y -= 200.0;
			}
		}
		else if (g_CVARS.CvarList[AntiAimY] == 4)
		{
			if (cmd->command_number % 3)
				cmd->viewangles.y += 200.0;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 5)
		{
			cmd->viewangles.y += 90.0;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 6)
		{
			if (cmd->command_number % 2)
			{
				cmd->viewangles.y += 90.0;
			}
			else
			{
				cmd->viewangles.y -= 90.0;
			}
		}
		else if (g_CVARS.CvarList[AntiAimY] == 7)
		{
			if (!(cmd->command_number % 2))
			{
				cmd->viewangles.y += 180.0;
			}
		}
		else if (g_CVARS.CvarList[AntiAimY] == 8)
		{
			float CalculatedCurTime = (g_Valve.pGlobalVars->curtime * 1000.0);
			cmd->viewangles.y = CalculatedCurTime;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 9)
		{
			float CalculatedCurTime_1 = (g_Valve.pGlobalVars->curtime * 5000.0);
			cmd->viewangles.y = CalculatedCurTime_1;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 10)
		{
			cmd->viewangles.y += 36000180.0;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 11)
		{
			cmd->viewangles.y = 36000180.000000;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 12)
		{
			float v42 = (g_Valve.pGlobalVars->curtime * 5000.0);
			cmd->viewangles.y = v42 + 36000000.0;
		}
		else if (g_CVARS.CvarList[AntiAimY] == 13)
		{
			if (cmd->command_number % 2)
			{
				cmd->viewangles.y = cmd->viewangles.y + 36000180.0;
			}
			float CalculatedCurTime_2 = (g_Valve.pGlobalVars->curtime * 5000.0);
			cmd->viewangles.y = CalculatedCurTime_2 + 36000000.0;
		}

		//============================================================================================//


		if (g_CVARS.CvarList[AntiAimFollowTarget])
		{
			AtTarget(cmd, pLocal);
			cmd->viewangles.y -= vNewAim.y;
		}
	}

	if (g_CVARS.CvarList[Spinbot])
		cmd->viewangles.y += (float)(fmod(g_Valve.pEngine->Time() / 0.4f * 360, 360));

	flYaw = DEG2RAD(cmd->viewangles.y - vRealView.y + vMove2.y);
	cmd->forwardmove = cos(flYaw) * flSpeed;
	cmd->sidemove = sin(flYaw) * flSpeed;
}

void CAntiaim::doAntiaim(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket)
{
	if (g_CVARS.CvarList[FakeLag])
		FakeLags(pLocal, cmd, SendPacket);

	if (g_CVARS.CvarList[AntiAim] || g_CVARS.CvarList[Spinbot])
		Main(pLocal, cmd, SendPacket);
}