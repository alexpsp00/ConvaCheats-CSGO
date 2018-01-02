#pragma once

class CAntiaim
{
public:

	void AtTarget(ValveSDK::CInput::CUserCmd* Cmd, CBaseEntity* LocalPlayer);
	void FakeLags(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket);
	void Main(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket);
	void doAntiaim(CBaseEntity* pLocal, ValveSDK::CInput::CUserCmd* cmd, bool &SendPacket);
	ValveSDK::CTrace::CTraceFilterNoPlayer tfNoPlayers;

	int iFakeLag = 0;

	Vector vNewAim;
private:
};

extern CAntiaim g_Antiaim;