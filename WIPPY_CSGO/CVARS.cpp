#include "main.h"
//
cCVARS g_CVARS;
//
//char cPath[255];
//char cPath1[255];
//char cPath2[255];
//
//float FindVarValue(const char *szTextArray, const char *pszVarName)
//{
//	int iLen = strlen(pszVarName) - 1;
//
//	for (int i = 0; i < strlen(szTextArray); i++)
//	{
//		//first character matches but we gotta check if whole word matches
//		if (szTextArray[i] == pszVarName[0])
//		{
//			bool bSkipThis = false;
//
//			for (int i2 = 0; i2 <= iLen; i2++)
//			{
//				//we already checked for first character in the array
//				if (i2 == 0)
//					continue;
//
//				if (szTextArray[i + i2] != pszVarName[i2])
//				{
//					bSkipThis = true;
//					break;//ok not our string lets skip this one
//				}
//			}
//
//			//something didnt match so lets skip to this one
//			if (bSkipThis)
//				continue;
//
//			//everything matches meaning we can retrieve the value now
//			std::string sOwn = &szTextArray[i + iLen + 1];//move 1 more spot as thats where the space is
//
//			return atof(sOwn.data());
//		}
//	}
//
//	return 0.0f;
//}
//
//void HandleConfig(const char *pszConfigName, int iType)
//{
//	HANDLE hFile, hFile2, hFile3;
//	CreateDirectoryA(cPath, 0);
//	strcat(cPath, "\\DAMAGE_CSGO");
//	CreateDirectoryA(cPath, 0);
//	strcpy(cPath1, cPath);
//	strcpy(cPath2, cPath);
//	strcat(cPath, "\\config1.ini");
//	strcat(cPath1, "\\config2.ini");
//	strcat(cPath2, "\\config3.ini");
//
//
//	if (g_CVARS.CvarList[config_select] == 0)
//		cSelectedPath = cPath;
//	else if (g_CVARS.CvarList[config_select] == 1)
//		cSelectedPath = cPath1;
//	else if (g_CVARS.CvarList[config_select] == 2)
//		cSelectedPath = cPath2;
//
//
//	//kolonote:
//	//to save shit were gonna generate a config file
//	std::string sSavedConfig;
//	//our file loaded from server
//	std::string sLoadResponse;
//
//	HW_PROFILE_INFO hwProfileInfo;
//
//	//REMEMBER: TEMPORARY
//	//this is utter shit but i didnt find a quicker way for unique identification and i need it to store configs for different users on server
//	GetCurrentHwProfile(&hwProfileInfo);
//
//	for (int varindex = 0; varindex < MAX_CVARS; varindex++)
//	{
//		bool bLastInLoop = (varindex == (MAX_CVARS - 1));
//		bool bFirstInLoop = (varindex == 0);
//
//		if (iType == LoadConfig && bFirstInLoop)
//		{
//			std::string sPath = cSelectedPath;
//			
//
//			/*delete[] cSelectedPath;*/
//		}
//
//		if (iType == SaveConfig)
//		{
//#ifdef DEBUGMODE
//			if (bFirstInLoop)
//			{
//				Base::Debug::LOG("");
//				Base::Debug::LOG("Settings Saved!");
//				Base::Debug::LOG("");
//			}
//
//			char szLog[256];
//			sprintf(szLog, "%s =  %f", CvarNames[varindex].data(), g_CVARS.CvarList[varindex]);
//			Base::Debug::LOG(szLog);
//#endif
//			char szBitcho[256];
//			sprintf(szBitcho,/*%s%f*/XorStr<0x46, 5, 0x504F1CD1>("\x63\x34\x6D\x2F" + 0x504F1CD1).s, CvarNames[varindex].data(), g_CVARS.CvarList[varindex]);
//			sSavedConfig += szBitcho;
//
//			if (bLastInLoop)
//			{
//				std::string sPath = /*confighandle.php*/XorStr<0x3A, 17, 0xE30B48FD>("\x59\x54\x52\x5B\x57\x58\x28\x20\x2C\x27\x28\x20\x68\x37\x20\x39" + 0xE30B48FD).s;
//				char *pszFullPath = new char[sPath.size() + sSavedConfig.size() + strlen(pszConfigName) + strlen(hwProfileInfo.szHwProfileGuid) + 20];
//				sprintf(pszFullPath,/*%s?t=0&n=%s&f=%s&d=%s&g=2*/XorStr<0xDB, 26, 0xCAACD7BA>("\xFE\xAF\xE2\xAA\xE2\xD0\xC7\x8C\xDE\xC1\x96\xC0\x81\xD5\xCC\x99\xCD\x88\xD0\xCB\x9C\xD6\x96\xCF\xC1" + 0xCAACD7BA).s, sPath.data(), pszConfigName, sSavedConfig.data(), hwProfileInfo.szHwProfileGuid);
//
//				std::string sOut;
//				Winsock_StreamOnlineDataToMemory(/*interwebz.cc*/XorStr<0xD0, 13, 0xAECE5734>("\xB9\xBF\xA6\xB6\xA6\xA2\xB3\xB5\xA2\xF7\xB9\xB8" + 0xAECE5734).s, pszFullPath, sOut);
//
//				delete[] pszFullPath;
//			}
//
//#ifdef DEBUGMODE
//			if (bLastInLoop)
//				Base::Debug::LOG("");
//#endif
//		}
//		else if (iType == LoadConfig)
//		{
//#ifdef DEBUGMODE
//			if (bFirstInLoop)
//			{
//				Base::Debug::LOG("");
//				Base::Debug::LOG("Settings Loaded!");
//				Base::Debug::LOG("");
//			}
//#endif
//
//			g_CVARS.CvarList[varindex] = FindVarValue(sLoadResponse.data(), g_CVARS.CvarList[varindex].data());
//
//#ifdef DEBUGMODE
//			char szLog[256];
//			sprintf(szLog, "%s =  %f", CvarNames[varindex].data(), g_CVARS.CvarList[varindex]);
//			Base::Debug::LOG(szLog);
//
//			if (bLastInLoop)
//				Base::Debug::LOG("");
//#endif
//		}
//	}
//}
