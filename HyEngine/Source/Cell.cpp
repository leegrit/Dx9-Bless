#include "StandardEngineFramework.h"
#include "Cell.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"

using namespace NavMeshEnums;

HyEngine::Cell::Cell(Scene * scene, GameObject * parent,
	const Vector3& pointA, const Vector3& pointB, const Vector3& pointC,
	const NavMeshEnums::ECellOption& cellOption, const unsigned int& group)
	: GameObject(ERenderType::RenderTexture, scene, parent, L"Cell")
{
	m_color = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_positions.push_back(pointA);
	m_positions.push_back(pointB);
	m_positions.push_back(pointC);
	m_cellOption = cellOption;
	m_group = group;
}

void HyEngine::Cell::Initialize()
{

	// ���⼭ Line�� ������ָ� ���� �ѵ�
	// �װ� �� �����غ�����


	m_pColorTriangle = Geometry::CreateGeometry<ColorTriangle>((void*)m_color);
	ColorVertex * vertices = m_pColorTriangle->LockVertices();
	{

		vertices[(int)EPoint::POINT_A].x = m_points[(int)EPoint::POINT_A].x;
		vertices[(int)EPoint::POINT_A].y = m_points[(int)EPoint::POINT_A].y;
		vertices[(int)EPoint::POINT_A].z = m_points[(int)EPoint::POINT_A].z;

		vertices[(int)EPoint::POINT_B].x = m_points[(int)EPoint::POINT_B].x;
		vertices[(int)EPoint::POINT_B].y = m_points[(int)EPoint::POINT_B].y;
		vertices[(int)EPoint::POINT_B].z = m_points[(int)EPoint::POINT_B].z;

		vertices[(int)EPoint::POINT_C].x = m_points[(int)EPoint::POINT_C].x;
		vertices[(int)EPoint::POINT_C].y = m_points[(int)EPoint::POINT_C].y;
		vertices[(int)EPoint::POINT_C].z = m_points[(int)EPoint::POINT_C].z;

	}
	m_pColorTriangle->UnlockVertices();

}

void HyEngine::Cell::Render()
{
	GameObject::Render();

	assert(m_pColorTriangle);
	DEVICE->SetStreamSource(0, m_pColorTriangle->GetVertexBuffer(), 0, m_pColorTriangle->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pColorTriangle->GetDeclare());
	// index buffer�� �ʿ� ������ ���ϼ��� ���ؼ� ���
	DEVICE->SetIndices(m_pColorTriangle->GetIndexBuffer());

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pColorTriangle->GetVertexCount(), 0, m_pColorTriangle->GetPrimitiveCount());
}

Cell * HyEngine::Cell::Create(Scene * scene, GameObject * parent, const Vector3 & pointA, const Vector3 & pointB, const Vector3 & pointC, const NavMeshEnums::ECellOption & cellOption, const unsigned int & group)
{
	Cell * cell = new Cell(scene, parent, pointA, pointB, pointC, cellOption, group);
	cell->Initialize();
	return cell;
}

D3DXVECTOR3 HyEngine::Cell::GetPosition(NavMeshEnums::EPoint point)
{
	return m_positions[(int)point];
}

