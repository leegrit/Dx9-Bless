#pragma once
#include "FlockSystem.h"
#include "FlockAgent.h"

namespace HyEngine
{
	class FlockBehaviour
	{
	public :
		virtual Vector3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockSystem* flock)  =0 ;
	};
}

