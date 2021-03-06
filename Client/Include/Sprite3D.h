#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class TextureQuad;
}
using namespace HyEngine;

class Sprite3D : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Sprite3D(Scene* pScene, std::wstring name, std::wstring spritePath, ELoopType loopType, float frameCount, float speed = 1.0f);
	virtual ~Sprite3D();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize();
	virtual void Render() override;
	virtual void Update() override;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	void PlayAnimation();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
protected : /* For Render */
	ID3DXEffect* m_pEffect = nullptr;
	TextureQuad * m_pTextureQuad = nullptr;
	IDirect3DTexture9 * m_pTexture = nullptr;

private : /* For Frame */
	float m_curFrame = 0.0f;
	float m_endFrame = 0.0f;
	float m_frameSpeed = 1.0f;

	ELoopType m_loopType;

	std::wstring m_path;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static Sprite3D * Create(Scene * pScene, std::wstring name, std::wstring spritePath, ELoopType loopType, float frameCount, float speed = 1.0f);

};

