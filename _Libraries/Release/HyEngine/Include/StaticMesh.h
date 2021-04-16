#pragma once
#include "Mesh.h"

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
		virtual void DrawPrimitive() override;
		virtual void UpdatedData(EDataType dataType) override;
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);

		//////////////////////////////////////////////////////////////////////////
		// FOR EDITOR
		//////////////////////////////////////////////////////////////////////////
	public :
		ID3DXMesh* GetMesh() const;
		bool CalcBounds(_Out_ D3DXVECTOR3* center, _Out_ float * radius);


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
		std::vector<std::wstring> m_textureNames;

		std::wstring m_lastLoadedMeshPath;



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

