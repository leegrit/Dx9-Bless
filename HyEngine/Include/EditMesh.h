#pragma once
#include "EditObject.h"

namespace Editor
{
	class EditMesh : public EditObject
	{
	protected :
		explicit EditMesh(Scene* scene, GameObject* parent, int editID);
		virtual ~EditMesh();
	public :
		virtual void Initialize();
		virtual void Render() override;

		static EditMesh* Create(Scene* scene, GameObject* parent, int editID)
		{
			//assert(false);
			EditMesh* mesh = new EditMesh(scene, parent, editID);
			//assert(false);
			mesh->Initialize();
			return mesh;
		}
	public :
		//// TODO 예외처리
		//void SetMesh(const std::wstring& path);
		//void SetDiffuse(const std::wstring& path);
		//void SetBumb(const std::wstring& path);
		//void SetEmission(const std::wstring& path);

		ID3DXMesh* GetDxMesh()const;
	private :
		std::shared_ptr<IDirect3DTexture9> m_pBaseTex = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pBumpTex = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pEmission = nullptr;
		std::shared_ptr<Mesh> m_pMesh = nullptr;

		// for xfile format
		ID3DXMesh* m_pDxMesh = nullptr;
		std::vector<D3DMATERIAL9> m_mtrls;
		std::vector<IDirect3DTexture9*> m_textures;

		std::wstring m_lastLoadedMeshPath;


		// Inherited via EditObject
		virtual void UpdatedData(EDataType dataType) override;
		class Collider* m_pCollider = nullptr;
	};

}

