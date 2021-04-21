#pragma once

namespace HyEngine
{
	/* �ӽ� */
	class DeferredQuad
	{
	public:
		DeferredQuad();
		~DeferredQuad();

		IDirect3DVertexBuffer9* _vb;
		IDirect3DIndexBuffer9* _ib;
		IDirect3DVertexDeclaration9* m_pDeclare;

		int numVertex = 4;
		int vertexSize;
		int primNum = 2;

	};

}