
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <psapi.h>
#include <time.h>
#include <process.h>
#include <vector>
#include <map>
#include <ostream>
#include <Shlobj.h>
#include <math.h>
#include <stdint.h>

#include "Valve/checksum_crc.h"
#include "Utils.h"
#include "Vector.h"
#include "CMath.h"
#include "SDK.h"
#include "CValve.h"
#include "CDraw.h"
#include "CAimbot.h"
#include "AntiAim.h"
#include "AngleStuff.h"
#include "Fakelag Fix\TimeSimulator.h"

#include "detours.h"

//CSGO
#include "Client.h"
#include "Panel.h"
#include "FrameStage.h"
#include "ModelExecute.h"

//MENU
#include "CVARS.h"
#include "menu.h"
#include "mouse.h"
#include "iniFile.h"
#include "MouseGUI.h"

#include "xor.h"

extern HMODULE hMod;

#pragma warning( disable : 4409 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4716 )

extern Vector savedangle;

extern bool bLAN_MODE;