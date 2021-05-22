#pragma once
#include "Camera.h"

using namespace HyEngine;
class StaticCamera : public Camera
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private: 
	StaticCamera(Scene* pScene, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	virtual ~StaticCamera();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize() override;
	virtual void Update() override;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private: 


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static StaticCamera* Create(Scene* pScene, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};

