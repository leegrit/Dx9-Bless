#pragma once
#include "Client_Enumerators.h"
class ItemInfo
{
public :
	ItemInfo();

	int uid;
	std::wstring imagePath;
	std::wstring itemName;
	EItemType itemType;
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

	bool availableForSale;
	bool availableForDestruction;
};

