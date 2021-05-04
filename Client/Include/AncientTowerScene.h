#pragma once
#include "GameScene.h"

namespace HyEngine
{
	class Pawn;
	class Equipment;
}

using namespace HyEngine;

class AncientTowerScene : public GameScene
{
	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Update() override;
	virtual void Load() override;
	virtual void LateLoadScene() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;
	virtual void RenderGUI() override;
	virtual Camera * GetEditCam() override;
	virtual Camera * GetGameCam() override;



private :
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;


	Equipment * m_pEquip;


	std::vector<class NonePlayer*> m_nonePlayers;


};

