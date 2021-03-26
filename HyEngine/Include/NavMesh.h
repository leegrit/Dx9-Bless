#pragma once

namespace HyEngine
{
	class NavMesh
	{
	public :
		// --------------------------------------------------------
		// CONSTRUCTOR & DESTRUCTOR
		// --------------------------------------------------------
		explicit NavMesh();
		~NavMesh();
	public :
		// ------------------------------------------------------
		// GETTERS
		// ------------------------------------------------------
		const std::vector<class Cell*>& GetCells();
		const int& GetCurCellIndex() const;
		const NavMeshEnums::ECellOption& GetCellOption(const int& cellIndex);
		const int& GetGroup(const int& cellIndex);

	public :
		// --------------------------------------------------------
		// SETTERS
		// --------------------------------------------------------
		void SetCurrentIndex(const unsigned long cellIndex);
		void SetGroup(const unsigned long& cellIndex, const unsigned int& group);

	public :
		// ----------------------------------------------------------
		// PUBLIC METHODS
		// ----------------------------------------------------------
		bool TryPickingCell(const D3DXVECTOR3& pickingPos, _Out_ unsigned long* cellIndex);
		bool TryDeleteCell(const D3DXVECTOR3& pickingPos, _Out_ unsigned long* cellIndex);
		void ClearCell();
		void ClearPickedPoses();
		void ChangeCellOption(const unsigned long& cellIndex, const NavMeshEnums::ECellOption& option);
		void ChangeCellOption(const unsigned int& group, const NavMeshEnums::ECellOption& option);




	private :
		// ---------------------------------------------------
		// VARIABLES
		// --------------------------------------------------
		std::vector<class Cell*> m_cells;
		unsigned long m_currentCellIndex;
		// 피킹된 vector들을 모아서
		// 3개가 되었을 때 Cell을 하나 생성한다.
		std::vector<D3DXVECTOR3> m_pickedVectors;
		float m_pickRadius = 0.2f;

	};
}

