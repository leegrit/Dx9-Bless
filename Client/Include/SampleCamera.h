#pragma once
#include "Camera.h"

using namespace HyEngine;


class SampleCamera : public Camera
{
public :
	SampleCamera(Scene* scene, GameObject* parent, wstring name);
	virtual ~SampleCamera();

public :
	static SampleCamera * Create(Scene* scene, GameObject* parent, wstring name)
	{
		SampleCamera * camera = new SampleCamera(scene, parent, name);
		camera->Initialize();
		return camera;
	}
public:
	virtual void Initialize() override;
	virtual void Update() override;
};

