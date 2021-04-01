#include "StandardEngineFramework.h"
#include "NavPrimitive.h"
#include "Cell.h"
#include "Line.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"

HyEngine::NavPrimitive::NavPrimitive(Scene * scene, GameObject * parent, Cell * cellA, Cell * cellB, Cell * cellC, const ECellOption & cellOption, const unsigned int & group
	, unsigned int navPrimIndex)
	: GameObject(ERenderType::RenderTexture, scene, parent, L"NavPrimitive")
{
	m_color = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_cells.push_back(cellA);
	m_cells.push_back(cellB);
	m_cells.push_back(cellC);
	m_cellOption = cellOption;
	m_group = group;
	m_navPrimIndex = navPrimIndex;
}

HyEngine::NavPrimitive::~NavPrimitive()
{
	SAFE_DELETE(m_pColorTriangle);
	for (int i = 0; i < m_cells.size(); i++)
	{
		Object::Destroy(m_cells[i]);
	}
	m_cells.clear();
}

void HyEngine::NavPrimitive::Initialize()
{
	
	
	m_pColorTriangle = Geometry::CreateGeometry<ColorTriangle>((void*)&m_color);
	ColorVertex * vertices = m_pColorTriangle->LockVertices();
	{

		vertices[(int)EPoint::POINT_A].x = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_A].y = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_A].z = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.z();
																		
		vertices[(int)EPoint::POINT_B].x = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_B].y = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_B].z = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.z();
																		
		vertices[(int)EPoint::POINT_C].x = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_C].y = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_C].z = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.z();

	}
	m_pColorTriangle->UnlockVertices();
	
	
}

void HyEngine::NavPrimitive::Render()
{
	GameObject::Render();

	ColorVertex * vertices = m_pColorTriangle->LockVertices();
	{

		vertices[(int)EPoint::POINT_A].x = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_A].y = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_A].z = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.z();

		vertices[(int)EPoint::POINT_B].x = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_B].y = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_B].z = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.z();

		vertices[(int)EPoint::POINT_C].x = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_C].y = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_C].z = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.z();

	}
	m_pColorTriangle->UnlockVertices();

	assert(m_pColorTriangle);
	DEVICE->SetStreamSource(0, m_pColorTriangle->GetVertexBuffer(), 0, m_pColorTriangle->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pColorTriangle->GetDeclare());
	// index buffer는 필요 없지만 통일성을 위해서 사용
	DEVICE->SetIndices(m_pColorTriangle->GetIndexBuffer());

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pColorTriangle->GetVertexCount(), 0, m_pColorTriangle->GetPrimitiveCount());
}

NavPrimitive * HyEngine::NavPrimitive::Create(Scene * scene, GameObject * parent, Cell * cellA, Cell * cellB, Cell * cellC, const ECellOption & cellOption, const unsigned int & group, unsigned int navPrimIndex)
{
	NavPrimitive * primitive = new NavPrimitive(scene, parent, cellA, cellB, cellC, cellOption, group, navPrimIndex);
	primitive->Initialize();
	return primitive;
}

D3DXVECTOR3 HyEngine::NavPrimitive::GetPosition(EPoint point)
{
	//todo
	return m_cells[(int)point]->m_pTransform->m_position.operator D3DXVECTOR3();
}

Cell * HyEngine::NavPrimitive::GetCell(int cellIndex)
{
	for (auto& cell : m_cells)
	{
		if (cell->GetCellIndex() == cellIndex)
		{
			return cell;
		}
	}
	return nullptr;
}

const std::vector<Cell*>& HyEngine::NavPrimitive::GetCells()
{
	return m_cells;
}

int HyEngine::NavPrimitive::GetNavPrimIndex() const
{
	return m_navPrimIndex;
}
