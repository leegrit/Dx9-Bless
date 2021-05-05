#include "StandardEngineFramework.h"
#include "Pawn.h"
#include "NavMesh.h"
HyEngine::Pawn::Pawn(Scene * scene, GameObject * parent, NavMesh * navMesh, ESkinningType skinningType)
	: DynamicMesh(scene, parent, L"Pawn", skinningType),
	m_pNavMesh(navMesh)
{
	m_positionOld = D3DXVECTOR3(0, 0, 0);
}

HyEngine::Pawn::~Pawn()
{
}

void HyEngine::Pawn::Initialize(std::wstring dataPath)
{
	DynamicMesh::Initialize(dataPath);

}

void HyEngine::Pawn::Update()
{
	DynamicMesh::Update();

	if (IS_CLIENT && m_pNavMesh)
	{

		// navMesh 위에 있다면 높이를 맞추고
		// navMesh를 벗어났다면 이전 포지션으로 돌아온다.
		float height = 0;
		bool isOnMesh = false;
		isOnMesh = m_pNavMesh->IsOnMesh(m_pTransform->m_position.operator D3DXVECTOR3(), &height);
		if (isOnMesh)
		{
			m_pTransform->m_position.y() = height;
			m_positionOld = m_pTransform->m_position.operator D3DXVECTOR3();
		}
		else
		{
			m_pTransform->m_position = m_positionOld;
		}

	}
}

void HyEngine::Pawn::Render()
{
	DynamicMesh::Render();
}

void HyEngine::Pawn::UpdatedData(EDataType type)
{
	DynamicMesh::UpdatedData(type);
	m_positionOld = m_pTransform->m_position.operator D3DXVECTOR3();
}

Pawn * HyEngine::Pawn::Create(Scene * scene, GameObject * parent, NavMesh * navMesh, std::wstring dataPath)
{
	Pawn* pawn = new Pawn(scene, parent, navMesh);
	pawn->Initialize(dataPath);
	return pawn;
}

int HyEngine::Pawn::GetNavPrimIndex() const
{
	return m_navPrimIndex;
}
