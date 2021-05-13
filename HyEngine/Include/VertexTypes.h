#pragma once

namespace HyEngine
{

	class ENGINE_DLL SimpleVertex
	{
	public:
		SimpleVertex() {}

		SimpleVertex(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

		float x, y, z;

		static const DWORD FVF;
	};

	class ENGINE_DLL ColorVertex
	{
	public:
		ColorVertex() {}

		ColorVertex(float x, float y, float z, D3DCOLOR c)
			: x(x), y(y), z(z), color(c)
		{

		}

		float x, y, z;
		D3DXCOLOR color;

		static const DWORD FVF;
	};

	class ENGINE_DLL VertexNormal
	{
	public:
		VertexNormal() {}

		VertexNormal(float x, float y, float z, float nx, float ny, float nz)
			: x(x), y(y), z(z), nx(nx), ny(ny), nz(nz)
		{}

		float x, y, z;
		float nx, ny, nz;

		static const DWORD FVF;
	};

	class ENGINE_DLL TextureVertex
	{
	public:
		TextureVertex() {}

		TextureVertex(
			float x, float y, float z,
			float u, float v)
			: x(x), y(y), z(z),
			u(u), v(v)
		{}

		float x, y, z;
		float u, v;

		static const DWORD FVF;
	};

	class ENGINE_DLL VTXSCREEN
	{
	public:
		D3DXVECTOR4 position;
		D3DXVECTOR2 uv;
		static const DWORD FVF;
	};

	class ENGINE_DLL ModelVertex
	{
	public:
		ModelVertex() {}

		ModelVertex(
			float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v)
			: x(x), y(y), z(z),
			nx(nx), ny(ny), nz(nz),
			u(u), v(v)
		{}

		float x, y, z;
		float nx, ny, nz;
		float u, v;

		static const DWORD FVF;
	};
	class ENGINE_DLL BumpModelVertex
	{
	public:

		float x, y, z;
		float u, v;
		float normalX, normalY, normalZ;
		float tangentX, tangentY, tangentZ;
		float binormalX, binormalY, binormalZ;
	};

	class ENGINE_DLL TextureCubeVertex
	{
	public:
		TextureCubeVertex() {}

		TextureCubeVertex(
			float x1, float y1, float z1,
			float x2, float y2, float z2)
			: x1(x1), y1(y1), z1(z1),
			x2(x2), y2(y2), z2(z2)
		{}

		float x1, y1, z1;
		float x2, y2, z2;

		static const DWORD FVF;
	};
}