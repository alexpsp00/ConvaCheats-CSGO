#pragma once
#include "Vector.h"//no.

//Define the game dll..... use the sdk,.....-
#define CSTRIKE_DLL

class CUserCmd;
#ifdef CSTRIKE_DLL
#define MAX_PLAYERS 64
#else
#define MAX_PLAYERS 32
#endif

struct LagRecord_t
{
	LagRecord_t();
	float						m_flSimulationTime;
	bool						m_bValidRecord;
	Vector						m_vecPreviousOrigin;
};

class CTimeSimulator
{
public:
	//Singleton
	static CTimeSimulator*		Get() { static CTimeSimulator m_sTimeSimulator; return &m_sTimeSimulator; }
	void						Cache();
	bool						ProcessCmd(int iTargetIndex, ValveSDK::CInput::CUserCmd* pCmd);

private:
	LagRecord_t					m_PlayerTable[MAX_PLAYERS];
};	