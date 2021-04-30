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
		bool Compare(const Cell* pCell)const;
	private :
		int m_cellIndex;
		// 보여주기용 or 클릭용
		class Collider* m_pCollider;
		ECellOption m_cellOption;
		unsigned int m_group = 100; // 기본 100


	};
}

