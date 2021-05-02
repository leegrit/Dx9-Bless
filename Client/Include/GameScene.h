#pragma once
#include "Scene.h"

using namespace HyEngine;


class GameManager;
class UIManager;
class QuestManager;
class NPCInteractManager;
class GameScene : public Scene
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
	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
	virtual Camera* GetEditCam() PURE;
	virtual Camera* GetGameCam() PURE;


	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public:
	void OnModeChanged(void*);

	//////////////////////////////////////////////////////////////////////////
	// GETTER FOR MANAGER
	//////////////////////////////////////////////////////////////////////////
public:
	GameManager* GetGameManager();
	UIManager* GetUIManager();
	QuestManager* GetQuestManager();
	NPCInteractManager* GetNPCInteractManager();

private:
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;

private : /* For Manager */
	GameManager* m_pGameManager = nullptr;
	UIManager * m_pUIManager = nullptr;
	QuestManager* m_pQuestManager = nullptr;
	NPCInteractManager* m_pNPCInteractManager = nullptr;

};

