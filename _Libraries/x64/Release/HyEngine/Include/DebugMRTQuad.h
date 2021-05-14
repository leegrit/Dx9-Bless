#pragma once
namespace HyEngine
{
	class DebugMRTQuad
	{
	public :
		DebugMRTQuad(float xPos, float yPos, float xSize, float ySize);
		~DebugMRTQuad();

		IDirect3DVertexBuffer9* _vb;
		IDirect3DIndexBuffer9* _ib;

		int numVertex = 4;
		int vertexSize;
		int primNum = 2;
	};
}

