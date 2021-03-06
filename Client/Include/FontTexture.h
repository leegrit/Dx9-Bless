#pragma once
#include "Billboard.h"

using namespace HyEngine;
class FontTexture : public Billboard
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected: 
	explicit FontTexture(Scene * pScene, std::wstring name, std::wstring fontTexturePath,
		GameObject* pOwner, D3DXVECTOR3 offset);
	virtual ~FontTexture();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize() override;
	virtual void Render() override;
	virtual void Update() override;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void SetColor(D3DXCOLOR color, float intensity);
	void SetOffset(D3DXVECTOR3 offset);

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private: /* For Render */
	IDirect3DTexture9* m_pFontTexture = nullptr;

private: /* For Position */
	GameObject * m_pOwner = nullptr;
	D3DXVECTOR3 m_offset;

private: /* For Color */
	D3DXCOLOR m_color;
	float m_colorIntensity;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static FontTexture * Create(Scene* pScene, std::wstring name, std::wstring fontTexturePath,
		GameObject* pOwner, D3DXVECTOR3 offset);

};

