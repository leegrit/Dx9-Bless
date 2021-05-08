#pragma once

namespace HyEngine
{
	class BumpModelVertex;
	class DxHelper
	{
	public :
		static DWORD Float2DWORD(float f)
		{
			return *((DWORD*)&f);
		}
		static float GetRandomFloat(float lowBound, float highBound)
		{
			if (lowBound >= highBound) // bad input
				return lowBound;

			// get random float in [0, 1] interval
			float f = (rand() % 10000) * 0.0001f;

			// return float in [lowBound, highBound] interval. 
			return (f * (highBound - lowBound)) + lowBound;
		}

		static void GetRandomVector(
			D3DXVECTOR3* out,
			D3DXVECTOR3* min,
			D3DXVECTOR3* max)
		{
			out->x = GetRandomFloat(min->x, max->x);
			out->y = GetRandomFloat(min->y, max->y);
			out->z = GetRandomFloat(min->z, max->z);
		}

		/*static float Lerp(float a, float b, float s)
		{
			return a + (b - a) * s;
		}*/

		static D3DXVECTOR3 CalcOffset(D3DXVECTOR3 source, D3DXVECTOR3 offset, D3DXVECTOR3 rightDir, D3DXVECTOR3 upDir, D3DXVECTOR3 forwardDir)
		{
			D3DXVECTOR3 resultPos =
				source +
				rightDir * offset.x +
				upDir* offset.y +
				forwardDir* offset.z;
			return resultPos;
		}
		static float Lerp(float a, float b, float lerpFactor)
		{
			float result = ((1.f - lerpFactor) * a) + (lerpFactor * b);
			return result;
		}
		static float LerpDegrees(float a, float b, float lerpFactor) // Lerps from angle a to b (both between 0.f and 360.f), taking the shortest path
		{
			float result;
			float diff = b - a;
			if (diff < -180.f)
			{
				// lerp upwards past 360
				b += 360.f;
				result = DxHelper::Lerp(a, b, lerpFactor);
				if (result >= 360.f)
				{
					result -= 360.f;
				}
			}
			else if (diff > 180.f)
			{
				// lerp downwards past 0
				b -= 360.f;
				result = DxHelper::Lerp(a, b, lerpFactor);
				if (result < 0.f)
				{
					result += 360.f;
				}
			}
			else
			{
				// straight lerp
				result = DxHelper::Lerp(a, b, lerpFactor);
			}

			return result;
		}

		static float LerpRadians(float a, float b, float lerpFactor) // Lerps from angle a to b (both between 0.f and PI_TIMES_TWO), taking the shortest path
		{
			float result;
			float diff = b - a;
			if (diff < -DxMath::PI)
			{
				// lerp upwards past PI_TIMES_TWO
				b += DxMath::PI_TIMES_TWO;
				result = DxHelper::Lerp(a, b, lerpFactor);
				if (result >= DxMath::PI_TIMES_TWO)
				{
					result -= DxMath::PI_TIMES_TWO;
				}
			}
			else if (diff > DxMath::PI)
			{
				// lerp downwards past 0
				b -= DxMath::PI_TIMES_TWO;
				result = DxHelper::Lerp(a, b, lerpFactor);
				if (result < 0.f)
				{
					result += DxMath::PI_TIMES_TWO;
				}
			}
			else
			{
				// straight lerp
				result = DxHelper::Lerp(a, b, lerpFactor);
			}

			return result;
		}
		static double  ReliableRandom(double min, double max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(min, max);
			return distr(gen);
		}

		static void CalculateTangentBinormal(const BumpModelVertex * vertex1, const BumpModelVertex *  vertex2, const  BumpModelVertex * vertex3,
			_Out_ D3DXVECTOR3 * tangent, _Out_ D3DXVECTOR3* binormal);

		static void CalculateNormal(const D3DXVECTOR3 * tangent, const D3DXVECTOR3 * binormal, _Out_ D3DXVECTOR3* normal);
	};
}