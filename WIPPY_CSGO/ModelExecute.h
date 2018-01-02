#pragma once

extern Base::Utils::CVMTHookManager g_pModelRenderVMT;
void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld);
extern DrawModelEx_ oDrawModelExecute;
