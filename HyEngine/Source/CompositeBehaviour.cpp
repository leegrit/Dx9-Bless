#include "StandardEngineFramework.h"
#include "CompositeBehaviour.h"

Vector3 HyEngine::CompositeBehaviour::CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock)
{
	assert(m_weights.size() == m_behaviours.size());

	Vector3 move = Vector3::Zero;

	for (UINT i = 0; i < m_behaviours.size(); i++)
	{
		Vector3 partialMove = m_behaviours[i]->CalculateMove(agent, context, flock);
		float length = D3DXVec3Length(&partialMove.operator D3DXVECTOR3());
		if (length > 100)
			int a = 0;
		if (partialMove != Vector3::Zero3)
		{
			move += partialMove * m_weights[i];
		}
	}
	return move;
}
