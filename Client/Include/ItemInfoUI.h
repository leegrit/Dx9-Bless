#pragma once
#include "GameObject.h"
#include "ItemInfo.h"

using namespace HyEngine;

class ItemInfoUI : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit ItemInfoUI(Scene* pScene, std::wstring name);
	virtual ~ItemInfoUI();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize();
	virtual void Update() override;
	virtual void Render() override;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Show(D3DXVECTOR3 itemSlotPosition, ItemInfo itemInfo,  bool bInventory = true);
	void ShowForShop(D3DXVECTOR3 position, ItemInfo itemInfo);
	void Hide();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Render */
	UIPanel* m_pBackground = nullptr;
	D3DXVECTOR3 m_backGroundOriginPos;
	UIPanel* m_pCoinIcon = nullptr;
	D3DXVECTOR3 m_coinIconOriginPos;

private :
	D3DXVECTOR3 m_itemSlotPosition;
	const D3DXVECTOR3 m_posOffset = D3DXVECTOR3(-151, -122, 0);
	const D3DXVECTOR3 m_equipUIOffset = D3DXVECTOR3(151, -122, 0);
	bool m_bShow = false;

private : /* For Font */
	const D3DXVECTOR3 m_titleOriginPos = D3DXVECTOR3(413, 263, 0);
	const D3DXVECTOR3 m_typeOriginPos = D3DXVECTOR3(413, 319, 0);
	const D3DXVECTOR3 m_effectOriginPos = D3DXVECTOR3(413, 364, 0); // 효과 또는 설명
	const D3DXVECTOR3 m_saleOriginPos = D3DXVECTOR3(413, 427, 0); // 판매 가능한지 여부 텍스트 위치
	const D3DXVECTOR3 m_dstrOriginPos = D3DXVECTOR3(413, 453, 0); // 파괴 가능한지 여부 텍스트 위치
	const D3DXVECTOR3 m_priceOriginPos = D3DXVECTOR3(568, 484, 0);

	D3DXVECTOR3 m_titlePosition;
	D3DXVECTOR3 m_typePosition;
	D3DXVECTOR3 m_effectPosition;
	D3DXVECTOR3 m_salePosition;
	D3DXVECTOR3 m_dstrPosition;
	D3DXVECTOR3 m_pricePosition;

private :
	ItemInfo m_showItemInfo;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static ItemInfoUI * Create(Scene * pScene, std::wstring name);
};

