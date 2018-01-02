#include "main.h"
#define M_PI	3.14159265358979323846f
#include "Client.h"
#include "CSpread.h"

CAimbot g_Aimbot;

void CAimbot::NormalizeVector(Vector& vec)
{
	for (int i = 0; i < 3; ++i)
	{
		while (vec[i] > 180.f)
			vec[i] -= 360.f;

		while (vec[i] < -180.f)
			vec[i] += 360.f;
	}

	vec[2] = 0.f;
}

void CAimbot::ClampAngles(Vector& vecAngles)
{
	if (vecAngles[0] > 89.f)
		vecAngles[0] = 89.f;
	if (vecAngles[0] < -89.f)
		vecAngles[0] = -89.f;
	if (vecAngles[1] > 180.f)
		vecAngles[1] = 180.f;
	if (vecAngles[1] < -180.f)
		vecAngles[1] = -180.f;

	vecAngles[2] = 0.f;
}

class TestFilter
{
	virtual bool ShouldHitEntity(CBaseEntity* ent, void* a2)
	{
		if (!strcmp(ent->GetClientClassName().c_str(), "CCSPlayer"))
			return false;

		return true;
	}
	virtual int GetTraceType()
	{
		return 0;
	}

	char pad[8];
};

//bool CAimbot::CanWallbang(CBaseEntity* pLocal, CBaseEntity* pEntity, Vector vecStart, Vector vecEnd)
//{//i didnt add the perfect autowall yet, its right here ok
//
//	/*pSuperBar*/
//	ValveSDK::EngineTraceClient::CTraceFilterSkipTwoEntities TraceFilter(pLocal, pEntity);
//	ValveSDK::EngineTraceClient::Ray_t ray;
//	ray.Init(vecStart, vecEnd);
//
//	ValveSDK::EngineTraceClient::trace_t trace;
//	g_Valve.g_pEngineTraceClient->TraceRay(ray, MASK_SOLID, (ValveSDK::EngineTraceClient::CTraceFilter*)&TraceFilter, &trace);
//
//	Vector vecEndPos[3];
//	vecEndPos[0] = trace.endpos;
//
//	ray.Init(vecEnd, vecStart);
//	g_Valve.g_pEngineTraceClient->TraceRay(ray, MASK_SOLID, (ValveSDK::EngineTraceClient::CTraceFilter*)&TraceFilter, &trace);
//
//	vecEndPos[1] = trace.endpos;
//	VectorSubtract(vecEndPos[0], vecEndPos[1], vecEndPos[2]);
//
//	return (vecEndPos[2].Length() < 19.5f) ? true : false; //autosniper is 19.5
//}

inline bool GetExitPos(Vector src, Vector& start, Vector& dt, ValveSDK::EngineTraceClient::trace_t& exit, TestFilter filter)
{
	ValveSDK::EngineTraceClient::Ray_t ray;
	Vector start2 = start;

	float dist = 0.0f;

	while (dist <= 90.0f)
	{
		dist += 4.0f;
		start2 = src + dt * dist;
		start = start2;

		if (g_Valve.g_pEngineTraceClient->GetPointContents(&start2, MASK_SOLID ^ CONTENTS_GRATE, nullptr) != 0)
			continue;

		ray.Init(start2, (start2 - (dt*4.0f)));

		g_Valve.g_pEngineTraceClient->TraceRay(ray, MASK_SOLID ^ CONTENTS_GRATE, (ValveSDK::EngineTraceClient::CTraceFilter*)&filter, &exit);

		if (exit.startSolid)
			continue;

		if (exit.fraction == 1 && !exit.allSolid && !exit.startSolid)
			continue;

		if (!(exit.contents & CONTENTS_WINDOW))
		{
			if (exit.surface.surfaceProps == 0)
				continue;
		}

		return true;
	}

	return false;
}

inline void GetMatFactor(short props, short& mat, float& pwr)
{

	void* result = g_Valve.pPhysics->GetSurfaceData(props);

	mat = *(short*)((DWORD)result + 84);
	pwr = *(float*)((DWORD)result + 76);
}
#define BASE_OFFSET 0x818
bool CAimbot::CanWallbang(CBaseEntity* pLocal, CBaseEntity* pEntity, Vector vecStart, Vector vecEnd)
{
	ValveSDK::EngineTraceClient::Ray_t ray;
	ValveSDK::EngineTraceClient::trace_t trace;
	ValveSDK::EngineTraceClient::trace_t exit;
	TestFilter TraceFilter;

	Vector Start = vecStart;
	Vector End = vecEnd;
	Vector Delta = End - Start;
	Vector Normal = Delta;
	float Length = Delta.Length();

	if (Length > 0.0f)
		Normal /= Length;

	int Pen = 3;
	float Damage = 0.0f;
	float Range = 0.0f;
	float Dist = 0.0f;

	void* wthis = pLocal->GetActiveBaseCombatWeapon();

	if (!wthis)
		return false;

	typedef void* (__thiscall* fn)(void*);
	void* v1 = ((fn)((*(DWORD**)wthis)[456]))(wthis);

	float wDamage = (float)(*(int*)((DWORD)v1 + (BASE_OFFSET)));
	float wRange = *(float*)((DWORD)v1 + (BASE_OFFSET + 0x4));
	float wRangeModifier = *(float*)((DWORD)v1 + (BASE_OFFSET - 0x18));
	float wPenetration = *(float*)((DWORD)v1 + (BASE_OFFSET - 0x4));

	Damage = wDamage;
	Range = wRange;

	while (true)
	{
		Range = (float)wRange - Dist;
		ray.Init(Start, Start + (Normal * Range));

		g_Valve.g_pEngineTraceClient->TraceRay(ray, MASK_SOLID ^ CONTENTS_GRATE /* How about using the mask the game uses?*/, (ValveSDK::EngineTraceClient::CTraceFilter*)&TraceFilter, &trace);

		float Add = trace.fraction * Range;

		if ((Dist + Add) >= Length)
		{
			Dist += Add;
			Damage *= powf(wRangeModifier, Dist / 500.0f);
			return true;
		}

		Dist += Add;
		Damage *= powf(wRangeModifier, Dist / 500.0f);

		if (Dist > 3000.0f || Pen == 0)
			return false;

		// iterate to unsolid point

		if (!GetExitPos(trace.endpos, End, Normal, exit, TraceFilter))
			return false;

		short in_mat, out_mat;
		float in_mod, out_mod;

		GetMatFactor(trace.surface.surfaceProps, in_mat, in_mod);
		GetMatFactor(exit.surface.surfaceProps, out_mat, out_mod);

		if (in_mod < 0.1f)
			return false;

		// calculate damage from how many units we penetrated

		float len = (exit.endpos - trace.endpos).Length();

		bool solid = !(trace.contents & CONTENTS_DEBRIS);

		if (trace.m_pEnt)
		{
			if (!strcmp(trace.m_pEnt->GetClientClassName().c_str(), "CBreakableSurface"))
				solid = false;
		}

		if (((trace.contents & CONTENTS_GRATE) && (exit.contents & CONTENTS_GRATE)))
			solid = false;

		if (solid)
		{
			{
				float total_mod = (in_mod + out_mod) * 0.5;
				float total_mult = 0.16;

				if (trace.contents & CONTENTS_GRATE || in_mat == 'G')
					total_mult = 0.05;

				if (in_mat == out_mat)
				{
					if (out_mat == 'W' || out_mat == 'U')
						total_mod = 3.0f;
					else if (out_mat == 'L')
						total_mod = 2.0f;
				}

				float mod = 1.0f / total_mod;
				float extra = (Damage * total_mult) + mod * 3.0f * ((3.0f / wPenetration) * 1.25f);

				len *= len;
				len *= mod;
				len /= 24.0f;

				float lost = max(0, len + extra);

				if (lost > Damage)
				{
					Damage = 0.0f;
					return false;
				}

				if (lost > 0.0f)
					Damage -= lost;

				if (Damage < 1.0f)
					return false;
			}
		}

		Start = exit.endpos;
		Pen -= 1;
	}

	return false;
}

bool CAimbot::SetupBones(CBaseEntity *pAnimating, matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	//sick inline assembly benny
	bool bRet;
	__asm
	{
		PUSH currentTime
			PUSH boneMask
			PUSH nMaxBones
			PUSH pBoneToWorldOut
			MOV ECX, DWORD PTR DS : [pAnimating]
			ADD ECX, 4
			MOV EDX, DWORD PTR DS : [pAnimating]
			MOV EAX, DWORD PTR DS : [EDX + 4]
			MOV EDX, DWORD PTR DS : [EAX + 0x34]
			CALL EDX
			MOV bRet, AL
	}
	return bRet;
}

FORCEINLINE float DotProduct(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

enum Hibtox_e
{
	PELVIS = 0,
	L_THIGH,
	L_CALF,
	L_FOOT,
	R_THIGH,
	R_CALF,
	R_FOOT,
	SPINE1,
	SPINE2,
	SPINE3,
	NECK,
	HEAD,
	L_UPPERARM,
	L_FOREARM,
	L_HAND,
	R_UPPERARM,
	R_FOREARM,
	R_HAND,
};

struct Hitbox_t
{
	int       iBone;
	Vector    vMin;
	Vector    vMax;
};

Hitbox_t    Hitbox[18];

void SetupHitbox(void)
{
	Hitbox[PELVIS].vMin = Vector(-6.420f, -4.280f, -6.955f);
	Hitbox[PELVIS].vMax = Vector(4.280f, 4.280f, 6.955f);
	Hitbox[PELVIS].iBone = 0;

	Hitbox[L_THIGH].vMin = Vector(5.029f, -3.959f, -2.140f);
	Hitbox[L_THIGH].vMax = Vector(22.149f, 3.424f, 4.280f);
	Hitbox[L_THIGH].iBone = 26;

	Hitbox[L_CALF].vMin = Vector(2.675f, -3.210f, -2.247f);
	Hitbox[L_CALF].vMax = Vector(19.260f, 2.675f, 2.247f);
	Hitbox[L_CALF].iBone = 27;

	Hitbox[L_FOOT].vMin = Vector(2.943f, -2.675f, -2.408f);
	Hitbox[L_FOOT].vMax = Vector(6.688f, 9.095f, 2.408f);
	Hitbox[L_FOOT].iBone = 28;

	Hitbox[R_THIGH].vMin = Vector(5.029f, -3.959f, -4.280f);
	Hitbox[R_THIGH].vMax = Vector(22.149f, 3.424f, 2.140f);
	Hitbox[R_THIGH].iBone = 23;

	Hitbox[R_CALF].vMin = Vector(5.029f, -3.959f, -4.280f);
	Hitbox[R_CALF].vMax = Vector(22.149f, 3.424f, 2.140f);
	Hitbox[R_CALF].iBone = 24;

	Hitbox[R_FOOT].vMin = Vector(2.943f, -2.675f, -2.408f);
	Hitbox[R_FOOT].vMax = Vector(6.688f, 9.095f, 2.408f);
	Hitbox[R_FOOT].iBone = 25;

	Hitbox[SPINE1].vMin = Vector(-4.280f, -4.280f, -5.885f);
	Hitbox[SPINE1].vMax = Vector(3.210f, 5.350f, 5.885f);
	Hitbox[SPINE1].iBone = 2;

	Hitbox[SPINE2].vMin = Vector(-4.280f, -4.280f, -5.885f);
	Hitbox[SPINE3].vMax = Vector(3.210f, 5.350f, 5.885f);
	Hitbox[SPINE3].iBone = 3;

	Hitbox[SPINE3].vMin = Vector(-4.280f, -4.280f, -5.885f);
	Hitbox[SPINE3].vMax = Vector(6.420f, 5.350f, 5.885f);
	Hitbox[SPINE3].iBone = 4;

	Hitbox[NECK].vMin = Vector(-1.070f, -2.622f, -2.151f);
	Hitbox[NECK].vMax = Vector(3.103f, 2.622f, 2.151f);
	Hitbox[NECK].iBone = 5;

	Hitbox[HEAD].vMin = Vector(-2.140f, -3.745f, -3.670f);
	Hitbox[HEAD].vMax = Vector(6.955f, 3.745f, 3.670f);
	Hitbox[HEAD].iBone = 10;

	Hitbox[L_UPPERARM].vMin = Vector(-2.675f, -3.210f, -2.140f);
	Hitbox[L_UPPERARM].vMax = Vector(12.840f, 3.210f, 2.140f);
	Hitbox[L_UPPERARM].iBone = 7;

	Hitbox[L_FOREARM].vMin = Vector(-0.000f, -2.140f, -2.140f);
	Hitbox[L_FOREARM].vMax = Vector(9.630f, 2.140f, 2.140f);
	Hitbox[L_FOREARM].iBone = 8;

	Hitbox[L_HAND].vMin = Vector(-1.723f, -1.220f, -1.380f);
	Hitbox[L_HAND].vMax = Vector(4.473f, 1.220f, 1.380f);
	Hitbox[L_HAND].iBone = 9;

	Hitbox[R_UPPERARM].vMin = Vector(-2.675f, -3.210f, -2.140f);
	Hitbox[R_UPPERARM].vMax = Vector(12.840f, 3.210f, 2.140f);
	Hitbox[R_UPPERARM].iBone = 13;

	Hitbox[R_FOREARM].vMin = Vector(-0.000f, -2.140f, -2.140f);
	Hitbox[R_FOREARM].vMax = Vector(9.630f, 2.140f, 2.140f);
	Hitbox[R_FOREARM].iBone = 14;

	Hitbox[R_HAND].vMin = Vector(-1.723f, -1.220f, -1.380f);
	Hitbox[R_HAND].vMax = Vector(4.473f, 1.220f, 1.380f);
	Hitbox[R_HAND].iBone = 15;
}

void VectorTransformm(const float *in1, const matrix3x4& in2, float *out)
{
	Assert(s_bMathlibInitialized);
	Assert(in1 != out);
	out[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out[2] = DotProduct(in1, in2[2]) + in2[2][3];
}

inline void VectorTransform(const Vector& in1, const matrix3x4 &in2, Vector &out)
{
	VectorTransformm(&in1.x, in2, &out.x);
}

float CAimbot::GenerateRandomFloat(float Min, float Max)
{
	float randomized = (float)rand() / (float)RAND_MAX;
	return Min + randomized * (Max - Min);
}

bool CAimbot::GetHitbox(Vector &vec, int hitbox, int index)
{
	static bool bDidOnce = false;

	if (!bDidOnce)
	{
		SetupHitbox();
		bDidOnce = true;
	}
	matrix3x4 matrix[128];
	float min[3];
	float max[3];

	//use the sdk defines
	if (!SetupBones(g_Valve.pEntList->GetClientEntity(index), matrix, 128, 0x00000100, 0.0f))
		return false;

	float flIn[3] = { Hitbox[hitbox].vMin[0], Hitbox[hitbox].vMin[1], Hitbox[hitbox].vMin[2] };
	float flIn2[3] = { Hitbox[hitbox].vMax[0], Hitbox[hitbox].vMax[1], Hitbox[hitbox].vMax[2] };
	VectorTransformm(flIn, matrix[Hitbox[hitbox].iBone], min);
	VectorTransformm(flIn2, matrix[Hitbox[hitbox].iBone], max);

	//AHAHAH WTF?
	//BENNY WTF IS THIS? its just something that shakes on your head nigga
	//nice hvh feature.
	vec[0] = (min[0] + max[0]) / 2;
	vec[1] = (min[1] + max[1]) / 2;
	vec[2] = (min[2] + max[2]) / 2;

	vec[2] += 5;

	if (g_CVARS.CvarList[AimbotMultiSpot])
	{
		vec[0] += GenerateRandomFloat(-g_CVARS.CvarList[AimbotMultiSpotLength], g_CVARS.CvarList[AimbotMultiSpotLength]);
		vec[1] += GenerateRandomFloat(-g_CVARS.CvarList[AimbotMultiSpotLength], g_CVARS.CvarList[AimbotMultiSpotLength]);
		vec[2] += GenerateRandomFloat(-g_CVARS.CvarList[AimbotMultiSpotLength], g_CVARS.CvarList[AimbotMultiSpotLength]);
	}

	return true;
}

bool CAimbot::IsAbleToShoot(CBaseEntity* pLocalClientBaseEntity)
{
	if (IsNullPtr(pLocalClientBaseEntity))
		return false;
	//is this psilent supposed to work?
	//well I can definiatly tell you that this looks retarded as fuck but excluding the fact that you
	//are not checking the CombatCharacter::NextAttack it is ok.
	if (!pLocalClientBaseEntity->isValidPlayer())
		return false;

	if (IsNullPtr(pLocalClientBaseEntity->GetActiveBaseCombatWeapon()))
		return false;

	float flServerTime = (float)pLocalClientBaseEntity->GetTickBase() * g_Valve.pGlobalVars->interval_per_tick;
	float flNextPrimaryAttack = pLocalClientBaseEntity->GetActiveBaseCombatWeapon()->GetNextPrimaryAttack();

	return(!(flNextPrimaryAttack > flServerTime));
}

void CalculateAngles(Vector& vecOrigin, Vector& vecOther, Vector& vecAngles)
{
	Vector vecDelta = Vector((vecOrigin[0] - vecOther[0]), (vecOrigin[1] - vecOther[1]), (vecOrigin[2] - vecOther[2]));
	float hyp = sqrtf(vecDelta[0] * vecDelta[0] + vecDelta[1] * vecDelta[1]);

	vecAngles[0] = (float)atan(vecDelta[2] / hyp) * (float)(180.f / M_PI);
	vecAngles[1] = (float)atan(vecDelta[1] / vecDelta[0])	* (float)(180.f / M_PI);
	vecAngles[2] = (float)0.f;

	if (vecDelta[0] >= 0.f)
		vecAngles[1] += 180.f;

	vecAngles[2] = 0.f;
}

void MakeVector(Vector& vecAngle, Vector& out)
{
	float pitch = float(vecAngle[0] * M_PI / 180.f);
	float tmp = float(cos(pitch));
	float yaw = float(vecAngle[1] * M_PI / 180.f);
	out[0] = float(-tmp * -cos(yaw));
	out[1] = float(sin(yaw)*tmp);
	out[2] = float(-sin(pitch));
}

void CAimbot::StrafeCorrection(ValveSDK::CInput::CUserCmd* cmd, Vector& qaView, Vector qaAim)
{
	FLOAT flMove[3];
	flMove[0] = cmd->forwardmove;
	flMove[1] = cmd->sidemove;
	flMove[2] = cmd->upmove;

	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);

	FLOAT flMoveNorm[3];
	g_Math.vectorAngles(flMove, flMoveNorm);

	Vector vMoveNorm(flMoveNorm[0], flMoveNorm[1], flMoveNorm[2]);

	Vector vAdjusted = vMoveNorm + (qaAim - qaView);

	FLOAT flAdjusted[3];
	flAdjusted[0] = vAdjusted.x;
	flAdjusted[1] = vAdjusted.y;
	flAdjusted[2] = vAdjusted.z;

	FLOAT flForward[3];
	FLOAT flSide[3];
	FLOAT flUp[3];

	g_Math.angleVectors(flAdjusted, flForward, flSide, flUp);

	Vector vForward(flForward[0], flForward[1], flForward[2]);
	Vector vSet = vForward * vMove.Length();

	cmd->forwardmove = vSet.x;
	cmd->sidemove = vSet.y;
}


float CAimbot::GetFov(Vector& vecAngle, Vector& vecOrigin, Vector& vecOther, bool bDistancebased)
{
	Vector ang, aim;
	double fov;

	CalculateAngles(vecOrigin, vecOther, ang);
	MakeVector(vecAngle, aim);
	MakeVector(ang, ang);

	float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
	float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));

	float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.f / M_PI);

	fov *= 1.4;

	if (bDistancebased)
	{
		float xDist = abs(vecOrigin[0] - vecOther[0]);
		float yDist = abs(vecOrigin[1] - vecOther[1]);
		float Distance = sqrt((xDist * xDist) + (yDist * yDist));

		Distance /= 650.f;

		if (Distance < 0.7f)
			Distance = 0.7f;

		if (Distance > 6.5)
			Distance = 6.5;

		fov *= Distance;
	}

	return (float)fov;
}

float CAimbot::GetDistance(const Vector &vAbsStart, const Vector &vAbsStop)
{
	float flLength = Vector(vAbsStop - vAbsStart).Length();
	float flDistance = sqrt(flLength);

	if (flDistance < 1.0f)
		flDistance = 1.0f;

	return flDistance;
}

bool CAimbot::LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos)
{
	typedef bool(__cdecl* oLineGoesThroughSmoke) (Vector, Vector);
	static oLineGoesThroughSmoke LineGoesThroughSmoke = (oLineGoesThroughSmoke)(Base::Utils::PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x44\x8B\x15", "xxxxxxxx", NULL, NULL));

	return LineGoesThroughSmoke(vStartPos, vEndPos);
}

/*VOID!!! wtf this winapi style*/
VOID CAimbot::doAim(ValveSDK::CInput::CUserCmd* pCmd, bool &SendPacket, ValveSDK::CBaseCombatWeapon *pWeapon)
{
	float AIMBOT_FOV = g_CVARS.CvarList[AimbotFOV];

	float flAim[3];
	float MaxDistance = 99999;

	static int iTime = 0;

	INT besttarget = -1;
	CBaseEntity* BestTarget = nullptr;
	CBaseEntity* pLocal = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
	Vector vLocalEye = pLocal->GetEyePosition();
	Vector vCurrentView;

	if (!pLocal)
		return;

	float BestDist = 99999;
	int bHitbox = 10;

	m_pTarget = NULL;

	for (INT i = 1; i < g_Valve.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pBaseEntity = g_Valve.pEntList->GetClientEntity(i);
		if (pBaseEntity && pBaseEntity->isValidPlayer() && pLocal->isValidPlayer())
		{
			float flDist = GetDistance(pLocal->GetAbsOrigin(), pBaseEntity->GetAbsOrigin());
			if (flDist > g_CVARS.CvarList[AimbotMaxDist])
				continue;
			if (flDist < g_CVARS.CvarList[AimbotMinDist])
				continue;

			if (g_CVARS.CvarList[AimbotIgnoreJumpers])
			{
				if (!(pBaseEntity->GetFlags() & FL_ONGROUND) || !(pLocal->GetFlags() & FL_ONGROUND))
					continue;
			}

			if (g_CVARS.CvarList[AimbotAntiDM])
			{
				if (pBaseEntity->IsSpawnProtected())
					continue;
			}

			Vector vTargetDest;

			GetHitbox(vTargetDest, 10, i);

			Vector vAimspot = vTargetDest - vLocalEye;

			float flAimspot[3];
			flAimspot[0] = vAimspot.x;
			flAimspot[1] = vAimspot.y;
			flAimspot[2] = vAimspot.z;

			g_Math.vectorAngles(flAimspot, flAim);
			Vector vAim(flAim[0], flAim[1], flAim[2]);

			bool ableToHitEnemy;
			if (g_CVARS.CvarList[AimbotWallBang])
				ableToHitEnemy = pWeapon->IsShotgun() ? g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity) 
				: g_Aimbot.CanWallbang(pLocal, pBaseEntity, pLocal->GetEyePosition(), vTargetDest)
				|| g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity);
			else
				ableToHitEnemy = g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity);

			if (pBaseEntity->GetTeam() == 3 || pBaseEntity->GetTeam() == 2)
			{
				if (GetFov(pCmd->viewangles, vLocalEye, vTargetDest, true) <= AIMBOT_FOV
					&& (ableToHitEnemy)
					&& (!g_CVARS.CvarList[AimbotTeamAim] && pLocal->GetTeam() != pBaseEntity->GetTeam() || g_CVARS.CvarList[AimbotTeamAim])
					&& (g_CVARS.CvarList[AimbotIgnoreThroughSmoke] && !LineGoesThroughSmoke(vLocalEye, vTargetDest) || !g_CVARS.CvarList[AimbotIgnoreThroughSmoke]))
				{
					if (GetFov(pCmd->viewangles, vLocalEye, vTargetDest, false) <= MaxDistance)
					{
						MaxDistance = GetFov(pCmd->viewangles, vLocalEye, vTargetDest, false);
						besttarget = i;
					}
				}
			}
		}
	}
	CBaseEntity* pBaseEntity = g_Valve.pEntList->GetClientEntity(besttarget);
	BestTarget = pBaseEntity;

	if (pBaseEntity && pBaseEntity->isValidPlayer() && pLocal->isValidPlayer() && besttarget > 0)
	{
		GetHitbox(vTargetDest, 10, besttarget);

		Vector vAimspot = vTargetDest - vLocalEye;

		float flAimspot[3];
		flAimspot[0] = vAimspot.x;
		flAimspot[1] = vAimspot.y;
		flAimspot[2] = vAimspot.z;

		g_Math.vectorAngles(flAimspot, flAim);
		Vector vAim(flAim[0], flAim[1], flAim[2]);

		bool ableToHitEnemy;
		if (g_CVARS.CvarList[AimbotWallBang])
			ableToHitEnemy = pWeapon->IsShotgun() ? g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity)
			: g_Aimbot.CanWallbang(pLocal, pBaseEntity, pLocal->GetEyePosition(), vTargetDest)
			|| g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity);
		else
			ableToHitEnemy = g_Valve.g_pEngineTraceClient->IsVisible(pLocal, pLocal->GetEyePosition(), vTargetDest, pBaseEntity);

		if (pBaseEntity->GetTeam() == 3 || pBaseEntity->GetTeam() == 2)
		{
			if (vTargetDest != Vector(0.0f, 0.0f, 0.0f)
				&& GetFov(pCmd->viewangles, vLocalEye, vTargetDest, true) <= AIMBOT_FOV 
&& (ableToHitEnemy)
				&& (!g_CVARS.CvarList[AimbotTeamAim] && pLocal->GetTeam() != pBaseEntity->GetTeam() || g_CVARS.CvarList[AimbotTeamAim])
				&& (g_CVARS.CvarList[AimbotIgnoreThroughSmoke] && !LineGoesThroughSmoke(vLocalEye, vTargetDest) || !g_CVARS.CvarList[AimbotIgnoreThroughSmoke]))
			{
				if (!pWeapon->IsShotgun()
					&& pWeapon->GetWeaponID() != awp
					&& pWeapon->GetWeaponID() != ssg08 
					&& pWeapon->GetWeaponID() != deagle
					&& g_CVARS.CvarList[AimbotRCS]
					&& g_CVARS.CvarList[AimbotRCSScale] > 0)
				{
					float flDist = GetDistance(pLocal->GetAbsOrigin(), pBaseEntity->GetAbsOrigin());
					if (flDist < g_CVARS.CvarList[AimbotRCSMaxDist] && flDist > g_CVARS.CvarList[AimbotRCSMinDist])
					{
						float Scale = g_CVARS.CvarList[AimbotRCSScale] / 100;
						float RecoilScale = 2.0f / Scale;

						vAim.x -= pLocal->GetPunchAngle().x * RecoilScale;
						vAim.y -= pLocal->GetPunchAngle().y * RecoilScale;
					}
				}

				//just on a side note, you definiatly have not tought trough making this target selection/validation algorthm

				Vector vHitbox;
				GetHitbox(vHitbox, bHitbox, BestTarget->GetIndex());
				m_pTarget = BestTarget;  //now it supposed to work.

				Vector vOldView = pCmd->viewangles;
				float flOldSidemove = pCmd->sidemove;
				float flOldForwardmove = pCmd->forwardmove;
				StrafeCorrection(pCmd, pCmd->viewangles, vAim); //sick.

				if (g_CVARS.CvarList[AimbotAutoStop])
				{
					pCmd->forwardmove = 0;
					pCmd->sidemove = 0;
				}

				if (g_CVARS.CvarList[AimbotAutoCrouch])
					pCmd->buttons |= IN_DUCK;

				pCmd->viewangles = vAim;

				if (!pLocal->GetScope() && (pWeapon->IsSniper() || pWeapon->GetWeaponID() == aug || pWeapon->GetWeaponID() == sg553) && g_CVARS.CvarList[AimbotScope])
					pCmd->buttons = IN_ATTACK2;

				//==============================================//
				int iSmoothness = (g_CVARS.CvarList[AimbotSmooth] + 1);
				if (iSmoothness <= 1) iSmoothness = 1;
				if (iSmoothness >= 30) iSmoothness = 30;

				if (g_CVARS.CvarList[AimbotSmooth] > 0)
				{
					Vector qCurrentView, qDelta;
					g_Valve.pEngine->GetViewAngles(qCurrentView);
					qDelta = pCmd->viewangles - qCurrentView;

					NormalizeVector(qDelta);
					pCmd->viewangles = qCurrentView + qDelta / iSmoothness;
					NormalizeVector(pCmd->viewangles);			
				}


				g_Valve.pEngine->GetViewAngles(vCurrentView);
				Vector vDelta = pCmd->viewangles - vCurrentView;
				if (g_CVARS.CvarList[AntiAUTH])
				{
					//..... wtf?
					float flRandSmooth = 3;

					if (vDelta[0] > flRandSmooth)
						pCmd->viewangles[0] = vCurrentView[0] + flRandSmooth;
					else if (vDelta[0] < -flRandSmooth)
						pCmd->viewangles[0] = vCurrentView[0] - flRandSmooth;
					if (vDelta[1] > flRandSmooth)
						pCmd->viewangles[1] = vCurrentView[1] + flRandSmooth;
					else if (vDelta[1] < -flRandSmooth)
						pCmd->viewangles[1] = vCurrentView[1] - flRandSmooth;
				}

				//==============================================//

				pCmd->viewangles.z = 0.0f;

				Vector vPunchAngle = pLocal->GetPunchAngle();
				int iRecoilLength = (int)abs(vPunchAngle.Length());
				float iMinRecoilz = 2.0f / g_CVARS.CvarList[LimitRecoilMax];
				if (iRecoilLength <= iMinRecoilz)
					iTime++;
				else
					iTime = 0;

				if (g_CVARS.CvarList[AimbotAutoShoot]
					&& (g_CVARS.CvarList[AimbotLimitRecoil] && iTime > g_CVARS.CvarList[LimitRecoilDelay] || !g_CVARS.CvarList[AimbotLimitRecoil]))
					pCmd->buttons |= IN_ATTACK;

				if (g_CVARS.CvarList[AimbotShootOnKey] && GetAsyncKeyState(g_CVARS.CvarList[AimbotOnKey])
					&& (g_CVARS.CvarList[AimbotLimitRecoil] && iTime > g_CVARS.CvarList[LimitRecoilDelay] || !g_CVARS.CvarList[AimbotLimitRecoil]))
					pCmd->buttons |= IN_ATTACK;

				if (!g_CVARS.CvarList[AimbotSilent])
					g_Valve.pEngine->SetViewAngles(pCmd->viewangles);

				if (!g_CVARS.CvarList[SafeMode])
				{
					if (g_CVARS.CvarList[PerfectSilent])
					{
						if (IsAbleToShoot(pLocal))
							SendPacket = false;
						else
						{
							SendPacket = true;
							pCmd->viewangles = vOldView;
							NormalizeVector(pCmd->viewangles);
							ClampAngles(pCmd->viewangles);
							pCmd->sidemove = flOldSidemove;
							pCmd->forwardmove = flOldForwardmove;
						}
					}
				}
			}
			else
			{
				iTime = 0;
			}
		}
	}

	if (iTime >= INT_MAX)
		iTime = 0;
}

void angleVectors(Vector angles, Vector &f)
{
	float sp, sy, sr, cp, cy, cr;

	g_Math.sinCos(DEG2RAD(angles[0]), &sp, &cp);
	g_Math.sinCos(DEG2RAD(angles[1]), &sy, &cy);
	g_Math.sinCos(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;
}

void angleVectors2(Vector angles, Vector &f, Vector &r, Vector &u)
{
	float sp, sy, sr, cp, cy, cr;

	g_Math.sinCos(DEG2RAD(angles[0]), &sp, &cp);
	g_Math.sinCos(DEG2RAD(angles[1]), &sy, &cy);
	g_Math.sinCos(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;

	r[0] = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
	r[1] = -1.0f * sr * sp * sy + -1.0f * cr * cy;
	r[2] = -1.0f * sr * cp;

	u[0] = cr * sp * cy + -sr * -sy;
	u[1] = cr * sp * sy + -sr * cy;
	u[2] = cr * cp;
}

bool CAimbot::Main_Triggerbot(Vector vSource, Vector qCurAngle, Vector vForward, Vector vRight, Vector vUp, float fMaxDistance, int iLocalTeamNumber, ValveSDK::CBaseCombatWeapon *pWeapon, CBaseEntity *pLocal)
{
	static bool bBurst;

	bool bRet = false;

	ValveSDK::CTrace::trace_t tr;
	ValveSDK::CTrace::Ray_t ray;

	Vector vEnd;
	angleVectors(qCurAngle, vEnd);

	vEnd = vSource + (vEnd * fMaxDistance);

	ValveSDK::CTrace::CSimpleTraceFilter tfSimple(pLocal);
	ray.Init(vSource, vEnd);
	g_Valve.pKoloTrace->TraceRay(ray, 0x46004003, (ValveSDK::CTrace::ITraceFilter*)&tfSimple, &tr);

	bool bNowBurst = false;
	static DWORD fTimer = GetTickCount();

	if (tr.m_pEnt && tr.m_pEnt->IsPlayer())
	{
		if ((tr.m_pEnt->GetTeam() != iLocalTeamNumber)
			&& (g_CVARS.CvarList[TriggerbotHead] && tr.hitgroup == 1 || !g_CVARS.CvarList[TriggerbotHead])
			&& (g_CVARS.CvarList[TriggerbotIgnoreArmsLegs] && tr.hitgroup != 4 && tr.hitgroup != 5 && tr.hitgroup != 6 && tr.hitgroup != 7 || !g_CVARS.CvarList[TriggerbotIgnoreArmsLegs])
			&& (g_CVARS.CvarList[TriggerbotSniper] && pWeapon->IsSniper() || !g_CVARS.CvarList[TriggerbotSniper])
			&& (g_CVARS.CvarList[TriggerbotOnlyWhenScoped] && (pWeapon->IsSniper() && pLocal->GetScope()) || !g_CVARS.CvarList[TriggerbotOnlyWhenScoped] && pWeapon->IsSniper() || !pWeapon->IsSniper()))
		{
			bRet = true;

			fTimer = 0;
			bBurst = true;
			bNowBurst = true;
		}
	}

	if (!bNowBurst && bBurst)
	{
		fTimer = GetTickCount() + (int)GenerateRandomFloat(g_CVARS.CvarList[TriggerbotOverBurst] * 100.f, g_CVARS.CvarList[TriggerbotOverBurst] * 100.f);
		bBurst = false;
	}

	bool ShouldBurst = (g_CVARS.CvarList[TriggerbotOverBurst] > 0 && pWeapon->GetWeaponID() != awp && pWeapon->GetWeaponID() != ssg08);

	if (ShouldBurst && fTimer > GetTickCount())
		bRet = true;

	return bRet;
}

bool CAimbot::Triggerbot(ValveSDK::CBaseCombatWeapon *pWeapon, CBaseEntity *pLocal, ValveSDK::CInput::CUserCmd* pUserCmd)
{
	Vector vEyePosition = pLocal->GetEyePosition();
	Vector qCurAngle = pUserCmd->viewangles;

	Vector vForward, vRight, vUp;
	angleVectors2(qCurAngle, vForward, vRight, vUp);

	int iMyTeam = pLocal->GetTeam();

	for (INT ax = 1; ax <= g_Valve.pEngine->GetMaxClients(); ax++)
	{
		CBaseEntity* pBaseEntity = g_Valve.pEntList->GetClientEntity(ax);

		if (!pBaseEntity
			|| !pBaseEntity->isValidPlayer()
			|| pBaseEntity == pLocal)
			continue;
	}

	return Main_Triggerbot(vEyePosition, qCurAngle, vForward, vRight, vUp, 8192.0f, iMyTeam, pWeapon, pLocal);
}