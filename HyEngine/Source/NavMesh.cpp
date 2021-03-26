#include "StandardEngineFramework.h"
#include "NavMesh.h"
#include "Cell.h"
#include "NavPrimitive.h"
#include "VectorData.h"
#include "CellData.h"

HyEngine::NavMesh::NavMesh(Scene* scene, GameObject* parent)
	: GameObject(ERenderType::None, scene, parent, L"NavMesh")
{
	m_nextCellIndex = 0;
	m_nextNavPrimIndex = 0;
}

HyEngine::NavMesh::~NavMesh()
{

}

void HyEngine::NavMesh::Render()
{
	assert(false);
}

void HyEngine::NavMesh::UpdatedData(EDataType dataType)
{
	if (dataType == EDataType::CellData)
	{
		// ���⼭ ������Ʈ �� ������ ������� �籸���Ѵ�.
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
	// ���� �̱���
	// TODO
	assert(false);
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
	case 0: // ù��° cell

		break;
	case 1: // �ι�° cell
		// �ߺ��� �ȵȴ�.
		if (pos == m_pickedCell[0]->m_pTransform->m_position.operator D3DXVECTOR3())
			return false;
		break;
	case 2 : // ����° cell
		// �ߺ��� �ȵȴ�.
		if (pos == m_pickedCell[0]->m_pTransform->m_position.operator D3DXVECTOR3() || 
			pos == m_pickedCell[1]->m_pTransform->m_position.operator D3DXVECTOR3())
			return false;
		break;
	default :
		assert(false);
	}

	// cell ����� ���� ��ġ���� �����Ѵ�.
	Cell* cell = Cell::Create(GetScene(), nullptr, m_nextCellIndex++,  option, pos);

	// ��� ����
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
	// �̱���
	assert(false);
}

void HyEngine::NavMesh::ChangeCellOption(const unsigned int & group, const  ECellOption & option)
{
	// �̱���
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

void HyEngine::NavMesh::SetCellEditMode(ECellEditMode cellEditMode)
{
	m_cellEditMode = cellEditMode;
}
