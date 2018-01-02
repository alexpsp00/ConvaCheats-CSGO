#include "main.h"
#include <assert.h>
	
HMODULE hMod = NULL;
CValve g_Valve;

void unhook()
{
	g_pPanelVMT.UnHook();
	g_pClientVMT.UnHook();
	g_pFrameStageNotify.UnHook();
}

VOID RemoveHooks(LPARAM lpParam)
{
	HMODULE hModule = (HMODULE)lpParam;

	while (true)
	{
		Sleep(100);
		if (g_CVARS.CvarList[key_Panic] > 0 && GetAsyncKeyState(g_CVARS.CvarList[key_Panic]) && !g_Mouse.ActiveMouse)
		{
			Sleep(1000);
			unhook();
			Sleep(2000);
			FreeLibraryAndExitThread(hModule, 0);
		}
	}
}

// HWID Protection - Credits : ???
static char cLastChar[128] = "";
#define D_CHECKPOINT { sprintf(cLastChar, "%s:%d", __FILE__, __LINE__); }
DWORD *CRC_Table = 0;

void GenerateTable()
{
	// Note: 
	// This is not the cause of the HWID changing constantly. You do not need to remove/change this.

	assert(!CRC_Table);

	DWORD dwPolynomial = 0xEDB88320;
	CRC_Table = new DWORD[256];

	DWORD x;
	D_CHECKPOINT
		for (int index = 0; index < 256; index++)
		{
			x = index;
			for (int index2 = 8; index2 > 0; index2--)
			{
				if (x & 1)
				{
					x = (x >> 1) ^ dwPolynomial;
				}
				else
				{
					x >>= 1;
				}
			}
			CRC_Table[index] = x;
		}
	D_CHECKPOINT
}

__forceinline DWORD GenerateTable32(const char* string)
{
	// Note: 
	// This is not the cause of the HWID changing constantly. You do not need to remove/change this.

	extern DWORD* CRC_Table;

	if (!CRC_Table)
	{
		GenerateTable();
	}

	register DWORD Crc32 = 0xFFFFFFFF;
	while (*string)
	{
		Crc32 = ((Crc32) >> 8) ^ CRC_Table[*string ^ ((Crc32)& 0xFF)]; string++;
	}
	return ~Crc32;
}

struct s_HWIDProtection
{
	//std::string *sLoginName;
	// Note:
	// More secure way of making a username login is to use std::string x
	// and use x.data as a username so you can encrypt it.
	std::string sLoginName;
	DWORD dwLoginHWID;
}
t_HWIDProtection;

int iCurrentHWID = 0;
std::map <int, s_HWIDProtection> hwids;

DWORD GetCurrentHWID()
{
	char cUserName[255] = "";
	DWORD dwUserName = sizeof(cUserName);
	GetUserName(cUserName, &dwUserName);

	char cComputerName[255] = "";
	DWORD dwComputerName = sizeof(cComputerName);
	GetComputerName(cComputerName, &dwComputerName);

	DWORD crcUserName = GenerateTable32(cUserName);
	DWORD crcComputerName = GenerateTable32(cComputerName);

	// Note: 
	// This is not the cause of the HWID changing constantly. You do not need to remove/change this.
	DWORD dwFinalHWID = crcUserName;
	DWORD dwFinalHWID2 = crcComputerName;

	DWORD dw2 = crcUserName * 1337;
	DWORD dw3 = crcComputerName * 2448;
	DWORD dw4 = dw2 * dw3;

	DWORD dw5;

	//np for wippys math skills
	if (dw4 < 0)
		dw5 = dw4 * (-INT_MAX);
	else
		dw5 = dw4 * (INT_MAX);

	return dw5;
}

void addhwid(std::string cLoginUserName, DWORD dwUserHWID)
{
	s_HWIDProtection HwidLoginInfo;
	iCurrentHWID += 1;
	HwidLoginInfo.dwLoginHWID = dwUserHWID;
	HwidLoginInfo.sLoginName = cLoginUserName;
	hwids[iCurrentHWID] = HwidLoginInfo;
}

using namespace std;
VOID initThread(PVOID ptr)
{
	g_Valve.initSDK();

	g_NetworkedVariableManager.Init();

	g_pPanelVMT.bInitialize((PDWORD*)g_Valve.pPanel);
	g_pPanelVMT.dwHookMethod((DWORD)hkdPaintTraverse, 41);	

	g_pClientVMT.bInitialize((PDWORD*)g_Valve.pClient);	
	g_pClientVMT.dwHookMethod((DWORD)hkdCreateMove, 21);
	g_pClientVMT.dwHookMethod((DWORD)hkdHudUpdate, 11);

	g_pFrameStageNotify.bInitialize((PDWORD*)g_Valve.pClient);
	g_pFrameStageNotify.dwHookMethod((DWORD)new_FrameStageNotify, 36);

	/*g_pModelRenderVMT.bInitialize((PDWORD*)g_Valve.pModelRender);*/
	/*g_pModelRenderVMT.dwHookMethod((DWORD)hkdDrawModelExecute, 19);*/

	/*oDrawModelExecute = (DrawModelEx_)g_pModelRenderVMT.dwHookMethod((DWORD)hkDrawModelExecute, 19);*/

	/*pModelHook = new CHook((DWORD**)pModelRender);
	oDrawModelExecute = (tDrawModelExecute)pModelHook->dwHookMethod((DWORD)hkDrawModelExecute, 21);*/

	//g_Valve.pInput = *(ValveSDK::CInput**)(g_pClientVMT.dwGetMethodAddress(21) + INPUTOFFSET);
	PDWORD pdwClientVMT = *(PDWORD*)g_Valve.pClient;
	g_Valve.pInput = *(ValveSDK::CInput**)(pdwClientVMT[15] + 0x1);
}

bool bHWID_FOUND = false;
bool bLAN_MODE;

INT WINAPI DllMain(_In_ HANDLE _HDllHandle, _In_ DWORD _Reason, _In_opt_ LPVOID _Reserved)
{
	if (_Reason == DLL_PROCESS_ATTACH)
	{
		


			/*g_Settings.LoadConfig();*/

			g_CVARS.DefaultConfig();

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)initThread, _HDllHandle, NULL, NULL);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RemoveHooks, _HDllHandle, NULL, NULL);
		/*}
		else
		{
			TerminateThread(initThread, 0);
			return FALSE;
		}*/
	}

	return TRUE;
}