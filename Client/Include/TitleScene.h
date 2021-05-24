#pragma once
#include "Scene.h"

using namespace HyEngine;

class TitleScene : public Scene
{
	//////////////////////////////////////////////////////////////////////////
	// INHIERTED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;
	virtual void RenderGUI() override;

private :
	class Sprite *m_pLogo = nullptr;

};

