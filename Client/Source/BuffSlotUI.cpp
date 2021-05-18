#include "stdafx.h"
#include "BuffSlotUI.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "PathManager.h"
#include "UIPanel.h"
#include "SkillProgressUI.h"
#include "PlayerBuffInfo.h"

BuffSlotUI::BuffSlotUI(Scene * pScene)
	: GameObject(ERenderType::None, pScene, nullptr, L"BuffSlotUI")
{
	EventDispatcher::AddEventListener(GameEvent::BeginLastingBuff, std::to_string(GetInstanceID()).c_str(),
		std::bind(&BuffSlotUI::OnBeginBuff, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::EndLastingBuff, std::to_string(GetInstanceID()).c_str(),
		std::bind(&BuffSlotUI::OnEndBuff, this, placeholders::_1));
}

BuffSlotUI::~BuffSlotUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::BeginLastingBuff, std::to_string(GetInstanceID()).c_str());
	EventDispatcher::RemoveEventListener(GameEvent::EndLastingBuff, std::to_string(GetInstanceID()).c_str());
}

void BuffSlotUI::Initialize()
{
	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));
	assert(m_pPlayerBuffInfo);

	for (int i = 0; i < m_maxSlotHorizontal; i++)
	{
		auto buffIcon = UIPanel::Create(GetScene(),
			L"",
			D3DXVECTOR3(m_slotXPoses[i], m_slotYPos, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(25, 25, 1),
			L"QuickSlot_ItemIcon");

		auto progress = SkillProgressUI::Create(GetScene(),
			PATH->ResourcesPathW() + L"Assets/UI/black.png",
			D3DXVECTOR3(m_slotXPoses[i], m_slotYPos, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(25, 25, 1),
			L"QuickSlotProgressUI");

		buffIcon->SetActive(false);

		m_buffIcons.push_back(buffIcon);
		m_progressUI.push_back(progress);



	}
}

void BuffSlotUI::Update()
{
	for (int i = 0; i < m_pPlayerBuffInfo->buffDescs.size(); i++)
	{
		float amount = m_pPlayerBuffInfo->buffDescs[i].elapsed / m_pPlayerBuffInfo->buffDescs[i].duration;
		m_progressUI[i]->SetAmount( 1- amount);
	}
}

void BuffSlotUI::Render()
{
}

void BuffSlotUI::OnBeginBuff(void * pBuffDesc)
{
	for (int i = 0; i < m_pPlayerBuffInfo->buffDescs.size(); i++)
	{
		BuffDesc desc = m_pPlayerBuffInfo->buffDescs[i];
		m_buffIcons[i]->SetTexture(desc.imagePath);
		m_buffIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	for (int i = m_pPlayerBuffInfo->buffDescs.size(); i < m_buffIcons.size(); i++)
	{
		m_buffIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}
}

void BuffSlotUI::OnEndBuff(void * pBuffDesc)
{
	for (int i = 0; i < m_pPlayerBuffInfo->buffDescs.size(); i++)
	{
		BuffDesc desc = m_pPlayerBuffInfo->buffDescs[i];
		m_buffIcons[i]->SetTexture(desc.imagePath);
		m_buffIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	for (int i = m_pPlayerBuffInfo->buffDescs.size(); i < m_buffIcons.size(); i++)
	{
		m_buffIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}
}

void BuffSlotUI::Show()
{
	for (int i = 0; i < m_pPlayerBuffInfo->buffDescs.size(); i++)
	{
		BuffDesc desc = m_pPlayerBuffInfo->buffDescs[i];
		m_buffIcons[i]->SetTexture(desc.imagePath);
		m_buffIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	for (int i = m_pPlayerBuffInfo->buffDescs.size(); i < m_buffIcons.size(); i++)
	{
		m_buffIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}
	m_bShow = true;
}

void BuffSlotUI::Hide()
{
	for (int i = 0; i < m_buffIcons.size(); i++)
	{
		m_buffIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}
	m_bShow = false;
}

bool BuffSlotUI::IsShow()
{
	return m_bShow;
}

BuffSlotUI * BuffSlotUI::Create(Scene * pScene)
{
	BuffSlotUI * ui = new BuffSlotUI(pScene);
	ui->Initialize();
	return ui;
}
