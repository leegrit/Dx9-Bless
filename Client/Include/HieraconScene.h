#pragma once
#include "GameScene.h"

namespace HyEngine
{
	class Pawn;
	class Equipment;
}

using namespace HyEngine;
class HieraconScene : public GameScene
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




	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :


private :
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;

	// test
	class Player* m_pPlayer;

	Equipment * m_pEquip;

	std::vector<class NonePlayer*> m_nonePlayers;

public:
	/* 임시 무기 위치 찾기 위해 사용 */
	static char temp[256];




	//////////////////////////////////////////////////////////////////////////
	// TEST
	//////////////////////////////////////////////////////////////////////////
private :
	int fontPosX = 0;
	int fontPosY = 0;
	int fontPosZ = 0;
	int fontScaleX = 0;
	int fontScaleY = 0;

};

