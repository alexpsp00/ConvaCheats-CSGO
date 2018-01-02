#pragma once

typedef struct
{
	int iDamage;
	float fMaxRange;
	float fRangeModifier;
	float fPenetrationPower;
} WeaponInfo_t;

class CAimbot
{
public:
	void NormalizeVector(Vector& vec);
	void ClampAngles(Vector& vecAngles);
	bool CanWallbang(CBaseEntity* pLocal, CBaseEntity* pEntity, Vector vecStart, Vector vecEnd);
	bool SetupBones(CBaseEntity *pAnimating, matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	bool GetHitbox(Vector &vec, int hitbox, int index);
	bool IsAbleToShoot(CBaseEntity* pLocalClientBaseEntity);
	float GetFov(Vector& vecAngle, Vector& vecOrigin, Vector& vecOther, bool bDistancebased);
	Vector HitScans(CBaseEntity *pLocal, CBaseEntity *pTarget);
	void StrafeCorrection(ValveSDK::CInput::CUserCmd* cmd, Vector& qaView, Vector qaAim);
	float GetDistance(const Vector &vAbsStart, const Vector &vAbsStop);
	VOID doAim(ValveSDK::CInput::CUserCmd* pCmd, bool &SendPacket, ValveSDK::CBaseCombatWeapon *pWeapon);
	inline void VectorTransform(const Vector& in1, const matrix3x4 &in2, Vector &out);
	bool CAimbot::LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos);
	float CAimbot::GenerateRandomFloat(float Min, float Max);

	ValveSDK::CTrace::CTraceFilterNoPlayer tfNoPlayers;

	bool Main_Triggerbot(Vector vSource, Vector qCurAngle, Vector vForward, Vector vRight, Vector vUp, float fMaxDistance, int iLocalTeamNumber, ValveSDK::CBaseCombatWeapon *pWeapon, CBaseEntity *pLocal);
	bool Triggerbot(ValveSDK::CBaseCombatWeapon *pWeapon, CBaseEntity *pLocal, ValveSDK::CInput::CUserCmd* pUserCmd);

	Vector vTargetDest;
	CBaseEntity* m_pTarget;

private:
};

extern CAimbot g_Aimbot;