#pragma once
#include "DynamicMesh.h"

namespace HyEngine
{
	class ENGINE_DLL Pawn : public DynamicMesh
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Pawn(Scene* scene, GameObject* parent, NavMesh* navMesh);
		virtual ~Pawn();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize(std::wstring dataPath);
		virtual void Update() override;
		virtual void Render() override;
		virtual void UpdatedData(EDataType type) override;
		static Pawn* Create(Scene* scene, GameObject* parent, NavMesh* navMesh, std::wstring dataPath);



		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		class NavMesh* m_pNavMesh;
		// NavMesh 위에 있을 때 최신화되고 
		// 벗어날 경우 마지막에 있었던 위치로 옮겨진다.
		D3DXVECTOR3 m_positionOld;
	};
}
