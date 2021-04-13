#pragma once
#include "Camera.h"

using namespace HyEngine;


class ENGINE_DLL DynamicCamera : public Camera
{
public :
	DynamicCamera(Scene* scene, GameObject* parent, wstring name);
	virtual ~DynamicCamera();

public :
	static DynamicCamera * Create(Scene* scene, GameObject* parent, wstring name)
	{
		DynamicCamera * camera = new DynamicCamera(scene, parent, name);
		camera->Initialize();
		return camera;
	}
public:
	virtual void Initialize() override;
	virtual void Update() override;

private :
	D3DXVECTOR3 lastClickedPos;
	D3DXVECTOR3 lastClickedRot;
	float m_speed = 10;
	float m_xRotMax = 70;
	float m_yRotMax = 70;
};

