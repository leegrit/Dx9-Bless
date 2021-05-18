#pragma once
#include "Client_Enumerators.h"

enum class EItemBuffType
{
	HPHeal,
	MPHeal,
	PowerUp,
	SpeedUp,
	DefenceUp,
	CoolTimeReset,
};


class ItemInfo
{
public :
	ItemInfo();

	int uid;
	std::wstring imagePath;
	std::wstring itemName;
	EItemType itemType;
	EItemBuffType buffType;
	std::wstring typeText;
	std::wstring effectText;
	// ��������
	int wearableLevel;
	int atk;
	int physicalDef;
	int magicalDef;
	int salePrice;
	// �Ҹ�ǰ ȿ�� ��
	int itemValue;
	// �Ҹ�ǰ ���ӽð�
	int itemDuration;
	// �Ҹ�ǰ ȿ���� ���� ����
	std::wstring itemDescription; 

	float coolTime;
	float curCoolTime;

	bool availableForSale;
	bool availableForDestruction;

public :
	// �Ҹ�ǰ, �⵿��ϰ��� ��� ��ø ����
	void AddItem(ItemInfo itemInfo);
	ItemInfo GetItem(int index);
	int GetOverlapCount();

private:
	int m_itemCount = 1;
public:
	std::vector<ItemInfo> m_overlapItems;

};

