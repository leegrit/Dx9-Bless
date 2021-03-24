#include "StandardEngineFramework.h"
#include "..\Include\MathUtils.h"

namespace HyEngine
{
	namespace MathUtils
	{
		float RandF(float l, float h)
		{
			if (l > h)
			{	// swap params in case order is wrong
				float tmp = l;
				l = h;
				h = tmp;
			}
			thread_local std::mt19937_64 generator(std::random_device{}());
			std::uniform_real_distribution<float> distribution(l, h);
			return distribution(generator);
		}

		// [)
		int RandI(int l, int h)
		{
			int offset = rand() % (h - l);
			return l + offset;
		}
		size_t RandU(size_t l, size_t h)
		{
#ifdef _DEBUG
			assert(l <= h);
#endif
			int offset = rand() % (h - l);
			return l + static_cast<size_t>(offset);
		}

	}
}
