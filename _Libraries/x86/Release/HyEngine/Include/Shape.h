#pragma once

namespace HyEngine
{
	class Shape abstract
	{
	private :
		Shape() {}
		virtual ~Shape() {}

	public :


	protected :
		virtual void Initialize(void* arg) = 0;
		virtual void CreateVertex() = 0;
		virtual void CreateIndex() = 0;

	public:
		IDirect3DVertexBuffer9* GetVertexBuffer();
		int GetVertexSize();
		int GetVertexCount();
		DWORD GetFVF();
		IDirect3DIndexBuffer9* GetIndexBuffer();
		int GetPrimitiveCount();

	protected:
		// vertex
		int m_vertexSize;
		int m_vertexCount;
		DWORD m_vertexFVF;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;

		// index
		int m_indexSize;
		int m_indexCount;
		int m_indexFMT;
		IDirect3DIndexBuffer9* m_pIndexBuffer = nullptr;

		int m_primitiveCount;

	private:
		static std::vector<Shape*> geometries;
	};
}

