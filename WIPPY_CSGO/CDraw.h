#pragma once

class CDraw
{
public:
	VOID initFont();
	std::wstring stringToWide(const std::string& text);
	VOID DrawString(unsigned long font, int x, int y, int r, int g, int b, const wchar_t *pszText);
	INT getWidht(unsigned long font, const char* input, ...);
	VOID DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...);
	VOID FillRGBA(float x, float y, float w, float h, int r, int g, int b, int a);
	VOID doESP( void );
	VOID DrawHealthBar(CBaseEntity* pLocalEntity, CBaseEntity* pBaseEntity);
	ValveSDK::ISurface* g_pSurface = NULL;
	unsigned long m_ESPFont, m_WatermarkFont, m_MenuFont, m_ListItemFont;
private:
};

extern CDraw g_Draw;