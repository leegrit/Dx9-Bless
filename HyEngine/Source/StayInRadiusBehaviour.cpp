#include "StandardEngineFramework.h"
#include "StayInRadiusBehaviour.h"





Vector3 HyEngine::StayInRadiusBehaviour::CalculateMove(FlockAgent * agent, std::vector<Transform*> context, FlockSystem * flock)
{
	center = Vector3::Zero; // 임시 / 나중에 player 위치로 수정

	Vector3 centerOffset = center - agent->GetTransform()->m_position;
	float t = DxMath::Length(centerOffset.operator D3DXVECTOR3()) / radius;
	if (t < 0.9f)
	{
		return Vector3::Zero;
	}
	D3DXVECTOR3 result;
	D3DXVec3Normalize(&result, &centerOffset.operator D3DXVECTOR3());
	//return result;
	//return centerOffset * t * t;
	//return result * t * t;
	return Vector3::Zero;
}
