#pragma once
#include "RenderGroup.h"

namespace HyEngine
{
	class StaticMesh;
	class StaticMeshGroup : public RenderGroup
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	public :
		explicit StaticMeshGroup(std::wstring meshFilePath);
		virtual ~StaticMeshGroup();

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public:
		/* InitializeBuffer는 모두 등록된 후 호출되어야한다. */
		void InitializeBuffer();
		void Insert(StaticMesh* mesh);
		void Insert(std::vector<StaticMesh*> meshes);

		//////////////////////////////////////////////////////////////////////////
		// FOR RENDER
		//////////////////////////////////////////////////////////////////////////
	public :
		void RenderAll();


		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		/* InstanceMeshes */
		std::vector<StaticMesh*> m_pMeshes;

		/* Buffer */
		IDirect3DVertexBuffer9* m_pOriginVertexBuffer = nullptr;
		IDirect3DIndexBuffer9* m_pOriginIndexBuffer = nullptr;
		IDirect3DVertexBuffer9* m_pVBInstanceBuffer = nullptr;

		IDirect3DVertexDeclaration9* m_pOriginVertexDeclaration = nullptr;
		
		// 같은 종류 메쉬만 등록 가능
		std::wstring m_meshFilePath;
		int m_meshCount;
	};
}

