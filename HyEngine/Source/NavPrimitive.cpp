#include "StandardEngineFramework.h"
#include "NavPrimitive.h"
#include "Cell.h"
#include "Line.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"

HyEngine::NavPrimitive::NavPrimitive(Scene * scene, GameObject * parent, Cell * cellA, Cell * cellB, Cell * cellC, const ECellOption & cellOption, const unsigned int & group
	, unsigned int navPrimIndex)
	: GameObject(ERenderType::RenderAlpha, scene, parent, L"NavPrimitive") // alpha 블렌드는 필요없지만 light영향을 받지 않게 하기위해 renderalpha로 설정한다.
{
	m_color = D3DCOLOR_ARGB(255, 0, 255, 0);
	m_cells.push_back(cellA);
	m_cells.push_back(cellB);
	m_cells.push_back(cellC);
	m_cellOption = cellOption;
	m_group = group;
	m_navPrimIndex = navPrimIndex;

	m_neighbors.resize((int)ENeighbor::NEIGHBOR_END);
	m_neighbors[(int)ENeighbor::NEIGHBOR_AB] = nullptr;
	m_neighbors[(int)ENeighbor::NEIGHBOR_BC] = nullptr;
	m_neighbors[(int)ENeighbor::NEIGHBOR_CA] = nullptr;

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
		vertices[(int)EPoint::POINT_A].color = D3DXCOLOR(0.5f, 1, 0, 0.5f);
		
		vertices[(int)EPoint::POINT_B].x = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_B].y = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_B].z = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.z();
		vertices[(int)EPoint::POINT_B].color = D3DXCOLOR(0.5f, 0, 1, 0.5f);

		vertices[(int)EPoint::POINT_C].x = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_C].y = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.y();
		vertices[(int)EPoint::POINT_C].z = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.z();
		vertices[(int)EPoint::POINT_C].color = D3DXCOLOR(0.5f, 0, 0, 0.5f);
	}
	m_pColorTriangle->UnlockVertices();
	
	
}

void HyEngine::NavPrimitive::Render()
{
	GameObject::Render();

#ifdef _DEBUG

	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderNavMesh);
		if (bRender == false)
			return;
	}

	if (IS_EDITOR)
	{

	}
	else
	{
		/* EDIT_MODE에만 그린다. */
// 		if (ENGINE->GetGameMode() == EGameMode::GAME_MODE)
// 			return;
	}

	/* vertex의 위치를 cell의 위치로 업데이트해준다. */
	ColorVertex * vertices = m_pColorTriangle->LockVertices();
	{
		/* For resolve ZFighting */
		float bias = 0;
#ifdef _DEBUG
		bias = 0.01f;
#endif

		vertices[(int)EPoint::POINT_A].x = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_A].y = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.y() + bias;
		vertices[(int)EPoint::POINT_A].z = m_cells[(int)EPoint::POINT_A]->m_pTransform->m_position.z();

		vertices[(int)EPoint::POINT_B].x = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_B].y = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.y() + bias;
		vertices[(int)EPoint::POINT_B].z = m_cells[(int)EPoint::POINT_B]->m_pTransform->m_position.z();

		vertices[(int)EPoint::POINT_C].x = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.x();
		vertices[(int)EPoint::POINT_C].y = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.y() + bias;
		vertices[(int)EPoint::POINT_C].z = m_cells[(int)EPoint::POINT_C]->m_pTransform->m_position.z();

	}

	/* GetShader */
	if (m_pShader == nullptr)
	{
		if (IS_EDITOR)
			EDIT_ENGINE->TryGetShader(L"DiffuseShader", &m_pShader);
		else
			ENGINE->TryGetShader(L"DiffuseShader", &m_pShader);
	}
	assert(m_pShader);

	/* Get Selected cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	/* Set world, view and projection */
	m_pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
	m_pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

	m_pShader->SetTechnique("DiffuseShader");
	m_pShader->Begin(0, 0);
	{
		m_pShader->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pColorTriangle->GetVertexBuffer(), 0, m_pColorTriangle->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pColorTriangle->GetDeclare());
		// index buffer는 필요 없지만 통일성을 위해서 사용
		DEVICE->SetIndices(m_pColorTriangle->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pColorTriangle->GetVertexCount(), 0, m_pColorTriangle->GetPrimitiveCount());

		m_pShader->EndPass();
	}
	m_pShader->End();
#endif
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
	assert(cellIndex <= 3);
	return m_cells[cellIndex];
	/*for (auto& cell : m_cells)
	{
		if (cell->GetCellIndex() == cellIndex)
		{
			return cell;
		}
	}
	return nullptr;*/
}

const std::vector<Cell*>& HyEngine::NavPrimitive::GetCells()
{
	return m_cells;
}

int HyEngine::NavPrimitive::GetNavPrimIndex() const
{
	return m_navPrimIndex;
}

NavPrimitive * HyEngine::NavPrimitive::GetNeighbor(ENeighbor index)
{
	return m_neighbors[(int)index];
}

const  std::vector<NavPrimitive*>& HyEngine::NavPrimitive::GetNeighbors() const
{
	return m_neighbors;
}

void HyEngine::NavPrimitive::SetNeighbor(ENeighbor index, NavPrimitive * neighbor)
{
	m_neighbors[(int)index] = neighbor;
}

bool HyEngine::NavPrimitive::ComparePoint(const Cell * pPointA, const Cell * pPointB, NavPrimitive * pNavPrim)
{
	if(m_cells[(int)EPoint::POINT_A]->Compare(pPointA))
	{
		if (m_cells[(int)EPoint::POINT_B]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_AB] = pNavPrim;
			return true;
		}
		if (m_cells[(int)EPoint::POINT_C]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_CA] = pNavPrim;
			return true;
		}
	}

	if(m_cells[(int)EPoint::POINT_B]->Compare(pPointA))
	{
		if (m_cells[(int)EPoint::POINT_A]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_AB] = pNavPrim;
			return true;
		}
		if (m_cells[(int)EPoint::POINT_C]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_BC] = pNavPrim;
			return true;
		}
	}
	if (m_cells[(int)EPoint::POINT_C]->Compare(pPointA))
	{
		if (m_cells[(int)EPoint::POINT_B]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_BC] = pNavPrim;
			return true;
		}
		if (m_cells[(int)EPoint::POINT_A]->Compare(pPointB))
		{
			m_neighbors[(int)ENeighbor::NEIGHBOR_CA] = pNavPrim;
			return true;
		}
	}
	return false;
}
