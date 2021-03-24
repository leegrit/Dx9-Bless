#pragma once


namespace HyEngine
{
	class ENGINE_DLL Geometry abstract
	{
	public :
		Geometry() {}
		~Geometry() {};
	public:
		template <typename T>
		static T* CreateGeometry(void* arg)
		{
			/*for (auto& geo : geometries)
			{
				T * result = static_cast<T*>(geo);
				if (result != nullptr)
					return result;
			}*/
			T* geometry = new T();
			geometry->Initialize(arg);
			geometry->CreateVertex();
			geometry->CreateIndex();
			//geometries.push_back(geometry);
			return geometry;
		}

	protected:
		virtual void Initialize(void* arg) = 0;
		virtual void CreateVertex() = 0;
		virtual void CreateIndex() = 0;
	public:
		IDirect3DVertexBuffer9* GetVertexBuffer();
		int GetVertexSize();
		int GetVertexCount();
		IDirect3DVertexDeclaration9* GetDeclare();
		DWORD GetFVF();
		IDirect3DIndexBuffer9* GetIndexBuffer();
		int GetPrimitiveCount();

	protected:
		// vertex
		int m_vertexSize;
		int m_vertexCount;
		DWORD m_vertexFVF;
		IDirect3DVertexDeclaration9* m_pDeclare;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;

		// index
		int m_indexSize;
		int m_indexCount;
		int m_indexFMT;
		IDirect3DIndexBuffer9* m_pIndexBuffer = nullptr;

		int m_primitiveCount;

	private:
		//static std::vector<Geometry*> geometries;
	};

}