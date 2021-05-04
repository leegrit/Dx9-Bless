#include "stdafx.h"
#include "GameManager.h"
#include "GameScene.h"
#include "Client_Events.h"
#include "PlayerInfo.h"
#include "ExpTable.h"

GameManager::GameManager(GameScene * pScene)
	: m_pScene(pScene)
{
	EventDispatcher::AddEventListener(GameEvent::SendExp, "GameManager",
		std::bind(&GameManager::OnSendExp, this, placeholders::_1));

}

GameManager::~GameManager()
{
	EventDispatcher::RemoveEventListener(GameEvent::SendExp, "GameManager");

}

void GameManager::OnSendExp(void * value)
{
	float exp = *static_cast<float*>(value);
	PlayerInfo* pPlayerInfo = m_pScene->GetPlayerInfo();
	pPlayerInfo->exp += exp;
	
	ExpTable* pExpTable = m_pScene->GetExpTable();

	// ���� ����ġ�� exp ���̺��� �ش� �������� ������ ������
	if (pPlayerInfo->exp >= pExpTable->expTable[pPlayerInfo->level - 1])
	{
		pPlayerInfo->level++;
		EventDispatcher::TriggerEvent(GameEvent::LevelUp, (int*)&pPlayerInfo->level);
	}


}

void GameManager::Initialize()
{
}

void GameManager::Update()
{
}
