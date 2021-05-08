#pragma once
#include "FlockBehaviour.h"

namespace HyEngine
{
	class StayInRadiusBehaviour : public FlockBehaviour
	{
	public:
		// Inherited via FlockBehaviour
		virtual Vector3 CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock) override;

	private :
		Vector3 center; // center is player
		float radius = 300;
	};

}

