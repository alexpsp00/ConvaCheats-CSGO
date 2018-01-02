//#include "Main.h"
//
//#ifndef _MENU_H_
//#define _MENU_H_
//
//struct anitem
//{
//	int type;
//	float *cvar;
//	float max;
//	float min;
//	float step;
//	char title[100];
//	char info[100];
//};
//
//struct sections
//{
//	float aimbot_sect;
//
//	float trigger_sect;
//
//	float visual_sect;
//
//	float visual_esp_sect;
//
//	float others_sect;
//
//	float skins_sect;
//
//	float config_sect;
//
//};
//
//class Position
//{
//public:
//	Position();
//
//	float PosX;
//	float PosY;
//
//	void Init(float x, float y);
//
//	void PositionCopy(Position src, Position dest);
//	void PositionAdd(Position src, Position add);
//
//	float m_flPos[2];
//};
//
//class cMenu
//{
//public:
//
//	cMenu(char* Menu_name);
//	void InitMenuItems();
//	void DrawMenu();
//
//	int AddEntry(int type, int i, char title[100], float* cvar, float max, float min, float step, char* info);
//
//	int nMenuindex;
//
//	int nMenuitems;
//
//	BOOL KeyHandle();
//
//	anitem Item[150];
//
//	Position pMenuPos;
//
//	float flSize[2];
//
//	bool bMenuopen;
//
//	sections Menusection;
//
//	char* szMenuname;
//};
//
//extern cMenu new_Menu;
//
//#endif