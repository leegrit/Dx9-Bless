#include "StandardEngineFramework.h"
#include "FlockAgent.h"
#include "DxMath.h"
#include "FlockSystem.h"


void HyEngine::FlockAgent::MoveDefault(Vector3 velocity)
{
	if (m_currentVelocity != Vector3::Zero)
	{
		D3DXVec3Lerp(&m_currentVelocity.operator D3DXVECTOR3()
			, &m_currentVelocity.operator D3DXVECTOR3()
			, &velocity.operator D3DXVECTOR3(), 0.5f);
	}
	else
	{
		m_currentVelocity = velocity;
	}

	D3DXVECTOR3 result;
	D3DXVec3Lerp(&result,
		&GetTransform()->m_position.operator D3DXVECTOR3(),
		&(GetTransform()->m_position + m_currentVelocity).operator D3DXVECTOR3(),
		(float)TIMER->getDeltaTime());
	GetTransform()->SetPosition(result);

	// TODO 회전은 보류

}
void FlockAgent:: SetFlock(FlockSystem* flock)
{
	m_pAgentFlock = flock;
}
