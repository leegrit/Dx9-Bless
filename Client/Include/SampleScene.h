#pragma once
#include "Scene.h"

namespace HyEngine
{
	class Pawn;
}

using namespace HyEngine;
class SampleScene : public Scene
{


	// Inherited via Scene
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;
	virtual void RenderGUI() override;

public :

private :
	// test
	Pawn* m_pPawn;
};

