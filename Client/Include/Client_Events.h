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
	// 인벤토리에 아이템 추가
	static std::string AddItemToInventory = "GameEvent.AddItemToInventory";
	// 인벤토리에 아이템 제거
	static std::string RemoveItemToInventory = "GameEvent.RemoveItemToInventory";

	// 장비 착용
	static std::string WearItem = "GameEvent.WearItem";
	// 장비 해제
	static std::string WearOffItem = "GameEvent.WearOffItem";
	static std::string DrinkItem = "GameEvent.DrinkItem";

	// 장비 교체
	static std::string EquipmentChange = "GameEvent.EquipmentChange";

	static std::string UseItem = "GameEvent.UseItem";

	// Skill
	static std::string UseSkillBook = "GameEvent.UseSkillBook";
	static std::string GainSkill = "GameEvent.GainSkill";

	// 소지금 부족
	static std::string NotEnoughMoney = "GameEvent.NotEnoughMoney";

	static std::string InventoryFull = "GameEvent.InventoryFull";

	static std::string BuyItem = "GameEvent.BuyItem";

	static std::string InvalidCoolTime = "GameEvent.InvalidCoolTime";
	static std::string InvalidTarget = "GameEvent.InvalidTarget";


	/* 전리품 수집 */
	static std::string BeginSpoils = "GameEvent.BeginSpoils";
	static std::string EndSpoils = "GameEvent.EndSpoils";

	/* Quick Slot */
	static std::string SetQuickSlot = "GameEvent.SetQuickSlot";
	static std::string RemoveQuickSlot = "GameEvent.RemoveQuickSlot";

	/* Buff */
	static std::string BeginLastingBuff = "GameEvent.BeginLastingBuff";
	static std::string EndLastingBuff = "GameEvent.EndLastingBuff";

	/* Cinematic */
	static std::string BeginCinematic = "GameEvent.BeginCinematic";
	static std::string EndCinematic = "GameEvent.EndCinematic";
}

