#include "StandardEngineFramework.h"
#include "Cell.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"

HyEngine::Cell::Cell(Scene * scene, GameObject * parent, unsigned int cellIndex, ECellOption option, D3DXVECTOR3 position, unsigned int group)
	:GameObject(ERenderType::None, scene, parent, L"Cell"),
	m_cellIndex(cellIndex),
	m_cellOption(option),
	m_group(group)
{
	m_pTransform->SetPosition(position);
}

HyEngine::Cell::~Cell()
{
	Object::Destroy(m_pCollider);
}

void HyEngine::Cell::Initialize()
{
	m_pCollider = SphereCollider::Create(EColliderType::Multipurpose, this, 5, Layer::Default, [](Collider*) {});

}

void HyEngine::Cell::Render()
{
	assert(false);
}

bool HyEngine::Cell::Compare(const Cell * pCell)const
{
	if (m_pTransform->m_position == pCell->m_pTransform->m_position)
		return true;
	else
		return false;
}
