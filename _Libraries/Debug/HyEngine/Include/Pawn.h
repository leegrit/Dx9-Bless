#pragma once
#include "DynamicMesh.h"

namespace HyEngine
{
	class ENGINE_DLL Pawn : public DynamicMesh
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	private :
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
		// NavMesh ���� ���� �� �ֽ�ȭ�ǰ� 
		// ��� ��� �������� �־��� ��ġ�� �Ű�����.
		D3DXVECTOR3 m_positionOld;
	};
}
