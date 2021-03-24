#pragma once
#include "LinearMath.h"

namespace HyEngine
{
	namespace DxMath
	{
		//const static float PI;
		//const static float PI_TIMES_TWO;
		static const float PI = 3.14159f;
		static const float PI_TIMES_TWO = 6.28318530718f;

		static D3DXVECTOR3 WorldMat2PosVec(const D3DXMATRIX& worldMat)
		{
			Vector3 posVec;
			posVec.x() = worldMat.m[3][0];
			posVec.y() = worldMat.m[3][1];
			posVec.z() = worldMat.m[3][2];
			return posVec;
		}
		static D3DXVECTOR3 WorldMat2ScaleVec(const D3DXMATRIX& worldMat)
		{
			Vector3 scaleVec;
			scaleVec.x() = worldMat.m[0][0];
			scaleVec.y() = worldMat.m[1][1];
			scaleVec.z() = worldMat.m[2][2];
			return scaleVec;
		}
		//// Dot product of two vector2's
		//static float DotProduct(const D3DXVECTOR2 &a, const D3DXVECTOR2 &b)
		//{
		//	return a.x*b.x + a.y*b.y;
		//}

		//// Dot product of two vector3's
		//static float DotProduct(const D3DXVECTOR3 &a, const D3DXVECTOR3 &b)
		//{
		//	return a.x*b.x + a.y*b.y + a.z*b.z;
		//}


		// Swap two vector2's
		static void SwapVec(D3DXVECTOR2 &a, D3DXVECTOR2 &b)
		{
			D3DXVECTOR2 tmp(a);

			a = b;
			b = tmp;
		}
		// 결과값 : -180 ~ 180
		static float GetAngle(const D3DXVECTOR3& a, const D3DXVECTOR3& b)
		{
			float cosAngle = acosf(D3DXVec3Dot(&a, &b) / (D3DXVec3Length(&a) * D3DXVec3Length(&b)));
			cosAngle = D3DXToDegree(cosAngle);

			// 외적의 z성분으로 방향이 결정된다.
			float angle = (a.x * b.y - a.y * b.x > 0.0f) ? cosAngle : -cosAngle;
			return angle;
		}
		// Swap two vector3's
		static void SwapVec(D3DXVECTOR3 &a, D3DXVECTOR3 &b)
		{
			D3DXVECTOR3 tmp(a);

			a = b;
			b = tmp;
		}
		// Dot product of two vector2's
		static float DotProduct(const D3DXVECTOR2 &a, const D3DXVECTOR2 &b)
		{
			return a.x*b.x + a.y*b.y;
		}

		// Dot product of two vector3's
		static float DotProduct(const D3DXVECTOR3 &a, const D3DXVECTOR3 &b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		// Cross product of two vector3's
		static D3DXVECTOR3 CrossProduct(const D3DXVECTOR3 &a, const D3DXVECTOR3 &b)
		{
			return D3DXVECTOR3(a.y*b.z - a.z*b.y,
				a.z*b.x - a.x*b.z,
				a.x*b.y - a.y*b.x);
		}

		// Are these two vector2's nearly equal?
		static  bool NearlyEquals(const D3DXVECTOR2& a, const D3DXVECTOR2& b, float r)
		{
			D3DXVECTOR2 diff = a - b; // difference

			return (DxMath::DotProduct(diff, diff) < r*r); // radius
		}

		// Are these two vector3's nearly equal?
		static  bool NearlyEquals(const D3DXVECTOR3& a, const D3DXVECTOR3& b, float r)
		{
			D3DXVECTOR3 diff = a - b; // difference

			return (DxMath::DotProduct(diff, diff) < r*r); // radius
		}
		static float Length(D3DXVECTOR3 vec)
		{
			return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		}
		static float SqrMagnitude(D3DXVECTOR3 vec)
		{
			return DxMath::Length(vec) * DxMath::Length(vec);
		}
		
		// 아마 -180 ~ 180
		//https://stackoverflow.com/questions/43749543/c-calculate-angle-0-to-360-between-two-3d-vectors
		static float CalculateAngle(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
		{
			float dotResult = 0;
			float magResult = 0;
			dotResult=D3DXVec3Dot(&v1, &v2);
			magResult = D3DXVec3Length(&v1) * D3DXVec3Length(&v2);

			return std::acos(dotResult / magResult);
		}
		static D3DXVECTOR3 RotationMatrixToEulerAngles(D3DXMATRIX& r)
		{
			float sy = std::sqrt(r._11 * r._11 + r._21 * r._21);

			bool singular = sy < 1e-6; // if

			float x, y, z;
			if (!singular)
			{
				x = std::atan2(r._32, r._33);
				y = std::atan2(-r._31, sy);
				z = std::atan2(r._21, r._11);
			}
			else
			{
				x = std::atan2(-r._23, r._22);
				y = std::atan2(-r._31, sy);
				z = 0;
			}
			return D3DXVECTOR3(x, y, z);

		}
		static float GetAngleBetween(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
		{
			float mag1 = DxMath::Length(vec1);
			float mag2 = DxMath::Length(vec2);
			float dotProduct = DxMath::DotProduct(vec1, vec2);

			return (float)(acos(dotProduct / (mag1 * mag2)));
		}

	}
}

