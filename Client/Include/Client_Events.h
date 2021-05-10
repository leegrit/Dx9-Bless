#pragma once
#include "stdafx.h"

namespace QuestEvent
{
	static std::string QuestDialogOpen = "QuestEvent.QuestDialogOpen";
	static std::string QuestDialogEnd = "QuestEvent.QuestDialogEnd";
	static std::string QuestAccept = "QuestEvent.QuestAccept";
	static std::string QuestFinish = "QuestEvent.QuestFinish";
	static std::string QuestCompletelyClear = "QuestEvent.QuestCompletelyClear";
	static std::string CollectQuestObject = "QuestEvent.CollectQuestObject";
}

namespace BattleEvent
{
	static std::string CharacterDie = "BattleEvent.CharacterDie";
	static std::string CharacterDamaged = "BattleEvent.CharacterDamaged";

}

namespace UIEvent
{
	static std::string ShopUIOpen = "UIEvent.ShopUIOpen";
	static std::string ShopUIClose = "UIEvent.ShopUIClose";
	static std::string InventoryUIOpen = "UIEvent.InventoryUIOpen";
	static std::string InventoryUIClose = "UIEvent.InventoryClose";
	static std::string EquipmentUIOpen = "UIEvent.EquipmentUIOpen";
	static std::string EquipmentUIClose = "UIEvent.EquipmentUIClose";
}

namespace PlayerEvent
{
	static std::string BeginCollect = "PlayerEvent.BeginCollect";
	static std::string EndCollect = "PlayerEvent.EndCollect";
}

namespace GameEvent
{
	static std::string LevelUp = "GameEvent.LevelUp";
	static std::string SendExp = "GameEvent.SendExp";
	// �κ��丮�� ������ �߰�
	static std::string AddItemToInventory = "GameEvent.AddItemToInventory";
	// �κ��丮�� ������ ����
	static std::string RemoveItemToInventory = "GameEvent.RemoveItemToInventory";

	// ��� ����
	static std::string WearItem = "GameEvent.WearItem";
	// ��� ����
	static std::string WearOffItem = "GameEvent.WearOffItem";
	static std::string DrinkItem = "GameEvent.DrinkItem";

	// ��� ��ü
	static std::string EquipmentChange = "GameEvent.EquipmentChange";

	// ������ ����
	static std::string NotEnoughMoney = "GameEvent.NotEnoughMoney";

	static std::string InventoryFull = "GameEvent.InventoryFull";

	static std::string BuyItem = "GameEvent.BuyItem";

	static std::string InvalidCoolTime = "GameEvent.InvalidCoolTime";
	static std::string InvalidTarget = "GameEvent.InvalidTarget";
}

