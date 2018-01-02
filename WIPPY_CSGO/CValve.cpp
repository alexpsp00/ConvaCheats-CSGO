#include "main.h"

ValveSDK::CBaseCombatWeapon* CBaseEntity::GetActiveBaseCombatWeapon()
{
	static int iOffset = g_NetworkedVariableManager.GetOffset("DT_CSPlayer", "m_hActiveWeapon");
	ULONG pWeepEhandle = *(PULONG)((DWORD)this + iOffset);
	return (ValveSDK::CBaseCombatWeapon*)(g_Valve.pEntList->GetClientEntityFromHandle(pWeepEhandle));
}

void* GetInterfacePtr(const char* interfaceName, const char* ptrName, CreateInterface_t pInterface)
{

	char szDebugString[1024];

	std::string sinterface = "";
	std::string interfaceVersion = "0";

	for (int i = 0; i <= 99; i++)
	{
		sinterface = interfaceName;
		sinterface += interfaceVersion;
		sinterface += std::to_string(i);

		void* funcPtr = pInterface(sinterface.c_str(), NULL);

		if ((DWORD)funcPtr != 0x0)
		{

			sprintf_s(szDebugString, "%s: 0x%x (%s%s%i)", ptrName, (DWORD)funcPtr, interfaceName, interfaceVersion.c_str(), i);
			Base::Debug::LOG(szDebugString);

			return funcPtr;
		}
		if (i >= 99 && interfaceVersion == "0")
		{
			interfaceVersion = "00";
			i = 0;
		}
		else if (i >= 99 && interfaceVersion == "00")
		{
			sprintf_s(szDebugString, "%s: 0x%x (error)", ptrName, (DWORD)funcPtr);
			Base::Debug::LOG(szDebugString);

		}
	}
	return 0;
}

bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
{
	for (; *szMask; ++szMask, ++Mask, ++Data)
	{
		if (*szMask == 'x' && *Mask != *Data)
		{
			return false;
		}
	}
	return (*szMask) == 0;
}

HMODULE GetModuleHandleSafe(const char* pszModuleName)
{
	HMODULE hmModuleHandle = NULL;

	do
	{
		hmModuleHandle = GetModuleHandle(pszModuleName);
		Sleep(1);
	} while (hmModuleHandle == NULL);

	return hmModuleHandle;
}

DWORD WaitOnModuleHandle(std::string moduleName)
{
	DWORD ModuleHandle = NULL;
	while (!ModuleHandle)
	{
		ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
		if (!ModuleHandle)
			Sleep(50);
	}
	return ModuleHandle;
}

DWORD FindTextPattern(std::string moduleName, char* string)
{
	DWORD Address = WaitOnModuleHandle(moduleName.c_str());
	MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
	DWORD Length = ModInfo.SizeOfImage;

	int len = strlen(string);
	char* szMask = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		szMask[i] = 'x';
	}
	szMask[len] = '\0';

	for (DWORD c = 0; c < Length; c += 1)
	{
		if (bCompare((BYTE*)(Address + c), (BYTE*)string, szMask))
		{
			return (DWORD)(Address + c);
		}
	}
	return 0;
}

DWORD Stdlib;
VOID CValve::initSDK()
{
	Base::Debug::LOG("Initiate Thread");
	char szDebugString[1024];


	DWORD dwInitAddress = Base::Utils::PatternSearch("engine.dll", (PBYTE)"\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\x53\x56\x57\xE8\x00\x00\x00\x00\x83\x3D\x00\x00\x00\x00\x00","xxxxx????xxxx????xx?????", NULL, NULL);
	sprintf_s(szDebugString, "dwInitAddress: 0x%x", dwInitAddress);
	Base::Debug::LOG(szDebugString);

	typedef ValveSDK::CGlowObjectManager*(__thiscall* GetGlowObjectManager_t)(void);
	static GetGlowObjectManager_t GetGlowObjectManager = (GetGlowObjectManager_t)Base::Utils::PatternSearch("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\xA8\x01\x75\x4E", "x????xxxx", NULL, NULL);

	g_pGlowObjectManager = GetGlowObjectManager();

	CreateInterfaceFn AppSystemFactory = (CreateInterfaceFn)**(PDWORD*)(dwInitAddress + APPSYSTEMFACTORYOFFSET);
	CreateInterfaceFn ClientFactory = (CreateInterfaceFn)**(PDWORD*)(dwInitAddress + CLIENTFACTORYOFFSET);
	CreateInterfaceFn matsystem = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("materialsystem.dll"), "CreateInterface");

	pSurface = (ValveSDK::ISurface*)GetInterfacePtr("VGUI_Surface","g_pSurface",AppSystemFactory);
	pPanel = (ValveSDK::IPanel*)GetInterfacePtr("VGUI_Panel", "g_pPanel", AppSystemFactory);
	pClient = (ValveSDK::HLCLient*)GetInterfacePtr("VClient", "g_pClient", ClientFactory);
	pEntList = (ValveSDK::CEntityList*)GetInterfacePtr("VClientEntityList", "g_pEntList", ClientFactory);
	pEngine = (ValveSDK::CEngineClient*)GetInterfacePtr("VEngineClient", "g_pEngine", AppSystemFactory);
	g_pDebugOverlay = (ValveSDK::CDebugOverlay*)GetInterfacePtr("VDebugOverlay", "g_pDebugOverlay", AppSystemFactory);
	g_pEngineTraceClient = (ValveSDK::EngineTraceClient*)GetInterfacePtr("EngineTraceClient", "g_pEngineTraceClient", AppSystemFactory);
	g_pModel = (ValveSDK::IVModelInfo*)GetInterfacePtr("VModelInfoClient", "g_pModel", AppSystemFactory);
	g_pPred = (ValveSDK::CPrediction*)GetInterfacePtr("VClientPrediction", "g_pPred", ClientFactory);
	g_pGameMovement = (ValveSDK::CGameMovement*)GetInterfacePtr("GameMovement", "g_pGameMovement", ClientFactory);
	pGameEventManager = (ValveSDK::IGameEventManager*)AppSystemFactory("GAMEEVENTSMANAGER002", NULL);
	pModelRender = (ValveSDK::IVModelRender*)GetInterfacePtr("VEngineModel","g_pModelRender", AppSystemFactory);
	pRenderView = (ValveSDK::IVRenderView*)GetInterfacePtr("VEngineRenderView","g_pRenderView", AppSystemFactory);

	pKoloTrace = (ValveSDK::CTrace*)GetInterfacePtr("EngineTraceClient", "pKoloTrace", AppSystemFactory);
	pPhysics = (ValveSDK::IPhysicsSurfaceProps*)GetInterfacePtr("VPhysicsSurfaceProps", "g_pPhysics", AppSystemFactory);

	pMaterialSystem = (ValveSDK::IMaterialSystem*)GetInterfacePtr("VMaterialSystem", "pMatSystem", matsystem);

	char* VEngineCvarName = (char*)FindTextPattern("engine.dll", "VEngineCvar00");
	Stdlib = WaitOnModuleHandle("vstdlib.dll");
	CreateInterfaceFn StdFactory = (CreateInterface_t)GetProcAddress((HMODULE)Stdlib, "CreateInterface");
	pCVar = (ValveSDK::ICVar*)StdFactory(VEngineCvarName, NULL);


	pGlobalVars = *(ValveSDK::CGlobalVars**)(((*(PDWORD*)g_Valve.pClient)[0]) + GLOBALSOFFSET);

	pGlobalVars = (ValveSDK::CGlobalVars*)*(PDWORD)pGlobalVars;

	m_bInitiated = TRUE;
}

BOOL CValve::isInitiated()
{
	return this->m_bInitiated;
}


bool CValve::WorldToScreen(const Vector& vOrigin, Vector& vScreen)
{
	return (g_pDebugOverlay->ScreenPosition(vOrigin, vScreen) != 1);
}
