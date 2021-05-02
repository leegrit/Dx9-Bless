#pragma once
#include "LoadingScene.h"

using namespace HyEngine;

class BlessLoadingScene : public LoadingScene
{
public :
	BlessLoadingScene();
	virtual ~BlessLoadingScene();

public :
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;

	virtual void LateLoadScene() override;

};

