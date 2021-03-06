#pragma once
#include "GameObject.h"
#include "ItemInfo.h"



using namespace HyEngine;
class SpoilsUI : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit SpoilsUI(Scene* pScene, std::wstring name);
	virtual ~SpoilsUI();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize();
	virtual void Update() override;
	virtual void Render() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	void Show(ItemInfo itemInfo);
	void Hide();
	bool IsShow();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	UIPanel* m_pBackground = nullptr;
	UIPanel* m_pItemSlotBack = nullptr;
	UIPanel* m_pItemSlotIcon = nullptr;
	UIPanel * m_pGainBtn = nullptr;
	UIPanel* m_pCancleBtn = nullptr;

	std::wstring m_gainFont = L"ȹ??(F)";
	std::wstring m_itemName = L"";

private :
	bool m_bShow = false;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static SpoilsUI* Create(Scene* pSceme, std::wstring name);

};

