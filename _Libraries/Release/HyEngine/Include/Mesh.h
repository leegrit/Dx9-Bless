#pragma once
namespace HyEngine
{
	class ENGINE_DLL Mesh
	{

	public :
		Mesh();
		virtual ~Mesh();

	public :
		void Load(std::string filePath) ;
		IDirect3DVertexBuffer9* GetVertexBuffer();
		int GetVertexSize();
		int GetVertexCount();
		IDirect3DIndexBuffer9* GetIndexBuffer();
		int GetPrimitiveCount();
		IDirect3DVertexDeclaration9* GetDeclare();

		float GetRadius();
	protected :
		int m_primCount;
		// vertex
		int m_vertexSize;
		int m_vertexCount;
		int m_indexCount;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;

		IDirect3DIndexBuffer9 * m_pIndexBuffer = nullptr;

		IDirect3DVertexDeclaration9* m_pDeclare = nullptr;

		// 
		float m_radius;

	};
}