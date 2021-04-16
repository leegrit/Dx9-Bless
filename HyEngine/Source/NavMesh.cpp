#include "StandardEngineFramework.h"
#include "NavMesh.h"
#include "Cell.h"
#include "NavPrimitive.h"
#include "VectorData.h"
#include "CellData.h"
#include "HierarchyData.h"
#include "Deserializer.h"

HyEngine::NavMesh::NavMesh(Scene* scene, GameObject* parent)
	: GameObject(ERenderType::None, scene, parent, L"NavMesh")
{

}

HyEngine::NavMesh::~NavMesh()
{
	for (auto& cell : m_pickedCell)
		Object::Destroy(cell);
	m_pickedCell.clear();
	m_navPrimitives.clear();

}

void HyEngine::NavMesh::Render()
{
	assert(false);
}

void HyEngine::NavMesh::UpdatedData(EDataType dataType)
{
	if (dataType == EDataType::CellData)
	{
		// 여기서 업데이트 된 데이터 기반으로 재구성한다.
		assert(m_pCellData);

		Cell* cell = nullptr;
		for (auto& navPrim : m_navPrimitives)
		{
			Cell* temp = navPrim->GetCell(m_pCellData->cellIndex);
			if (temp != nullptr)
			{
				cell = temp;
				break;
			}
		}
		assert(cell);

		D3DXVECTOR3 prePos = cell->m_pTransform->m_position;
		cell->m_pTransform->SetPosition(m_pCellData->position.x, m_pCellData->position.y, m_pCellData->position.z);
		cell->SetCellOption(m_pCellData->option);

		if (m_cellEditMode == ECellEditMode::Similar)
		{
			std::vector<Cell*> similarCells;

			for (auto& navPrim : m_navPrimitives)
			{
				std::vector<Cell*> tempCells = navPrim->GetCells();
				for (auto& tempCell : tempCells)
				{
					if (tempCell->m_pTransform->m_position == prePos)
					{
						similarCells.push_back(tempCell);
					}
				}
			}
			
			for (auto& similarCell : similarCells)
			{
				similarCell->m_pTransform->SetPosition(m_pCellData->position.x, m_pCellData->position.y, m_pCellData->position.z);
			}
		}


	

	}
}

const std::vector<class NavPrimitive*>& HyEngine::NavMesh::GetNavPrimitives()
{
	return m_navPrimitives;
}


const  ECellOption & HyEngine::NavMesh::GetCellOption(const int & cellIndex)
{
	// TODO: insert return statement here
	assert(false);
	return ECellOption::NORMAL;
}

const int & HyEngine::NavMesh::GetGroup(const int & cellIndex)
{
	// TODO: insert return statement here
	assert(false);
	return 0;
}


void HyEngine::NavMesh::SetGroup(const unsigned long & cellIndex, const unsigned int & group)
{
	// 아직 미구현
	// TODO
	assert(false);
}

void HyEngine::NavMesh::Initialize(std::wstring dataPath)
{
	std::shared_ptr<HierarchyData> data = Deserializer::Deserialize(dataPath);
	
	InsertGameData(data->gameObjectData);

	for (int i = 0; i < data->cells.size(); i++)
	{
		D3DXVECTOR3 position;
		position.x = data->cells[i]->position.x;
		position.y = data->cells[i]->position.y;
		position.z = data->cells[i]->position.z;

		AddCell(position, (ECellOption)data->cells[i]->option,
			data->cells[i]->group);
	}
}

bool HyEngine::NavMesh::TryPickingCell(_Out_ VectorData* pickedPos,  const D3DXVECTOR3& pickingPos, const  ECellOption& option, const unsigned int& group )
{


	D3DXVECTOR3 pos = pickingPos;
	bool isTouched = false;
	for (auto& navPrimitive : m_navPrimitives)
	{
		for (int i = 0; i < (int)EPoint::POINT_END; i++)
		{
			D3DXVECTOR3 pointPos = navPrimitive->GetPosition((EPoint)i);
			float dist = D3DXVec3Length(&(pos - pointPos));

			if (dist > m_pickRadius)
				continue;
			pos = pointPos;
			isTouched = true;
		}
	}

	switch (m_pickedCell.size())
	{
	case 0: // 첫번째 cell

		break;
	case 1: // 두번째 cell
		// 중복은 안된다.
		if (pos == m_pickedCell[0]->m_pTransform->m_position.operator D3DXVECTOR3())
			return false;
		break;
	case 2 : // 세번째 cell
		// 중복은 안된다.
		if (pos == m_pickedCell[0]->m_pTransform->m_position.operator D3DXVECTOR3() || 
			pos == m_pickedCell[1]->m_pTransform->m_position.operator D3DXVECTOR3())
			return false;
		break;
	default :
		assert(false);
	}

	// cell 만들기 전에 위치값을 보관한다.
	Cell* cell = Cell::Create(GetScene(), nullptr, m_nextCellIndex++,  option, pos);

	// 결과 전달
	pickedPos->x = pos.x;
	pickedPos->y = pos.y;
	pickedPos->z = pos.z;


	m_pickedCell.push_back(cell);

	if (m_pickedCell.size() == 3)
	{
		NavPrimitive* navPrimitive = NavPrimitive::Create(GetScene(), nullptr,
			m_pickedCell[(int)EPoint::POINT_A],
			m_pickedCell[(int)EPoint::POINT_B],
			m_pickedCell[(int)EPoint::POINT_C],
			option, group, m_nextNavPrimIndex++);
		assert(navPrimitive);
		m_navPrimitives.push_back(navPrimitive);
		m_pickedCell.clear();
	}
	return true;
}

void HyEngine::NavMesh::AddCell(const D3DXVECTOR3 & position, const ECellOption & option, const unsigned int & group)
{

	// cell 만들기 전에 위치값을 보관한다.
	Cell* cell = Cell::Create(GetScene(), nullptr, m_nextCellIndex++, option, position);

	m_pickedCell.push_back(cell);

	if (m_pickedCell.size() == 3)
	{
		NavPrimitive* navPrimitive = NavPrimitive::Create(GetScene(), nullptr,
			m_pickedCell[(int)EPoint::POINT_A],
			m_pickedCell[(int)EPoint::POINT_B],
			m_pickedCell[(int)EPoint::POINT_C],
			option, group, m_nextNavPrimIndex++);
		assert(navPrimitive);
		m_navPrimitives.push_back(navPrimitive);
		m_pickedCell.clear();
	}
}

//bool HyEngine::NavMesh::TryDeleteCell(const D3DXVECTOR3 & pickingPos, unsigned long * cellIndex)
//{
//	return false;
//}

void HyEngine::NavMesh::ClearCell()
{
	for (auto& navPrimitive : m_navPrimitives)
		Object::Destroy(navPrimitive);
	m_navPrimitives.clear();
	for (auto& cell : m_pickedCell)
		Object::Destroy(cell);
	m_pickedCell.clear();
}

void HyEngine::NavMesh::ClearPickedPoses()
{
	for (auto& cell : m_pickedCell)
		Object::Destroy(cell);
	m_pickedCell.clear();
}

void HyEngine::NavMesh::ChangeCellOption(const unsigned long & cellIndex, const  ECellOption & option)
{
	// 미구현
	assert(false);
}

void HyEngine::NavMesh::ChangeCellOption(const unsigned int & group, const  ECellOption & option)
{
	// 미구현
	assert(false);
}

void HyEngine::NavMesh::CreateCell(CellData * data)
{
	D3DXVECTOR3 position;
	position.x = data->position.x;
	position.y = data->position.y;
	position.z = data->position.z;

	Cell* cell = Cell::Create(GetScene(), nullptr, data->cellIndex, (ECellOption)data->option, position, data->group);


	m_pickedCell.push_back(cell);

	if (m_pickedCell.size() == 3)
	{
		NavPrimitive* navPrimitive = NavPrimitive::Create(GetScene(), nullptr,
			m_pickedCell[(int)EPoint::POINT_A],
			m_pickedCell[(int)EPoint::POINT_B],
			m_pickedCell[(int)EPoint::POINT_C],
			(ECellOption)data->option,
			data->group, m_nextNavPrimIndex++);
		assert(navPrimitive);
		m_navPrimitives.push_back(navPrimitive);
		m_pickedCell.clear();
	}
}

void HyEngine::NavMesh::RemoveNavPrim(int navPrimIndex)
{
	for (int i = 0; i < m_navPrimitives.size(); i++)
	{
		if (m_navPrimitives[i]->GetNavPrimIndex() == navPrimIndex)
		{
			Object::Destroy(m_navPrimitives[i]);
			m_navPrimitives.erase(m_navPrimitives.begin() + i);
			i--;
			return;
		}
	}
}

void HyEngine::NavMesh::SetCellEditMode(ECellEditMode cellEditMode)
{
	m_cellEditMode = cellEditMode;
}

bool HyEngine::NavMesh::IsOnMesh(D3DXVECTOR3 position, float * yPos)
{
	// 삼각형 순회
	for (auto& prim : m_navPrimitives)
	{
		if (DxMath::PointInTriangle(position,
			prim->GetPosition(EPoint::POINT_A),
			prim->GetPosition(EPoint::POINT_B),
			prim->GetPosition(EPoint::POINT_C)))
		{
			// 평면의 방정식을 활용한 높이 구하기

			*yPos = DxMath::GetHeightFromPoints(position,
				prim->GetPosition(EPoint::POINT_A),
				prim->GetPosition(EPoint::POINT_B),
				prim->GetPosition(EPoint::POINT_C));

			return true;
		}
	}
	return false;
}

bool HyEngine::NavMesh::PickOnMesh(D3DXVECTOR3 origin, D3DXVECTOR3 direction, D3DXVECTOR3 * pickedPos)
{
	// 미구현
	assert(false);
	return false;
}

unsigned long NavMesh::m_nextCellIndex = 0;
unsigned long NavMesh::m_nextNavPrimIndex = 0;
