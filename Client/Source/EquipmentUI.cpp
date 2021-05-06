#include "stdafx.h"
#include "EquipmentUI.h"
#include "Button.h"
#include "PathManager.h"
#include "ItemInfoUI.h"

EquipmentUI::EquipmentUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

EquipmentUI::~EquipmentUI()
{
}

void EquipmentUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUISkillTree_I47_1.png",
		D3DXVECTOR3(-237, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(460, 494, 1),
		L"EquipmentUI_Background");

	m_pCloseButton = Button::Create(GetScene(), L"EquipmentUI_CloseButton",
		PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png",
		D3DXVECTOR3(-43, 224, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(20, 20, 1));

	m_equipSlots.reserve((int)EEquipSlot::MAX);
	m_equipSlots.resize((int)EEquipSlot::MAX);

	/* Left */
	m_equipSlots[(int)EEquipSlot::Helmet] = Button::Create(GetScene(),
		L"EquipSlot_Helmet",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_5.png",
		D3DXVECTOR3(-403, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Helmet]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]() 
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Helmet]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Helmet]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Helmet]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Upper] = Button::Create(GetScene(),
		L"EquipSlot_Upper",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_17.png",
		D3DXVECTOR3(-403, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Upper]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Upper]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Upper]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Upper]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Belt] = Button::Create(GetScene(),
		L"EquipSlot_Belt",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_8.png",
		D3DXVECTOR3(-403, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Belt]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Belt]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Belt]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Belt]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Glove] = Button::Create(GetScene(),
		L"EquipSlot_Glove",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_9.png",
		D3DXVECTOR3(-403, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Glove]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Glove]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Glove]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Glove]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});


	/* Right */
	m_equipSlots[(int)EEquipSlot::Weapon] = Button::Create(GetScene(),
		L"EquipSlot_Weapon",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_10.png",
		D3DXVECTOR3(-69, 143 , 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Weapon]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Weapon]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Weapon]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Weapon]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Shoulder] = Button::Create(GetScene(),
		L"EquipSlot_Shoulder",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_18.png",
		D3DXVECTOR3(-69, 143 - 60 , 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Shoulder]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Shoulder]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Lower] = Button::Create(GetScene(),
		L"EquipSlot_Lower",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_4.png",
		D3DXVECTOR3(-69, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Lower]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Lower]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Lower]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Lower]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});

	m_equipSlots[(int)EEquipSlot::Boots] = Button::Create(GetScene(),
		L"EquipSlot_Boots",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_6.png",
		D3DXVECTOR3(-69, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Boots]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Boots]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Boots]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Boots]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});



	m_pUnderLine = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIPartyMatching_I11_2.png",
		D3DXVECTOR3(-235.2, -88.8, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(489.6, 3, 1),
		L"EquipmentUI_UnderLine");

	m_pUnderPanel = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
		D3DXVECTOR3(-237.6, -115.2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(445, 35, 1),
		L"EquipmentUI_UnderPanel");

	m_pClassIcon = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/ClassMark_0.png",
		D3DXVECTOR3(-420.8, -116.8, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(60, 60, 1),
		L"EquipmentUI_ClassMark");

	m_pEquipSelectPanel = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_1.png",
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"EquipSelectPanel");
	m_pEquipSelectPanel->SetActive(false);

	m_pEquipInfoUI = ItemInfoUI::Create(GetScene(), L"EquipInfoUI");
	m_pEquipInfoUI->Hide();

}

void EquipmentUI::Update()
{
	if (m_bShow)
	{
		/* Title */
		ENGINE->DrawText(L"Ä³¸¯ÅÍ Á¤º¸", D3DXVECTOR3(112, 146, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* Level */
		ENGINE->DrawText(L"·¹º§", D3DXVECTOR3(130, 490, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		// level value´Â ÀÓ½Ã
		ENGINE->DrawText(L"50", D3DXVECTOR3(200, 490, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* Character name */
		ENGINE->DrawText(L"¹ß¸®¾È", D3DXVECTOR3(306, 490,0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1,(float)127 / 255, 0, 1));
		
		/* Èû */
		ENGINE->DrawText(L"Èû", D3DXVECTOR3(67, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(L"62", D3DXVECTOR3(230, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* Ã¼·Â */
		ENGINE->DrawText(L"Ã¼·Â", D3DXVECTOR3(67, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(L"130", D3DXVECTOR3(230, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));


		/* Áö´É */
		ENGINE->DrawText(L"Áö´É", D3DXVECTOR3(304, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(L"31", D3DXVECTOR3(435, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		
		/* ¹ÎÃ¸ */
		ENGINE->DrawText(L"¹ÎÃ¸", D3DXVECTOR3(304, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(L"38", D3DXVECTOR3(435, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));



	}
}

void EquipmentUI::Render()
{
}

void EquipmentUI::Show()
{
	m_pBackground->SetActive(true);
	for (auto slot : m_equipSlots)
	{
		slot->SetActive(true);
	}
	m_pCloseButton->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pUnderPanel->SetActive(true);
	m_pClassIcon->SetActive(true);

	m_pEquipSelectPanel->SetActive(false);

	m_bShow = true;
}

void EquipmentUI::Hide()
{
	m_pBackground->SetActive(false);
	for (auto slot : m_equipSlots)
	{
		slot->SetActive(false);
	}
	m_pCloseButton->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pUnderPanel->SetActive(false);
	m_pClassIcon->SetActive(false);

	m_pEquipSelectPanel->SetActive(false);

	m_bShow = false;
}

bool EquipmentUI::IsShow()
{
	return m_bShow;
}

EquipmentUI * EquipmentUI::Create(Scene * pScene, std::wstring name)
{
	EquipmentUI * ui = new EquipmentUI(pScene, name);
	ui->Initialize();
	return ui;
}
