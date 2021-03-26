#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Cell : public GameObject 
	{
	private  :
		explicit Cell(class Scene* scene, GameObject* parent, unsigned int cellIndex, ECellOption option, D3DXVECTOR3 position, unsigned int group = 100);
		virtual ~Cell();

	public :
		virtual void Initialize();
		virtual void Render() override;

		static Cell* Create(class Scene* scene, GameObject* parent, unsigned int cellIndex, ECellOption option, D3DXVECTOR3 position, unsigned int group = 100)
		{
			Cell* cell = new Cell(scene, parent, cellIndex , option, position, group);
			cell->Initialize();
			return cell;
		}

	public :
		int GetCellIndex() { return m_cellIndex; }
		void SetCellOption(int option) { m_cellOption = (ECellOption)option; }
		ECellOption GetCellOption() { m_cellOption; }
	private :
		int m_cellIndex;
		// 보여주기용 or 클릭용
		class Collider* m_pCollider;
		ECellOption m_cellOption;
		unsigned int m_group = 100; // 기본 100

	//protected :
	//	explicit Cell(class Scene* scene, GameObject* parent,
	//		const D3DXVECTOR3& pointA, const D3DXVECTOR3& pointB, const D3DXVECTOR3& pointC,
	//		const  ECellOption& cellOption, const unsigned int& group);
	//	virtual ~Cell() = default;

	//public :
	//	// Inherited via GameObject
	//	virtual void Initialize();
	//	virtual void Render() override;

	//	static Cell* Create(class Scene* scene, GameObject* parent,
	//		const D3DXVECTOR3& pointA, const D3DXVECTOR3& pointB, const D3DXVECTOR3& pointC,
	//		const  ECellOption& cellOption, const unsigned int& group);


	//	D3DXVECTOR3 GetPosition( EPoint point);
	//private:
	//	class ColorTriangle* m_pColorTriangle = nullptr;
	//	D3DCOLOR m_color;

	//	std::vector<D3DXVECTOR3> m_positions;
	//	std::vector<Cell*> m_neighbor;
	//	std::vector<class Line*> m_lines;

	//	unsigned long m_cellIndex;
	//	 ECellOption m_cellOption;
	//	bool m_bClicked;
	//	unsigned int m_group = 100; // 기본 100


	};
}

