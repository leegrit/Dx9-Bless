#include "stdafx.h"
#include "EquipmentUI.h"
#include "Button.h"
#include "PathManager.h"
#include "ItemInfoUI.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "PlayerEquipData.h"
#include "PlayerInfo.h"
#include "PlayerStatusData.h"
#include "InventoryData.h"
#include "SoundManager.h"
EquipmentUI::EquipmentUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
	EventDispatcher::AddEventListener(GameEvent::EquipmentChange, std::to_string(GetInstanceID()).c_str(),
		std::bind(&EquipmentUI::OnEquipmentChanged, this, placeholders::_1));
}

EquipmentUI::~EquipmentUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::EquipmentChange, std::to_string(GetInstanceID()).c_str());
}

void EquipmentUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUISkillTree_I47_1.png",
		D3DXVECTOR3(-237, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(460, 494, 1),
		L"EquipmentUI_Background");
	m_pBackground->SetRenderQueue(3500);

	m_pCloseButton = Button::Create(GetScene(), L"EquipmentUI_CloseButton",
		PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png",
		D3DXVECTOR3(-43, 224, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(20, 20, 1));

	m_equipSlots.reserve((int)EEquipSlot::MAX);
	m_equipSlots.resize((int)EEquipSlot::MAX);

	m_equipIcons.reserve((int)EEquipSlot::MAX);
	m_equipIcons.resize((int)EEquipSlot::MAX);

	m_iconCovers.reserve((int)EEquipSlot::MAX);
	m_iconCovers.resize((int)EEquipSlot::MAX);

	/* Left */
	m_equipSlots[(int)EEquipSlot::Helmet] = Button::Create(GetScene(),
		L"EquipSlot_Helmet",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_5.png",
		D3DXVECTOR3(-403, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Helmet]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]() 
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Helmet)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Helmet]->m_pTransform->m_position.operator D3DXVECTOR3(), pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Helmet), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Helmet]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Helmet]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Helmet]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Helmet) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Helmet));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Helmet);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});

	m_equipSlots[(int)EEquipSlot::Helmet]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Helmet] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-403, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Helmet]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Helmet]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Helmet] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-403, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Helmet]->SetActive(false);

	

	m_equipSlots[(int)EEquipSlot::Upper] = Button::Create(GetScene(),
		L"EquipSlot_Upper",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_17.png",
		D3DXVECTOR3(-403, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Upper]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Upper)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Upper]->m_pTransform->m_position.operator D3DXVECTOR3(), 
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Upper), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Upper]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Upper]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Upper]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Upper) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Upper));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Upper);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});

	m_equipSlots[(int)EEquipSlot::Upper]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Upper] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-403, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Upper]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Upper]->SetActive(false);
	m_iconCovers[(int)EEquipSlot::Upper] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-403, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Upper]->SetActive(false);


	m_equipSlots[(int)EEquipSlot::Belt] = Button::Create(GetScene(),
		L"EquipSlot_Belt",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_8.png",
		D3DXVECTOR3(-403, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Belt]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Belt)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Belt]->m_pTransform->m_position.operator D3DXVECTOR3(),
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Belt),false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Belt]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Belt]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Belt]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Belt) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Belt));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Belt);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});

	m_equipSlots[(int)EEquipSlot::Belt]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Belt] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-403, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Belt]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Belt]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Belt] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-403, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Belt]->SetActive(false);


	m_equipSlots[(int)EEquipSlot::Glove] = Button::Create(GetScene(),
		L"EquipSlot_Glove",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_9.png",
		D3DXVECTOR3(-403, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Glove]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Glove)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Glove]->m_pTransform->m_position.operator D3DXVECTOR3(), 
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Glove),false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Glove]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Glove]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Glove]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Glove) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Glove));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Glove);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});
	m_equipSlots[(int)EEquipSlot::Glove]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Glove] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-403, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Glove]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Glove]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Glove] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-403, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Glove]->SetActive(false);

	/* Right */
	m_equipSlots[(int)EEquipSlot::Weapon] = Button::Create(GetScene(),
		L"EquipSlot_Weapon",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_10.png",
		D3DXVECTOR3(-69, 143 , 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Weapon]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Weapon)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Weapon]->m_pTransform->m_position.operator D3DXVECTOR3(), 
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Weapon), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Weapon]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Weapon]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Weapon]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Weapon) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Weapon));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Weapon);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});
	m_equipSlots[(int)EEquipSlot::Weapon]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Weapon] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-69, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Weapon]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Weapon]->SetActive(false);

	m_equipIcons[(int)EEquipSlot::Weapon]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Weapon]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Weapon] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-69, 143, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Weapon]->SetActive(false);

	m_equipSlots[(int)EEquipSlot::Shoulder] = Button::Create(GetScene(),
		L"EquipSlot_Shoulder",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_18.png",
		D3DXVECTOR3(-69, 143 - 60 , 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Shoulder)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Shoulder]->m_pTransform->m_position.operator D3DXVECTOR3(), 
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Shoulder), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Shoulder]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Shoulder) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Shoulder));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Shoulder);
		

		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});
	m_equipSlots[(int)EEquipSlot::Shoulder]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Shoulder] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-69, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Shoulder]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Shoulder]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Shoulder] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-69, 143 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Shoulder]->SetActive(false);

	m_equipSlots[(int)EEquipSlot::Lower] = Button::Create(GetScene(),
		L"EquipSlot_Lower",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_4.png",
		D3DXVECTOR3(-69, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Lower]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Lower)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Lower]->m_pTransform->m_position.operator D3DXVECTOR3(),
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Lower), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Lower]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Lower]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Lower]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Lower) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Lower));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Lower);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});
	m_equipSlots[(int)EEquipSlot::Lower]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Lower] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-69, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Lower]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Lower]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Lower] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-69, 143 - 60 * 2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Lower]->SetActive(false);

	m_equipSlots[(int)EEquipSlot::Boots] = Button::Create(GetScene(),
		L"EquipSlot_Boots",
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_6.png",
		D3DXVECTOR3(-69, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1));
	m_equipSlots[(int)EEquipSlot::Boots]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (!pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Boots)) return;
		m_pEquipSelectPanel->SetActive(true);
		m_pEquipInfoUI->Show(m_equipSlots[(int)EEquipSlot::Boots]->m_pTransform->m_position.operator D3DXVECTOR3(), 
			pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Boots), false);
		m_pEquipSelectPanel->m_pTransform->SetPosition(m_equipSlots[(int)EEquipSlot::Boots]->m_pTransform->m_position);
	});
	m_equipSlots[(int)EEquipSlot::Boots]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [&]()
	{
		m_pEquipSelectPanel->SetActive(false);
		m_pEquipInfoUI->Hide();
	});
	m_equipSlots[(int)EEquipSlot::Boots]->SetButtonEvent(EButtonEvent::RightButtonUp, [&]()
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Boots) == false) return;
		pScene->GetInventoryData()->PushItem(pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot::Boots));
		pScene->GetPlayerEquipData()->RemoveEquipment(EEquipSlot::Boots);
		EventDispatcher::TriggerEvent(GameEvent::EquipmentChange);
	});
	m_equipSlots[(int)EEquipSlot::Boots]->SetRenderQueue(3400);

	m_equipIcons[(int)EEquipSlot::Boots] = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-69, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_Icon");
	m_equipIcons[(int)EEquipSlot::Boots]->SetRenderQueue(3300);
	m_equipIcons[(int)EEquipSlot::Boots]->SetActive(false);

	m_iconCovers[(int)EEquipSlot::Boots] = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-69, 143 - 60 * 3, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"Equip_IconCover");
	m_iconCovers[(int)EEquipSlot::Boots]->SetActive(false);


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
		GameScene * pScene = static_cast<GameScene*>(SCENE);
		

		/* Title */
		ENGINE->DrawText(L"캐릭터 정보", D3DXVECTOR3(112, 146, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* Level */
		ENGINE->DrawText(L"레벨", D3DXVECTOR3(130, 490, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));


		// level value는 임시
		ENGINE->DrawText(std::to_wstring(pScene->GetPlayerInfo()->level).c_str(), D3DXVECTOR3(200, 490, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* Character name */
		ENGINE->DrawText(L"발리안", D3DXVECTOR3(306, 490,0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1,(float)127 / 255, 0, 1));
		
		/* 힘 */
		ENGINE->DrawText(L"힘", D3DXVECTOR3(67, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(std::to_wstring(pScene->GetPlayerStatusData()->power + pScene->GetPlayerEquipData()->GetPower()).c_str(), D3DXVECTOR3(230, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		/* 체력 */
		ENGINE->DrawText(L"체력", D3DXVECTOR3(67, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(std::to_wstring(pScene->GetPlayerStatusData()->life).c_str(), D3DXVECTOR3(230, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));


		/* 지능 */
		ENGINE->DrawText(L"물리방어", D3DXVECTOR3(304, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(std::to_wstring(pScene->GetPlayerStatusData()->intel).c_str(), D3DXVECTOR3(435, 542, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		
		/* 민첩 */
		ENGINE->DrawText(L"마법방어", D3DXVECTOR3(304, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(std::to_wstring(pScene->GetPlayerStatusData()->dex).c_str(), D3DXVECTOR3(435, 582, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));



	}
}

void EquipmentUI::Render()
{
}

void EquipmentUI::OnEquipmentChanged(void *)
{
	if (m_bShow == false)return;
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	for (int i = 0; i < m_equipIcons.size(); i++)
	{
		if (pScene->GetPlayerEquipData()->IsExistEquipment((EEquipSlot)i))
		{
			auto data = pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot(i));
			m_equipIcons[i]->SetTexture(data.imagePath);
			m_equipIcons[i]->SetActive(true);
			m_iconCovers[i]->SetActive(true);
		}
		else
		{
			m_equipIcons[i]->SetActive(false);
			m_iconCovers[i]->SetActive(false);
		}
	}
}

void EquipmentUI::Show()
{
	m_pBackground->SetActive(true);
	for (auto slot : m_equipSlots)
	{
		slot->SetActive(true);
	}
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	for (int i = 0; i < m_equipIcons.size(); i++)
	{
		if (pScene->GetPlayerEquipData()->IsExistEquipment((EEquipSlot)i))
		{
			auto data = pScene->GetPlayerEquipData()->GetEquipment(EEquipSlot(i));
			m_equipIcons[i]->SetTexture(data.imagePath);
			m_equipIcons[i]->SetActive(true);
			m_iconCovers[i]->SetActive(true);
		}
		else
		{
			m_equipIcons[i]->SetActive(false);
			m_iconCovers[i]->SetActive(false);
		}
	}

	m_pCloseButton->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pUnderPanel->SetActive(true);
	m_pClassIcon->SetActive(true);

	m_pEquipSelectPanel->SetActive(false);

	m_bShow = true;

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("Equip_Open", L"Inven_Open.wav", desc);

	EventDispatcher::TriggerEvent(UIEvent::EquipmentUIOpen);
}

void EquipmentUI::Hide()
{
	m_pBackground->SetActive(false);
	for (auto slot : m_equipSlots)
	{
		slot->SetActive(false);
	}
	for (auto icon : m_equipIcons)
	{
		icon->SetActive(false);
	}
	for (auto cover : m_iconCovers)
	{
		cover->SetActive(false);
	}
	m_pCloseButton->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pUnderPanel->SetActive(false);
	m_pClassIcon->SetActive(false);

	m_pEquipSelectPanel->SetActive(false);
	m_pEquipInfoUI->Hide();
	m_bShow = false;

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("Equip_Close", L"Inven_Close.wav", desc);

	EventDispatcher::TriggerEvent(UIEvent::EquipmentUIClose);
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
