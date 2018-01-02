#include "main.h"

cIni g_Settings;

std::string CvarNames[MAX_CVARS];
char* cSelectedPath;

float FindVarValue(const char *szTextArray, const char *pszVarName)
{
	int iLen = strlen(pszVarName) - 1;

	for (int i = 0; i < strlen(szTextArray); i++)
	{
		//first character matches but we gotta check if whole word matches
		if (szTextArray[i] == pszVarName[0])
		{
			bool bSkipThis = false;

			for (int i2 = 0; i2 <= iLen; i2++)
			{
				//we already checked for first character in the array
				if (i2 == 0)
					continue;

				if (szTextArray[i + i2] != pszVarName[i2])
				{
					bSkipThis = true;
					break;//ok not our string lets skip this one
				}
			}

			//something didnt match so lets skip to this one
			if (bSkipThis)
				continue;

			//everything matches meaning we can retrieve the value now
			std::string sOwn = &szTextArray[i + iLen + 1];//move 1 more spot as thats where the space is

			return atof(sOwn.data());
		}
	}

	return 0.0f;
}

std::string ConfigName()
{
	if (g_CVARS.config_select == 0)
		return "Damage for CSGO - ConvaCheats CSGO\\Legit.ini";
	else if (g_CVARS.config_select == 1)
		return "Damage for CSGO - ConvaCheats CSGO\\Rage.ini";
	else if (g_CVARS.config_select == 2)
		return "Damage for CSGO - ConvaCheats CSGO\\HackVsHack.ini";
}

void cIni::LoadConfig()
{
	std::string strConfigFileLoc = ConfigName();

	std::ifstream fstrCurConfigFile(strConfigFileLoc);
	std::string sSavedCVARS;
	std::string sFoundCVARS;

	for (int varindex = 0; varindex < MAX_CVARS; varindex++)
	{
		bool bFirstInLoop = (varindex == 0);

		if (bFirstInLoop)
		{
			//Read Text from file
			if (fstrCurConfigFile.is_open())
			{
				while (std::getline(fstrCurConfigFile, sSavedCVARS))
				{
					//Add found text to string to store saved CVAR enums
					sFoundCVARS += sSavedCVARS;
				}
			}
		}
		//Replace CVAR enum values with values collected from config
		g_CVARS.CvarList[varindex] = FindVarValue(sFoundCVARS.data(), CvarNames[varindex].data());
	}
	fstrCurConfigFile.close();
	sFoundCVARS.erase(sFoundCVARS.end() - 1);
}

void cIni::SaveConfig()
{
	std::string strConfigFileLoc = ConfigName();

	std::ofstream fstrCurConfigFile(strConfigFileLoc);
	std::string sCurCVARS;

	for (int varindex = 0; varindex < MAX_CVARS; varindex++)
	{
		bool bLastInLoop = (varindex == (MAX_CVARS - 1));

		//Create a name for each CVAR enums
		char szName[10];
		sprintf(szName, "[var%i", varindex);
		CvarNames[varindex] = szName;

		char cFindCurCVARS[256];
		sprintf(cFindCurCVARS, "%s]%f", CvarNames[varindex].data(), g_CVARS.CvarList[varindex]);
		//Find each individual CVAR enum values and add them to a string
		sCurCVARS += cFindCurCVARS;

		//Once up to the last CVAR enum stop copying them
		if (bLastInLoop)
		{
			if (fstrCurConfigFile.is_open())
			{
				//Write string which stored all CVAR enums to config file
				fstrCurConfigFile << sCurCVARS;
			}
			//Clear string after to minimize issues
			sCurCVARS.erase(sCurCVARS.end() - 1);
		}
	}
	fstrCurConfigFile.close();
}