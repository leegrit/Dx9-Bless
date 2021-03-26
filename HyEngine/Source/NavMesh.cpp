#include "StandardEngineFramework.h"
#include "NavMesh.h"
#include "Cell.h"

using namespace NavMeshEnums;

HyEngine::NavMesh::NavMesh()
{
	m_currentCellIndex = -1;
}

HyEngine::NavMesh::~NavMesh()
{

}

const std::vector<class Cell*>& HyEngine::NavMesh::GetCells()
{
	// TODO: insert return statement here
}

const int & HyEngine::NavMesh::GetCurCellIndex() const
{
	// TODO: insert return statement here
}

const NavMeshEnums::ECellOption & HyEngine::NavMesh::GetCellOption(const int & cellIndex)
{
	// TODO: insert return statement here
}

const int & HyEngine::NavMesh::GetGroup(const int & cellIndex)
{
	// TODO: insert return statement here
}

void HyEngine::NavMesh::SetCurrentIndex(const unsigned long cellIndex)
{
}

void HyEngine::NavMesh::SetGroup(const unsigned long & cellIndex, const unsigned int & group)
{
}

bool HyEngine::NavMesh::TryPickingCell(const D3DXVECTOR3 & pickingPos, unsigned long * cellIndex)
{
	D3DXVECTOR3 pos = pickingPos;
	for (auto& cell : m_cells)
	{
		for (int i = 0; i < (int)EPoint::POINT_END; i++)
		{
			D3DXVECTOR3 pointPos = cell->GetPosition((EPoint)i);
			float dist = D3DXVec3Length(&(pos - pointPos));

			if (dist > m_pickRadius)
				continue;
			pos = pointPos;
		}
	}

	// cell 만들기 전에 위치값을 보관한다.
	m_pickedVectors.push_back(pos);

	if (m_pickedVectors.size() == 3)
	{
			
	}
	return false;
}

bool HyEngine::NavMesh::TryDeleteCell(const D3DXVECTOR3 & pickingPos, unsigned long * cellIndex)
{
	return false;
}

void HyEngine::NavMesh::ClearCell()
{
}

void HyEngine::NavMesh::ClearPickedPoses()
{
}

void HyEngine::NavMesh::ChangeCellOption(const unsigned long & cellIndex, const NavMeshEnums::ECellOption & option)
{
}

void HyEngine::NavMesh::ChangeCellOption(const unsigned int & group, const NavMeshEnums::ECellOption & option)
{
}
