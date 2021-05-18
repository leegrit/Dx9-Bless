#pragma once
#include "Scene.h"

using namespace HyEngine;

enum class EObjectGroup
{
	PlayerGroup,
	EnemyGroup,

};

class GameManager;
class UIManager;
class QuestManager;
class NPCInteractManager;
class BattleManager;
class InteractManager;
class EffectManager;
class CinematicManager;
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
	// GETTER FOR SCRIPTABLE DATA
	//////////////////////////////////////////////////////////////////////////
public :
	class PlayerInfo* GetPlayerInfo();
	class ExpTable * GetExpTable();
	class PlayerMoneyData * GetPlayerMoneyData();
	class InventoryData* GetInventoryData();
	class PlayerEquipData* GetPlayerEquipData();
	class PlayerStatusData* GetPlayerStatusData();
	
	//////////////////////////////////////////////////////////////////////////
	// GETTER
	//////////////////////////////////////////////////////////////////////////
public:
	std::vector<GameObject*> GetObjectGroup(EObjectGroup objectGroup);



	//////////////////////////////////////////////////////////////////////////
	// GETTER FOR MANAGER
	//////////////////////////////////////////////////////////////////////////
public:
	GameManager* GetGameManager();
	UIManager* GetUIManager();
	QuestManager* GetQuestManager();
	NPCInteractManager* GetNPCInteractManager();
	BattleManager* GetBattleManager();
	InteractManager* GetInteractManager();
	EffectManager* GetEffectManager();
	CinematicManager * GetCinematicManager();

	/* TEMP */
public :
	float GetFloatA();
	float GetFloatB();
	float GetFloatC();
	float GetFloatD();
	float GetFloatE();
	float GetFloatF();
	char* GetText();

	float m_floatA;
	float m_floatB;
	float m_floatC;
	float m_floatD;
	float m_floatE;
	float m_floatF;
	char m_text[256];

private:
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;

private : /* For Object Group */	
	std::unordered_map<EObjectGroup, std::vector<GameObject*>> m_objectGroups;

private : /* For ScriptableData */
	class PlayerInfo * m_pPlayerInfo = nullptr;
	class ExpTable * m_pExpTable = nullptr;
	class PlayerMoneyData * m_pPlayerMoneyData = nullptr;
	class InventoryData* m_pInventoryData = nullptr;
	class PlayerEquipData* m_pPlayerEquipData = nullptr;
	class PlayerStatusData* m_pPlayerStatusData = nullptr;

private : /* For Manager */
	GameManager* m_pGameManager = nullptr;
	UIManager * m_pUIManager = nullptr;
	QuestManager* m_pQuestManager = nullptr;
	NPCInteractManager* m_pNPCInteractManager = nullptr;
	BattleManager* m_pBattleManager = nullptr;
	InteractManager* m_pInteractManager = nullptr;
	EffectManager* m_pEffectManager = nullptr;
	CinematicManager * m_pCinematicManager = nullptr;
};

