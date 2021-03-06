#pragma once
#include "GameManager.h"
#include "ItemInfo.h"

namespace HyEngine
{
	class Button;
}

class ShopUI : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit ShopUI(Scene* pScene, std::wstring name);
	virtual ~ShopUI();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize();
	virtual void Update() override;
	virtual void Render() override;

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual std::wstring GetShopTitle() PURE;
	virtual std::vector<ItemInfo> GetItemInfos()PURE;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	void Show();
	void Hide();
	bool IsShow();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Render */
	UIPanel* m_pBackground = nullptr;
	Button * m_pCloseButton = nullptr;
	std::vector<Button*> m_itemSlots;
	std::vector<UIPanel* >m_itemSlotBacks;
	std::vector<UIPanel*> m_itemSlotPrices;

	std::vector<ItemInfo> m_items; 
	std::vector<UIPanel*> m_itemIcons; // 실제 아이템 아이콘

	UIPanel * m_pCenterLine = nullptr;
	UIPanel* m_pUnderLine = nullptr;
	UIPanel * m_pUnderPanel = nullptr;
	UIPanel * m_pCoinIcon = nullptr;

	UIPanel* m_pItemSelectPanel = nullptr;
	class ItemInfoUI* m_pItemInfoUI = nullptr;

	bool m_bShow = false;
private : /* For Slot */
	const int m_slotOffset = 63;
};

