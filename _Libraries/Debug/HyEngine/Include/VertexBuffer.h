#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	template <typename T>
	void Create(const std::vector<T>& vertices, const DWORD usage = D3DUSAGE_DYNAMIC)
	{
		count = vertices.size();
		ENGINE->CreateVertexBuffer
		(

		)
	}

private :
	IDirect3DVertexBuffer9 * buffer = nullptr;
	UINT count;
};

