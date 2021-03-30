#pragma once
#include "Scene.h"

using namespace HyEngine;
class SampleScene : public Scene
{


	// Inherited via Scene
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;

public :

};

