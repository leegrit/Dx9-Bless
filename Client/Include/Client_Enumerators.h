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
	PutInWeapon,
	MountOnHorse,

};
enum class EEquipSlot
{
	Helmet,
	Upper,
	Belt,
	Glove,
	Weapon,
	Shoulder,
	Lower,
	Boots,
	MAX
};
enum class EQuestState
{
	NotOpen, // 오픈 조건 충족안됨.
	Open, // 오픈은 되었으나 수락 안함
	Accepted, // 수락된 상태
	Clear, // 클리어
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
	Item, // 소모품
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

enum class ENotifyType
{
	// 재사용 대기시간 중에는 사용할 수 없습니다.
	InvalidCoolTime, //CoolTimeNotify,
	// 올바른 대상을 선택하십시오.
	InvalidTarget,//CorrectTargetNotify,
	// 아이템을 획득하였습니다.
	GetItemNotify,
	// 아이템을 구매하였습니다.
	BuyItemNotify,
};

enum class ESkill
{

};