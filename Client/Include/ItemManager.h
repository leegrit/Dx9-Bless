#pragma once
#include "ItemInfo.h"


class ItemManager
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	ItemManager(class GameScene* pScene);
	~ItemManager();

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK 
	//////////////////////////////////////////////////////////////////////////
public :
	void OnUseSkillBook(void* pItemInfo);


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize();
	void Update();

	void UseItem(ItemInfo info);

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : 
	class GameScene* pScene = nullptr;

private : /* For Item */
	class InventoryData* m_pInventoryData = nullptr;
	class QuickSlotData * m_pQuickSlotData = nullptr;
	class PlayerSkillInfo * m_pPlayerSkillInfo = nullptr;
};

