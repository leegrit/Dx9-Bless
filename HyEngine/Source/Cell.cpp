#include "StandardEngineFramework.h"
#include "Cell.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"


//
//HyEngine::Cell::Cell(Scene * scene, GameObject * parent,
//	const D3DXVECTOR3& pointA, const D3DXVECTOR3& pointB, const D3DXVECTOR3& pointC,
//	const  ECellOption& cellOption, const unsigned int& group)
//	: GameObject(ERenderType::RenderTexture, scene, parent, L"Cell")
//{
//	m_color = D3DCOLOR_ARGB(255, 255, 0, 0);
//	m_positions.push_back(pointA);
//	m_positions.push_back(pointB);
//	m_positions.push_back(pointC);
//	m_cellOption = cellOption;
//	m_group = group;
//}
//
//void HyEngine::Cell::Initialize()
//{
//
//	// 여기서 Line도 만들어주면 좋긴 한데
//	// 그건 좀 생각해봐야함
//
//
//	m_pColorTriangle = Geometry::CreateGeometry<ColorTriangle>((void*)&m_color);
//	ColorVertex * vertices = m_pColorTriangle->LockVertices();
//	{
//
//		vertices[(int)EPoint::POINT_A].x = m_positions[(int)EPoint::POINT_A].x;
//		vertices[(int)EPoint::POINT_A].y = m_positions[(int)EPoint::POINT_A].y;
//		vertices[(int)EPoint::POINT_A].z = m_positions[(int)EPoint::POINT_A].z;
//
//		vertices[(int)EPoint::POINT_B].x = m_positions[(int)EPoint::POINT_B].x;
//		vertices[(int)EPoint::POINT_B].y = m_positions[(int)EPoint::POINT_B].y;
//		vertices[(int)EPoint::POINT_B].z = m_positions[(int)EPoint::POINT_B].z;
//
//		vertices[(int)EPoint::POINT_C].x = m_positions[(int)EPoint::POINT_C].x;
//		vertices[(int)EPoint::POINT_C].y = m_positions[(int)EPoint::POINT_C].y;
//		vertices[(int)EPoint::POINT_C].z = m_positions[(int)EPoint::POINT_C].z;
//
//	}
//	m_pColorTriangle->UnlockVertices();
//
//}
//
//void HyEngine::Cell::Render()
//{
//	GameObject::Render();
//
//	assert(m_pColorTriangle);
//	DEVICE->SetStreamSource(0, m_pColorTriangle->GetVertexBuffer(), 0, m_pColorTriangle->GetVertexSize());
//	DEVICE->SetVertexDeclaration(m_pColorTriangle->GetDeclare());
//	// index buffer는 필요 없지만 통일성을 위해서 사용
//	DEVICE->SetIndices(m_pColorTriangle->GetIndexBuffer());
//
//	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pColorTriangle->GetVertexCount(), 0, m_pColorTriangle->GetPrimitiveCount());
//}
//
//Cell * HyEngine::Cell::Create(Scene * scene, GameObject * parent, const D3DXVECTOR3 & pointA, const D3DXVECTOR3 & pointB, const D3DXVECTOR3 & pointC, const  ECellOption & cellOption, const unsigned int & group)
//{
//	Cell * cell = new Cell(scene, parent, pointA, pointB, pointC, cellOption, group);
//	cell->Initialize();
//	return cell;
//}
//
//D3DXVECTOR3 HyEngine::Cell::GetPosition( EPoint point)
//{
//	return m_positions[(int)point];
//}
//

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
	m_pCollider = SphereCollider::Create(EColliderType::Multipurpose, this, 1, Layer::Default, [](Collider*) {});

}

void HyEngine::Cell::Render()
{
	assert(false);
}
