//#pragma once
//
//
//namespace HyEngine
//{
//	class ObjData
//	{
//	public:
//		void Load(std::string filePath);
//
//		D3DXVECTOR3 GetPosition(int index) const;
//		D3DXVECTOR3 GetTexcoord(int index) const;
//		D3DXVECTOR3 GetNormal(int index) const;
//		UINT GetIndices(int index) const;
//	
//		inline int GetPrimCount() const { return m_primCount; }
//		inline int GetVertexCount() const { return m_vertexCount; }
//		inline int GetIndexCount() const { return m_indexCount; }
//	private : 
//		bool m_bLoaded = false;
//		int m_primCount;
//		int m_vertexCount;
//		int m_indexCount;
//
//		class OBJL::Loader* m_pLoader;
//	};
//
//}