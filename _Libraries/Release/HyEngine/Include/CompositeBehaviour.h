#pragma once
#include "FlockBehaviour.h"
#include "CohesionBehaviour.h"
#include "AlignmentBehaviour.h"
#include "AvoidanceBehaviour.h"
#include "StayInRadiusBehaviour.h"
namespace HyEngine
{

	class CompositeBehaviour : public FlockBehaviour
	{
	public :
		virtual Vector3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockSystem* flock) override;

	private :
		std::vector<FlockBehaviour*> m_behaviours
		{
			new CohesionBehaviour(),
			new AlignmentBehaviour(),
			//new AvoidanceBehaviour(),
			new StayInRadiusBehaviour(),
			// TODO RandomMovementBehaviour()
		};
		std::vector<float> m_weights
		{
			0.5f,
			0.3f,
			//0.3f,
			0.6f,
		};
	};
}

