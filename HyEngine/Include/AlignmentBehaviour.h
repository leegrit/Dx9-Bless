#pragma once
#include "FlockBehaviour.h"

namespace HyEngine
{
	class Flock;
	class FlockAgent;
	class AlignmentBehaviour : public FlockBehaviour
	{
	public :
		virtual Vector3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockSystem* flock) override;
	};
}

