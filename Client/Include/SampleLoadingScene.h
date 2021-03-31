#pragma once
#include "LoadingScene.h"

using namespace HyEngine;

class SampleLoadingScene : public LoadingScene
{
public:
	SampleLoadingScene();
	virtual ~SampleLoadingScene();
public:
	// Inherited via Scene
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;

	virtual void LateLoadScene() override;

private:
};

