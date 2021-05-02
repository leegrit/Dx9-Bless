#pragma once
#include "stdafx.h"

namespace QuestEvent
{
	static std::string QuestDialogOpen = "QuestEvent.QuestDialogOpen";
	static std::string QuestDialogEnd = "QuestEvent.QuestDialogEnd";
	static std::string QuestAccept = "QuestEvent.QuestAccept";
	static std::string QuestFinish = "QuestEvent.QuestFinish";
	static std::string QuestCompletelyClear = "QuestEvent.QuestCompletelyClear";
}

namespace BattleEvent
{
	static std::string CharacterDie = "BattleEvent.CharacterDie";
}

namespace GameEvent
{
	static std::string LevelUp = "GameEvent.LevelUp";
}
