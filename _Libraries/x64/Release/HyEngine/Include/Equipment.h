#pragma once
#include "Mesh.h"

namespace HyEngine
{
	class ENGINE_DLL Equipment : public Mesh
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Equipment(Scene* scene, GameObject* pOwner, std::wstring name);
		virtual ~Equipment();


		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize(std::wstring xFilePath, std::wstring boneName);
		virtual void Update() override;
		virtual void Render() override;
		virtual void PostRender(ID3DXEffect * pEffect) override;
		virtual void DrawPrimitive(ID3DXEffect* pShader) override;
		virtual void UpdatedData(EDataType dataType) override;
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);



		//////////////////////////////////////////////////////////////////////////
		// CALLBACK
		//////////////////////////////////////////////////////////////////////////
	public:
		void OnRenderBegin(void*);


		//////////////////////////////////////////////////////////////////////////
		// PUBLIC_METHOD
		//////////////////////////////////////////////////////////////////////////
	public :


		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		GameObject* m_pOwner = nullptr;
		ID3DXMesh* m_pMesh = nullptr;
		std::vector<D3DXMATERIAL> m_mtrls;
		std::vector<IDirect3DTexture9*> m_textures;
		std::vector<IDirect3DTexture9*> m_normals;
		std::vector<IDirect3DTexture9*> m_emissives;
		std::vector<IDirect3DTexture9*> m_speculars;
		std::vector<std::wstring> m_textureNames;
		ID3DXEffect* m_pShader = nullptr;
		std::wstring m_lastLoadedMeshPath;

		/* For Equip */
		const D3DXMATRIX * m_pParentBoneMatrix = nullptr;
		D3DXMATRIX m_pParentWorldMatrix;
		//char m_boneName[256]; // юс╫ц

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static Equipment* Create(Scene * scene, GameObject* owner,std::wstring xFilePath, std::wstring boneName, std::wstring name);
	};
}

