#include "StandardEngineFramework.h"
#include "AlignmentBehaviour.h"
#include "Transform.h"
#include "FlockAgent.h"


Vector3 HyEngine::AlignmentBehaviour::CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock)
{
	// if no neighbors, maintain current alignment
	if (context.size() == 0)
		return agent->GetTransform()->Forward();

	Vector3 alignmentMove = Vector3::Zero;

	for(auto& item : context)
	{
		alignmentMove += item->Forward();
	}
	alignmentMove  = alignmentMove / (float)context.size();

	D3DXVECTOR3 result;
	D3DXVec3Normalize(&result,&alignmentMove.operator D3DXVECTOR3());
	alignmentMove = result;
	return alignmentMove;
}
