#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL Terrain : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Terrain(Scene* scene, GameObject* parent, std::wstring name);
		/* For.Editor */
		explicit Terrain(Scene* scene, GameObject* parent, std::wstring name, int editID);
		virtual ~Terrain();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize();
		virtual void Update() override;
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		static Terrain* Create(Scene* scene, GameObject* parent, int editID)
		{
			Terrain* terrain = new Terrain(scene, parent,L"Terrain", editID);
			terrain->Initialize();
			return terrain;
		}

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHODS
		//////////////////////////////////////////////////////////////////////////
	public :
		bool TryPickOnTerrain(D3DXVECTOR3 origin, D3DXVECTOR3 direction, _Out_ D3DXVECTOR3 * pPickedPos);



		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private : /* For.Render */
		IDirect3DVertexBuffer9* m_pVB = nullptr;
		size_t m_vertexCount = 0; 
		size_t m_vertexSize = 0;
		size_t m_triCount = 0;
		unsigned int m_fvf;
		IDirect3DVertexDeclaration9* m_pDeclaration;


		IDirect3DIndexBuffer9* m_pIB = nullptr;
		D3DFORMAT m_indexFMT = D3DFMT_INDEX32;
		size_t m_indexSize = 0;

		// vertexBuffer를 Lock, Unlock하지 않고
		// 바로 vertex position 값을 받아오기 위한 값.
		std::vector<D3DXVECTOR3> m_vtxPositions;

	private : /* For.Resources */
		IDirect3DTexture9* m_pTexture = nullptr;
		IDirect3DTexture9* m_pNormal = nullptr;


	private : /* For.Terrain */
		size_t m_vertexCountX = 10;
		size_t m_vertexCountZ = 10;
		float m_textureCountX = 20.f;
		float m_textureCountZ = 20.f;
		float m_vertexInterval = 1.f;
	};
}

