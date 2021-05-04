#pragma once
#include "Camera.h"

using namespace HyEngine;

class ZoomInCamera final : public Camera
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	ZoomInCamera(Scene* pScene, GameObject* pTarget, std::wstring name);
	virtual ~ZoomInCamera();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize() override;
	virtual void Update() override;

	
	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	D3DXVECTOR3 m_offset = D3DXVECTOR3(0, 0, 0);
	GameObject* m_pTarget = nullptr;
	D3DXVECTOR3 m_at = D3DXVECTOR3(0, 0, 0);


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static ZoomInCamera* Create(Scene* pScene, GameObject* pTarget, std::wstring name);

};

