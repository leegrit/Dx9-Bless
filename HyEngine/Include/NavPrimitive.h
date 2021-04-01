#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Cell;
	class Line;
	class NavPrimitive : public GameObject
	{
	protected : 
		explicit NavPrimitive(class Scene* scene, GameObject* parent,
			Cell* cellA, Cell* cellB, Cell* cellC,
			const  ECellOption& cellOption, const unsigned int& group, unsigned int navPrimIndex);
		virtual ~NavPrimitive();

	public :
		// Inherited via GameObject
		virtual void Initialize();
		virtual void Render() override;

		static NavPrimitive* Create(class Scene* scene, GameObject* parent,
			Cell* cellA, Cell* cellB, Cell* cellC,
			const  ECellOption& cellOption, const unsigned int& group, unsigned int navPrimIndex);

		D3DXVECTOR3 GetPosition(EPoint point);
		Cell* GetCell(int cellIndex);
		const std::vector<Cell*>& GetCells();
		int GetNavPrimIndex()const;
	private :
		class ColorTriangle* m_pColorTriangle = nullptr;
		D3DCOLOR m_color;

		std::vector<Cell*> m_cells;
		//std::vector<NavPrimitive*> m_neighbor;
		//std::vector<Line*> m_lines;

		ECellOption m_cellOption;

		unsigned int m_navPrimIndex;

		// ±âº» 100
		unsigned int m_group = 100;


	};
}

