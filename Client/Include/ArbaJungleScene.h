#pragma once
#include "GameScene.h"

class ArbaJungleScene : public GameScene
{
	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Update() override;
	virtual void Load() override;
	virtual void LateLoadScene() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;
	virtual void RenderGUI() override;
	virtual Camera * GetEditCam() override;
	virtual Camera * GetGameCam() override;


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:


private:
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;

	class Player* m_pPlayer = nullptr;
};

