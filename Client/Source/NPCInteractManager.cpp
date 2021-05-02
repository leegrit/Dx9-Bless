#include "stdafx.h"
#include "NPCInteractManager.h"
#include "ObjectContainer.h"
#include "NonePlayer.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "UIManager.h"

NPCInteractManager::NPCInteractManager(Scene * pScene)
{
	m_pScene = pScene;
	m_bInteractable = true;

	EventDispatcher::AddEventListener(QuestEvent::QuestDialogOpen, "NPCInteractManager",
		std::bind(&NPCInteractManager::OnQuestDialogOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogEnd, "NPCInteractManager",
		std::bind(&NPCInteractManager::OnQuestDialogEnd, this, placeholders::_1));

}

NPCInteractManager::~NPCInteractManager()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, "NPCInteractManager");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, "NPCInteractManager");
}

void NPCInteractManager::OnQuestDialogOpen(void *)
{
	m_bInteractable = false;
	// ���ɱ� ui �� ���ֱ�(�Ⱥ��̰�)
	GameScene* gameScene = static_cast<GameScene*>(m_pScene);
	gameScene->GetUIManager()->HideTalkInteractPanel();
}

void NPCInteractManager::OnQuestDialogEnd(void *)
{
	m_bInteractable = true;
}

void NPCInteractManager::Initialize()
{
	auto& container = m_pScene->GetObjectContainer()->GetDynamicMeshAll();

	for (auto& obj : container)
	{
		NonePlayer* pNonePlayer = dynamic_cast<NonePlayer*>(obj);
		if (pNonePlayer == nullptr)
			continue;
		
		m_nonePlayers.push_back(pNonePlayer);
	}
}

void NPCInteractManager::Update()
{
	if (m_bInteractable == false)
		return;

	// ��ó�� npc�� �ִ���
	bool bExistCloseNPC = false;

	for (auto& npc : m_nonePlayers)
	{
		float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position.operator D3DXVECTOR3() - npc->m_pTransform->m_position.operator D3DXVECTOR3()));

		if (dist <= m_interDist)
		{
			bExistCloseNPC = true;
			// ��ȣ�ۿ��� ������ ����
			if (KEYBOARD->Down('F'))
			{
				m_bInteractable = false;
				npc->DoInteract();
				// ���ɱ� ui Ŭ�� �̺�Ʈ
				
				return;
			}
		}
	}

	if (bExistCloseNPC == true)
	{
		// ���⼭ ���ɱ� UI ����
		GameScene* gameScene = static_cast<GameScene*>(m_pScene);
		gameScene->GetUIManager()->ShowTalkInteractPanel();
	}
	else
	{
		GameScene* gameScene = static_cast<GameScene*>(m_pScene);
		gameScene->GetUIManager()->HideTalkInteractPanel();

	}
}
