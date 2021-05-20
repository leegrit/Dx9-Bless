#include "stdafx.h"
#include "SpoilsObject.h"
#include "GameScene.h"
#include "UIManager.h"
#include "Client_Events.h"
#include "InventoryData.h"

SpoilsObject::SpoilsObject(Scene * pScene, std::wstring name, SpoilsObjectDesc desc)
	:GameObject( ERenderType::None, pScene,nullptr,  name)
{
	m_desc = desc;
}

SpoilsObject::~SpoilsObject()
{
}

void SpoilsObject::Initialize()
{
	m_pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
}

void SpoilsObject::Update()
{
}

void SpoilsObject::Collecting(_Out_ bool * bEnd)
{
	if (m_bCollectable == false) return;
	*bEnd = false;

	float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position - m_pTransform->m_position).operator D3DXVECTOR3());

	GameScene * pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowCollectInteractPanel();

	if (KEYBOARD->Down('F'))
	{
		if (m_bCollecting == false)
		{
			m_bCollecting = true;
			OnCollectBegin();

			EventDispatcher::TriggerEvent(GameEvent::BeginSpoils, nullptr);
		}
		else if (m_bCollecting == true)
		{
			*bEnd = true;
			DoCollect();
			OnCollectEnd();
			EventDispatcher::TriggerEvent(GameEvent::EndSpoils, nullptr);
		}
	}
}

void SpoilsObject::OutOfRange()
{
	OnCollectEnd();
}

void SpoilsObject::DoCollect()
{
	if (m_desc.itemInfo1.itemType != EItemType::None)
	{
		m_pInventoryData->PushItem(m_desc.itemInfo1);
		EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&m_desc.itemInfo1);
	}
	if (m_desc.itemInfo2.itemType != EItemType::None)
	{
		m_pInventoryData->PushItem(m_desc.itemInfo2);
		EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&m_desc.itemInfo2);
	}
}

void SpoilsObject::OnCollected()
{
}

void SpoilsObject::OnCollectBegin()
{
	GameScene * pScene = static_cast<GameScene*>(SCENE);
	pScene->GetUIManager()->ShowSpoilsUI(m_desc.itemInfo1);

}

void SpoilsObject::OnCollectEnd()
{
	GameScene * pScene = static_cast<GameScene*>(SCENE);
	pScene->GetUIManager()->HideSpoilsUI();

}

SpoilsObject * SpoilsObject::Create(Scene * pScene, std::wstring name, SpoilsObjectDesc desc)
{
	SpoilsObject* obj = new SpoilsObject(pScene, name, desc);
	obj->Initialize();
	return obj;
}
