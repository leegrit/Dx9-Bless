#include "StandardEngineFramework.h"
#include "CohesionBehaviour.h"

using namespace HyEngine;

Vector3 HyEngine::CohesionBehaviour::CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock)
{
	if (context.size() == 0)
		return Vector3::Zero;

	// add all points together and average.
	Vector3 cohesionMove = Vector3::Zero;
	for (auto& item : context)
	{
		cohesionMove += item->m_position;
	}
	cohesionMove = cohesionMove / (float)context.size();

	// create offset from agent position
	cohesionMove = cohesionMove - agent->GetTransform()->m_position;

	return cohesionMove;

	D3DXVECTOR3 result;
	D3DXVec3Lerp(&result,
		&agent->GetTransform()->Forward().operator D3DXVECTOR3(),
		&cohesionMove.operator D3DXVECTOR3(),
		0.5f);
	cohesionMove = result;
	return cohesionMove; 
}
