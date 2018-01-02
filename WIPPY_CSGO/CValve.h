#pragma once
class CValve
{
public:
	VOID initSDK();
	BOOL isInitiated();
	ValveSDK::ISurface* pSurface;
	ValveSDK::IPanel* pPanel;
	ValveSDK::HLCLient* pClient;
	ValveSDK::CEntityList* pEntList;
	ValveSDK::CEngineClient* pEngine;
	ValveSDK::CInput* pInput;
	ValveSDK::EngineTraceClient* g_pEngineTraceClient;
	ValveSDK::IVModelInfo* g_pModel;
	ValveSDK::CPrediction* g_pPred;
	ValveSDK::CGameMovement* g_pGameMovement;
	ValveSDK::IMoveHelper* g_pMoveHelper;
	ValveSDK::CGlobalVars* pGlobalVars;
	ValveSDK::CTrace* pKoloTrace;
	ValveSDK::IVModelRender* pModelRender;
	ValveSDK::IVRenderView* pRenderView;
	ValveSDK::IPhysicsSurfaceProps* pPhysics;
	ValveSDK::IGameEventManager* pGameEventManager;
	ValveSDK::IMaterialSystem* pMaterialSystem;

	ValveSDK::ICVar* pCVar;
	bool WorldToScreen(const Vector &vOrigin, Vector &vScreen);	
	//ValveSDK::CDebugOverlay* pDebugOverlay;
private:
	BOOL m_bInitiated;
private:
}; extern CValve g_Valve;