#pragma once
#include "Mesh.h"

#define MAX_SUBSET_COUNT 16

namespace HyEngine
{
	class HierarchyData;
	class StaticMesh : public Mesh
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit StaticMesh(Scene * scene, GameObject* parent, int editID);
		explicit StaticMesh(Scene* scene, GameObject* parent, std::wstring name);
		virtual ~StaticMesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public:
		virtual void Initialize();
		virtual void Initialize(shared_ptr<HierarchyData> data);
		virtual void Render() override;
		virtual void DrawPrimitive(ID3DXEffect* pShader) override;
		virtual void UpdatedData(EDataType dataType) override;
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);

		//////////////////////////////////////////////////////////////////////////
		// FOR EDITOR
		//////////////////////////////////////////////////////////////////////////
	public :
		ID3DXMesh* GetMesh() const;
		bool CalcBounds(_Out_ D3DXVECTOR3* center, _Out_ float * radius);

		/////////////////////////////////////////////////////aawwawaawwwwaaw/////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		std::wstring GetMeshPath() const;

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		ID3DXMesh* m_pMesh = nullptr;
		std::vector<D3DXMATERIAL> m_mtrls;
		std::vector<IDirect3DTexture9*> m_textures;
		std::vector<IDirect3DTexture9*> m_normals;
		std::vector<IDirect3DTexture9*> m_emissives;
		std::vector<IDirect3DTexture9*> m_speculars;
		std::vector<IDirect3DTexture9*> m_diffuseMasks; // green ���
		std::vector<std::wstring> m_textureNames;
		std::vector<ID3DXEffect*> m_effects;
		ID3DXEffect* m_pShader = nullptr;
		std::wstring m_lastLoadedMeshPath;

		/* Handles */
		D3DXHANDLE m_albedoHandle;
		D3DXHANDLE m_normalHandle;
		D3DXHANDLE m_emissiveHandle;
		D3DXHANDLE m_specularHandle;
		D3DXHANDLE m_specularMaskHandle;
		D3DXHANDLE m_diffuseMaskHandle;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static StaticMesh* Create(Scene* scene, GameObject* parent, int editID)
		{
			StaticMesh * mesh = new StaticMesh(scene, parent, editID);
			mesh->Initialize();
			return mesh;
		}
		static StaticMesh* Create(Scene* scene, GameObject * parent, std::wstring name, shared_ptr<HierarchyData>data)
		{
			StaticMesh* mesh = new StaticMesh(scene, parent, name);
			mesh->Initialize(data);
			return mesh;
		}
	};
}

