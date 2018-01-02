#include "main.h"

namespace wippyhack_anglestuff
{
	extern void NormalizeVector(Vector& vec);
	extern void ClampAngles(Vector& vecAngles);
	extern VOID angleVectors(PFLOAT angles, PFLOAT f, PFLOAT r, PFLOAT u);
	extern void vectorAngles(float* forward, float* angles);
	extern void vectorAnglesVec(Vector forward, Vector &angles);
	extern void VectorAngles3D(const Vector&vecForward, Vector&vecAngles);
	extern void AngleMatrix(const Vector &angles, matrix3x4_t &matrix);
}