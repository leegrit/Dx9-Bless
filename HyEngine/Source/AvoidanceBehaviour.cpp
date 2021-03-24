#include "StandardEngineFramework.h"
#include "AvoidanceBehaviour.h"
#include "DxMath.h"
Vector3 HyEngine::AvoidanceBehaviour::CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock)
{
	// if no neighbors, return no adjustment
	if (context.size() == 0)
		return Vector3::Zero;

	Vector3 avoidanceMove = Vector3::Zero;
	int nAvoid = 0;

	for (auto& item : context)
	{
		if (std::abs(DxMath::Length((item->m_position - agent->GetTransform()->m_position).operator D3DXVECTOR3()))
			< flock->m_avoidDistance)
		{
			nAvoid++;
			avoidanceMove += agent->GetTransform()->m_position - item->m_position;
		}
	}
	if (nAvoid > 0)
		avoidanceMove = avoidanceMove /  (float)nAvoid;
	return avoidanceMove;
}
