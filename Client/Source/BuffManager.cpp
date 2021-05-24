#include "stdafx.h"
#include "BuffManager.h"
#include "ItemInfo.h"
#include "GameScene.h"
#include "Player.h"
#include "Client_Events.h"
#include "PlayerBuffInfo.h"

BuffManager::BuffManager(GameScene * pScene)
{
	m_pScene = pScene;
	EventDispatcher::AddEventListener(GameEvent::UseItem, "BuffManager",
		std::bind(&BuffManager::OnUseItem, this, placeholders::_1));


}

BuffManager::~BuffManager()
{
	EventDispatcher::RemoveEventListener(GameEvent::UseItem, "BuffManager");
}

void BuffManager::OnUseItem(void * pUseItem)
{
	ItemInfo itemInfo = *static_cast<ItemInfo*>(pUseItem);

	switch (itemInfo.buffType)
	{
	case EItemBuffType::HPHeal:
	{
		PlayerPotionEffectDesc * desc= new PlayerPotionEffectDesc();
		desc->key = L"PotionBuffEffect";
		desc->lifeTime = 2.0f;
		desc->color = D3DXCOLOR(0, 1, 0, 1);
		desc->onUpdate = std::bind(&BuffManager::OnBuffEffectUpdate, this, placeholders::_1);
		desc->onEnd = std::bind(&BuffManager::OnBuffEffectEnd, this, placeholders::_1);

		
		m_pScene->GetEffectManager()->AddCustomEffect(desc);


		Player* pPlayer = static_cast<Player*>(PLAYER);
		pPlayer->IncreaseHP(itemInfo.itemValue);

		break;
	}
	case EItemBuffType::MPHeal:
	{
		PlayerPotionEffectDesc * desc = new PlayerPotionEffectDesc();
		desc->key = L"PotionBuffEffect";
		desc->lifeTime = 2.0f;
		desc->color = D3DXCOLOR(0, 0, 1, 1);
		desc->onUpdate = std::bind(&BuffManager::OnBuffEffectUpdate, this, placeholders::_1);
		desc->onEnd = std::bind(&BuffManager::OnBuffEffectEnd, this, placeholders::_1);

		m_pScene->GetEffectManager()->AddCustomEffect(desc);


		Player* pPlayer = static_cast<Player*>(PLAYER);
		pPlayer->IncreaseMP(itemInfo.itemValue);
		break;
	}
	case EItemBuffType::PowerUp:
	{
		PlayerPotionEffectDesc * desc = new PlayerPotionEffectDesc();
		desc->key = L"PotionBuffEffect";
		desc->lifeTime = 2.0f;
		desc->color = D3DXCOLOR(1, 0, 0, 1);
		desc->onUpdate = std::bind(&BuffManager::OnBuffEffectUpdate, this, placeholders::_1);
		desc->onEnd = std::bind(&BuffManager::OnBuffEffectEnd, this, placeholders::_1);

		m_pScene->GetEffectManager()->AddCustomEffect(desc);

		BuffDesc buffDesc;
		buffDesc.key = L"PowerUpBuff";
		buffDesc.imagePath = itemInfo.imagePath;
		buffDesc.duration = itemInfo.itemDuration;
		buffDesc.addAtk = itemInfo.itemValue;

		m_pPlayerBuffInfo->AddBuff(buffDesc);
		break;
	}
	case EItemBuffType::SpeedUp:
	{
		PlayerPotionEffectDesc * desc = new PlayerPotionEffectDesc();
		desc->key = L"PotionBuffEffect";
		desc->lifeTime = 2.0f;
		desc->color = D3DXCOLOR(1, 0, 0, 1);
		desc->onUpdate = std::bind(&BuffManager::OnBuffEffectUpdate, this, placeholders::_1);
		desc->onEnd = std::bind(&BuffManager::OnBuffEffectEnd, this, placeholders::_1);

		m_pScene->GetEffectManager()->AddCustomEffect(desc);

		BuffDesc buffDesc;
		buffDesc.key = L"SpeedUpBuff";
		buffDesc.imagePath = itemInfo.imagePath;
		buffDesc.duration = itemInfo.itemDuration;
		buffDesc.addAtkSpd = itemInfo.itemValue;

		m_pPlayerBuffInfo->AddBuff(buffDesc);
		break;
	}
	case EItemBuffType::DefenceUp:
	{
		PlayerPotionEffectDesc * desc = new PlayerPotionEffectDesc();
		desc->key = L"PotionBuffEffect";
		desc->lifeTime = 2.0f;
		desc->color = D3DXCOLOR(1, 0, 0, 1);
		desc->onUpdate = std::bind(&BuffManager::OnBuffEffectUpdate, this, placeholders::_1);
		desc->onEnd = std::bind(&BuffManager::OnBuffEffectEnd, this, placeholders::_1);

		m_pScene->GetEffectManager()->AddCustomEffect(desc);


		BuffDesc buffDesc;
		buffDesc.key = L"DefenceUpBuff";
		buffDesc.imagePath = itemInfo.imagePath;
		buffDesc.duration = itemInfo.itemDuration;
		buffDesc.addDef = itemInfo.itemValue;

		m_pPlayerBuffInfo->AddBuff(buffDesc);
		break;
	}
	case EItemBuffType::CoolTimeReset:
	{

		break;
	}
	default:
		assert(false);
		break;
	}
}

void BuffManager::Initialize()
{
	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));
}

void BuffManager::Update()
{
	for (int i = 0; i < m_pPlayerBuffInfo->buffDescs.size(); i++)
	{
		m_pPlayerBuffInfo->buffDescs[i].elapsed += TIMER->getDeltaTime();
		if (m_pPlayerBuffInfo->buffDescs[i].duration <= m_pPlayerBuffInfo->buffDescs[i].elapsed)
		{
			m_pPlayerBuffInfo->RemoveBuff(m_pPlayerBuffInfo->buffDescs[i]);
			i--;
		}
	}
}

void BuffManager::OnBuffEffectUpdate(CustomEffectDesc * pDesc)
{
	PlayerPotionEffectDesc * pEffectDesc = static_cast<PlayerPotionEffectDesc*>(pDesc);
	float amount = (float)pEffectDesc->elapsed / pEffectDesc->lifeTime;
	amount = (1 - amount) - 0.3f;
	amount = amount <= 0 ? 0 : amount;
	Player* pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetRenderEffectOption(RenderEffectOption::RimLight);
	pPlayer->SetRimWidth(amount);
	pPlayer->SetRimColor(pEffectDesc->color);
}

void BuffManager::OnBuffEffectEnd(CustomEffectDesc * pDesc)
{
	PlayerPotionEffectDesc * pEffectDesc = static_cast<PlayerPotionEffectDesc*>(pDesc);
	float amount = pEffectDesc->elapsed / pEffectDesc->lifeTime;

	Player* pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetRenderEffectOption(RenderEffectOption::None);
}
