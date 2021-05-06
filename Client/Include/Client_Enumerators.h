#pragma once

enum class EPlayerState
{
	Idle,
	Attack,
	Hit,
	Die,
	Move,
	Jump,
	OtherAction, 
	OtherEvent,
};

enum class EQuestState
{
	NotOpen, // ���� ���� �����ȵ�.
	Open, // ������ �Ǿ����� ���� ����
	Accepted, // ������ ����
	Clear, // Ŭ����
};

enum class EQuestImportance
{
	Main,
	Sub,
};
enum class EQuestType
{
	Combat,

};

enum class EQuestDialogType
{
	AcceptDialog,
	FinishDialog,
};

enum class EItemType
{
	None,
	Upper,
	Lower,
	Boots,
	Glove,
	Helmet,
	Shoulder,
	Belt,
	CollectItem,
	Weapon,
	Item, // �Ҹ�ǰ
	QuestItem,
	Spoils,
};

enum class EItemSaleType
{
	SalePossible,
	SaleImpossible,
};

enum class EItemDestructionType
{
	Destrucalbe,
	InDestrucalbe
};

