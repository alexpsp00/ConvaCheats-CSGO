#include "main.h"

VOID sinCos(float radians, PFLOAT sine, PFLOAT cosine)
{
	__asm
	{
		fld dword ptr[radians]
			fsincos
			mov edx, dword ptr[cosine]
			mov eax, dword ptr[sine]
			fstp dword ptr[edx]
			fstp dword ptr[eax]
	}
}

float sseSqrt(float x)
{
	float root = 0.0f;

	__asm
	{
		sqrtss xmm0, x
			movss root, xmm0
	}

	return root;
}

namespace wippyhack_anglestuff
{
	void NormalizeVector(Vector& vec)
	{
		for (int i = 0; i < 3; ++i)
		{
			while (vec[i] > 180.f)
				vec[i] -= 360.f;

			while (vec[i] < -180.f)
				vec[i] += 360.f;
		}

		vec[2] = 0.f;
	}

	void ClampAngles(Vector& vecAngles)
	{
		if (vecAngles[0] > 89.f)
			vecAngles[0] = 89.f;
		if (vecAngles[0] < -89.f)
			vecAngles[0] = -89.f;
		if (vecAngles[1] > 180.f)
			vecAngles[1] = 180.f;
		if (vecAngles[1] < -180.f)
			vecAngles[1] = -180.f;

		vecAngles[2] = 0.f;
	}

	VOID angleVectors(PFLOAT angles, PFLOAT f, PFLOAT r, PFLOAT u)
	{
		float sp, sy, sr, cp, cy, cr;

		sinCos(DEG2RAD(angles[0]), &sp, &cp);
		sinCos(DEG2RAD(angles[1]), &sy, &cy);
		sinCos(DEG2RAD(angles[2]), &sr, &cr);

		f[0] = cp * cy;
		f[1] = cp * sy;
		f[2] = -sp;

		r[0] = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
		r[1] = -1.0f * sr * sp * sy + -1.0f * cr * cy;
		r[2] = -1.0f * sr * cp;

		u[0] = cr * sp * cy + -sr * -sy;
		u[1] = cr * sp * sy + -sr * cy;
		u[2] = cr * cp;
	}

	void vectorAngles(float* forward, float* angles)
	{
		if (forward[1] == 0.0f && forward[0] == 0.0f)
		{
			angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
			angles[1] = 0.0f;
		}
		else
		{
			float len2d = sseSqrt(square(forward[0]) + square(forward[1]));

			angles[0] = RAD2DEG(atan2f(-forward[2], len2d));
			angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

			if (angles[0] < 0.0f) angles[0] += 360.0f;
			if (angles[1] < 0.0f) angles[1] += 360.0f;
		}

		angles[2] = 0.0f;
	}

	void vectorAnglesVec(Vector forward, Vector &angles)
	{
		if (forward[1] == 0.0f && forward[0] == 0.0f)
		{
			angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
			angles[1] = 0.0f;
		}
		else
		{
			float len2d = sseSqrt(square(forward[0]) + square(forward[1]));

			angles[0] = RAD2DEG(atan2f(-forward[2], len2d));
			angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

			if (angles[0] < 0.0f) angles[0] += 360.0f;
			if (angles[1] < 0.0f) angles[1] += 360.0f;
		}

		angles[2] = 0.0f;
	}

	void VectorAngles3D(const Vector&vecForward, Vector&vecAngles)
	{
		Vector vecView;
		if (vecForward[1] == 0.f && vecForward[0] == 0.f)
		{
			vecView[0] = 0.f;
			vecView[1] = 0.f;
		}
		else
		{
			vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / PI;

			if (vecView[1] < 0.f)
				vecView[1] += 360;

			vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

			vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / PI;
		}

		vecAngles[0] = -vecView[0];
		vecAngles[1] = vecView[1];
		vecAngles[2] = 0.f;
	}

	void AngleMatrix(const Vector &angles, matrix3x4_t &matrix)
	{
		float angle;
		float sr, sp, sy, cr, cp, cy;

		angle = angles.x * (6.283185f / 360);
		sp = sin(angle);
		cp = cos(angle);

		angle = angles.y * (6.283185f / 360);
		sy = sin(angle);
		cy = cos(angle);

		angle = angles.z * (6.283185f / 360);
		sr = sin(angle);
		cr = cos(angle);

		// matrix = (YAW * PITCH) * ROLL
		matrix[0][0] = cp*cy;
		matrix[1][0] = cp*sy;

		matrix[2][0] = -sp;
		matrix[0][1] = sr*sp*cy + cr*-sy;

		matrix[1][1] = sr*sp*sy + cr*cy;
		matrix[2][1] = sr*cp;

		matrix[0][2] = (cr*sp*cy + -sr*-sy);
		matrix[1][2] = (cr*sp*sy + -sr*cy);

		matrix[2][2] = cr*cp;

		matrix[0][3] = 0.0;
		matrix[1][3] = 0.0;
		matrix[2][3] = 0.0;
	}
}