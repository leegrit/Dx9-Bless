#pragma once
#include "Animator.h"

namespace HyEngine
{
	class MeshAnimator final : public Animator
	{
	private :
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
		explicit MeshAnimator(class GameObject* owner, ID3DXMesh* mesh);
		virtual ~MeshAnimator() override;

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;


		//////////////////////////////////////////////////////////////////////////
		// CREATOR
		//////////////////////////////////////////////////////////////////////////
	public :
		static MeshAnimator* Create(GameObject* owner, ID3DXMesh* mesh)
		{
			MeshAnimator* animator = new MeshAnimator(owner, mesh);
			animator->Initialize();
			return animator;
		}


	public :

	protected: 

		//////////////////////////////////////////////////////////////////////////
		// PRIVATE METHODS
		//////////////////////////////////////////////////////////////////////////
	private :
		void FrameMove();




		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		ID3DXMesh * m_pMesh;
		UINT m_face;
		UINT m_vertices;
		UINT m_perVertex;
		UINT m_fvf;
		UINT m_index;
		UINT m_aniVertex;
		UINT m_aniIndex;
		UINT m_aniFace;
		IDirect3DVertexBuffer9* m_pVB;
		IDirect3DIndexBuffer9* m_pIB;
		IDirect3DVertexBuffer9* m_pAniVB;
		IDirect3DIndexBuffer9* m_pAniIB;
		class ModelVertex* m_pVertices;
		class ModelVertex* m_pVerticesAni;
		WORD* m_pIndices;
		WORD* m_pIndicesAni;

	private :
		int m_cnt = 3;
		int m_start = 0;
		int m_next = 1;
		float m_scale = 0.0f;
		int m_tmp = 0;
	};

}