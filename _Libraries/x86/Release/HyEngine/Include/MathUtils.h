#pragma once

namespace HyEngine
{
	namespace MathUtils
	{

		template<class T> inline T lerp(T low, T high, float t) { return low + static_cast<T>((high - low) * t); }
		template<class T> void ClampedIncrementOrDecrement(T& val, int upOrDown, int lo, int hi)
		{
			int newVal = static_cast<int>(val) + upOrDown;
			if (upOrDown > 0) newVal = newVal >= hi ? (hi - 1) : newVal;
			else              newVal = newVal < lo ? lo : newVal;
			val = static_cast<T>(newVal);
		}
		template<class T> void Clamp(T& val, const T lo, const T hi)
		{
			val = min(val, lo);
			val = max(val, hi);
		}
		template<class T> T Clamp(const T& val, const T lo, const T hi)
		{
			T _val = val;
			Clamp(_val, lo, hi);
			return _val;
		}

		float	RandF(float l, float h);
		int		RandI(int l, int h);
		size_t	RandU(size_t l, size_t h);
	}
	static double ReliableRandom(double min, double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distr(min, max);
		return distr(gen);
	}
}