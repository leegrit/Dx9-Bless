#pragma once

namespace HyEngine
{
	class Font;
}

class NameFont
{
public :
	NameFont() = default;
	~NameFont() = default;

	void Initialize(std::wstring text, GameObject* pOwner, D3DXVECTOR2 size,  D3DXVECTOR3 offset, float centerOffset ,D3DXCOLOR color);
	void RenderFont();

	void SetOffset(D3DXVECTOR3 offset);
	void SetCenterOffset(float centerOffset);
	
	void SetColor(D3DXCOLOR color);
private :
	/* For Font */
	std::wstring m_text;
	Font* m_pFont = nullptr;

	/* For Offset */
	GameObject* m_pOwner;
	D3DXVECTOR3 m_offset;
	D3DXVECTOR2 m_size;
	D3DXCOLOR m_color;
	float m_centerOffset;
};

