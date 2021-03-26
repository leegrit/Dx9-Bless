#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Cell : public GameObject 
	{
	protected :
		explicit Cell(class Scene* scene, GameObject* parent,
			const Vector3& pointA, const Vector3& pointB, const Vector3& pointC,
			const NavMeshEnums::ECellOption& cellOption, const unsigned int& group);
		virtual ~Cell() = default;

	public :
		// Inherited via GameObject
		virtual void Initialize();
		virtual void Render() override;

		static Cell* Create(class Scene* scene, GameObject* parent,
			const Vector3& pointA, const Vector3& pointB, const Vector3& pointC,
			const NavMeshEnums::ECellOption& cellOption, const unsigned int& group);


		D3DXVECTOR3 GetPosition(NavMeshEnums::EPoint point);
	private:
		class ColorTriangle* m_pColorTriangle = nullptr;
		D3DCOLOR m_color;

		std::vector<Vector3> m_positions;
		std::vector<Cell*> m_neighbor;
		std::vector<class Line*> m_lines;

		unsigned long m_cellIndex;
		NavMeshEnums::ECellOption m_cellOption;
		bool m_bClicked;
		unsigned int m_group = 100; // ±âº» 100


	};
}

