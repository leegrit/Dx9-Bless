#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL Mesh abstract : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR 
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Mesh(ERenderType renderType, Scene * scene, GameObject* parent, std::wstring name);
		virtual ~Mesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Render() override;
		virtual void DrawPrimitive(ID3DXEffect* pShader) override;
		virtual void UpdatedData(EDataType dataType) override;

		//////////////////////////////////////////////////////////////////////////
		// VIRTUAL
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);


		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		void RenderBoundingMesh(ID3DXEffect* pEffect);
		void OcclusionCulled(bool isCulled);
		bool IsOcclusionCulled();

		//////////////////////////////////////////////////////////////////////////
		// PROTECTED METHOD
		//////////////////////////////////////////////////////////////////////////
	protected :
		void CreateBoundingMesh(D3DXVECTOR3 center, float m_radius);

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		/* For Occlusion Query */
		ID3DXMesh* m_pBoundingMesh = nullptr;
		bool m_occlusionCulled = false;
		D3DXVECTOR3 m_boundingCenter;
	};

}