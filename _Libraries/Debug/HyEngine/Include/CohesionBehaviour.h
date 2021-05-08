#pragma once
#include "FlockBehaviour.h"

namespace HyEngine
{
	class CohesionBehaviour : public FlockBehaviour
	{
	public:

		// Inherited via FlockBehaviour
		virtual Vector3 CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock) override;
	};

}

