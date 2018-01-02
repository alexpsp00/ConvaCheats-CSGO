#include "main.h"

Base::Utils::CVMTHookManager g_pModelRenderVMT;
DrawModelEx_ oDrawModelExecute;

namespace ChamsFuncs
{
	DWORD KeyValues_KeyValues;
	DWORD KeyValues_LoadFromBuffer;
	DWORD dwCalcPlayerView;
};

void InitValues()
{
	ChamsFuncs::KeyValues_KeyValues = Base::Utils::PatternSearch("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx", NULL, NULL);
	ChamsFuncs::KeyValues_KeyValues += 7;
	ChamsFuncs::KeyValues_KeyValues = ChamsFuncs::KeyValues_KeyValues + *reinterpret_cast<PDWORD_PTR>(ChamsFuncs::KeyValues_KeyValues + 1) + 5;

	ChamsFuncs::KeyValues_LoadFromBuffer = Base::Utils::PatternSearch("client.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x8A\xD8\xFF\x15\x00\x00\x00\x00\x84\xDB", "x????xxxx????xx", NULL, NULL);
	ChamsFuncs::KeyValues_LoadFromBuffer = ChamsFuncs::KeyValues_LoadFromBuffer + *reinterpret_cast<PDWORD_PTR>(ChamsFuncs::KeyValues_LoadFromBuffer + 1) + 5;
}

void InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)ChamsFuncs::KeyValues_KeyValues;
	__asm
	{
		push name
			mov ecx, keyValues
			call dwFunction
	}
}

void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{
	DWORD dwFunction = (DWORD)ChamsFuncs::KeyValues_LoadFromBuffer;

	__asm
	{
		push 0
			push 0
			push 0
			push pBuffer
			push resourceName
			mov ecx, keyValues
			call dwFunction
	}
}

ValveSDK::IMaterial *CreateMaterial(bool shouldIgnoreZ, bool isLit, bool isWireframe) //credits to ph0ne
{
	static int created = 0;

	static const char tmp[] =
	{
		"\"%s\"\
								\n{\
																				\n\t\"$basetexture\" \"vgui/white_additive\"\
																																								\n\t\"$envmap\" \"\"\
																																																																						\n\t\"$model\" \"1\"\
																																																																																																																\n\t\"$flat\" \"1\"\
																																																																																																																																																																								\n\t\"$nocull\" \"0\"\
																																																																																																																																																																																																																																																\n\t\"$selfillum\" \"1\"\
																																																																																																																																																																																																																																																																																																																																										\n\t\"$halflambert\" \"1\"\
																																																																																																																																																																																																																																																																																																																																																																																																																																																								\n\t\"$nofog\" \"0\"\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												\n\t\"$ignorez\" \"%i\"\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																								\n\t\"$znearer\" \"0\"\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														\n\t\"$wireframe\" \"%i\"\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														        \n}\n"
	};

	char* baseType = (isLit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char name[512];
	sprintf_s(name, sizeof(name), "#ayy_meme_%i.vmt", created);
	++created;

	KeyValues* keyValues = (KeyValues*)malloc(sizeof(KeyValues));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);

	ValveSDK::IMaterial *createdMaterial = g_Valve.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}

void ForceMaterial(ValveSDK::Color color, ValveSDK::IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float temp[3] =
		{
			color.r(),
			color.g(),
			color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = color.a();

		g_Valve.pRenderView->SetBlend(1.0f);
		g_Valve.pRenderView->SetColorModulation(temp);
	}

	if (forceMaterial)
		g_Valve.pModelRender->ForcedMaterialOverride(material);
	else
		g_Valve.pModelRender->ForcedMaterialOverride(NULL);
}

void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	//ValveSDK::Color color;
	//float flColor[3] = { 0.f };
	//static ValveSDK::IMaterial* CoveredLit = CreateMaterial(true, true, false);
	//static ValveSDK::IMaterial* OpenLit = CreateMaterial(false, true, false);
	//static ValveSDK::IMaterial* CoveredFlat = CreateMaterial(true, false, false);
	//static ValveSDK::IMaterial* OpenFlat = CreateMaterial(false, false, false);
	//bool DontDraw = false;

	//const char* ModelName = g_Valve.g_pModel->GetModelName((model_t*)pInfo.pModel);
	//CBaseEntity* pModelEntity = (CBaseEntity*)g_Valve.pEntList->GetClientEntity(pInfo.entity_index);
	//CBaseEntity* pLocal = (CBaseEntity*)g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());

	//// Player Chams
	//int ChamsStyle = 1;
	//if (strstr(ModelName, "models/player"))
	//{
	//	if (pLocal && (!pModelEntity->GetTeam() != pLocal->GetTeam()))
	//	{
	//		ValveSDK::IMaterial *covered = ChamsStyle == 1 ? CoveredLit : CoveredFlat;
	//		ValveSDK::IMaterial *open = ChamsStyle == 1 ? OpenLit : OpenFlat;

	//		CBaseEntity* pModelEntity = (CBaseEntity*)g_Valve.pEntList->GetClientEntity(pInfo.entity_index);
	//		if (pModelEntity)
	//		{
	//			CBaseEntity *local = g_Valve.pEntList->GetClientEntity(g_Valve.pEngine->GetLocalPlayer());
	//			if (local)
	//			{
	//				if (pModelEntity->GetHealth() > 0 /*&& pModelEntity->GetTeamNum() != local->GetTeamNum()*/)
	//				{
	//					float alpha = 1.f;

	//					if (pModelEntity->GetTeam() == 2)
	//					{
	//						flColor[0] = 240.f / 255.f;
	//						flColor[1] = 30.f / 255.f;
	//						flColor[2] = 35.f / 255.f;
	//					}
	//					else
	//					{
	//						flColor[0] = 63.f / 255.f;
	//						flColor[1] = 72.f / 255.f;
	//						flColor[2] = 205.f / 255.f;
	//					}

	//					g_Valve.pRenderView->SetColorModulation(flColor);
	//					g_Valve.pRenderView->SetBlend(alpha);
	//					g_Valve.pModelRender->ForcedMaterialOverride(covered);
	//					oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	//					if (pModelEntity->GetTeam() == 2)
	//					{
	//						flColor[0] = 247.f / 255.f;
	//						flColor[1] = 180.f / 255.f;
	//						flColor[2] = 20.f / 255.f;
	//					}
	//					else
	//					{
	//						flColor[0] = 32.f / 255.f;
	//						flColor[1] = 180.f / 255.f;
	//						flColor[2] = 57.f / 255.f;
	//					}

	//					g_Valve.pRenderView->SetColorModulation(flColor);
	//					g_Valve.pRenderView->SetBlend(alpha);
	//					g_Valve.pModelRender->ForcedMaterialOverride(open);
	//				}
	//				else
	//				{
	//					color.SetColor(255, 255, 255, 255);
	//					ForceMaterial(color, open, true, true);
	//				}
	//			}
	//		}
	//	}
	//}
	//oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	//g_Valve.pModelRender->ForcedMaterialOverride(NULL);
}