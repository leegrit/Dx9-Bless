#include "stdafx.h"
#include "NonePlayer.h"
#include "Quest.h"
#include "Billboard.h"
#include "PathManager.h"
#include "GameScene.h"
#include "QuestManager.h"


NonePlayer::NonePlayer(Scene * scene)
	:Character(scene, nullptr)
{

}

NonePlayer::~NonePlayer()
{
}

void NonePlayer::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);


	//m_pMainQuestMarker = HyEngine::Billboard::Create(GetScene(), this, L"MainQuestMarker");
	//m_pMainQuestMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"Texture/StatusGauge_4.png");
	//m_pMainQuestMarker->m_pTransform->SetScale(100, 100, 1);
	//m_pMainQuestMarker->SetActive(false);

	//m_pSubQuestMarker = HyEngine::Billboard::Create(GetScene(), this, L"SubQuestMarker");
	//m_pSubQuestMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"Texture/quest mark_question mark5_12.png");
	//m_pSubQuestMarker->m_pTransform->SetScale(100, 100, 1);
	//m_pSubQuestMarker->SetActive(false);

	//m_pMainQuestFinishMarker = HyEngine::Billboard::Create(GetScene(), this, L"MainQuestFinishMarker");
	//m_pMainQuestFinishMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"Texture/BLUINameTag_I1_36.png");
	//m_pMainQuestFinishMarker->m_pTransform->SetScale(100, 100, 1);
	//m_pMainQuestFinishMarker->SetActive(false);

	//m_pSubQuestFinishMarker = HyEngine::Billboard::Create(GetScene(), this, L"SubQuestFinishMarker");
	//m_pSubQuestFinishMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"Texture/BLUINameTag_I1_37.png");
	//m_pSubQuestFinishMarker->m_pTransform->SetScale(100, 100, 1);
	//m_pSubQuestFinishMarker->SetActive(false);

}

void NonePlayer::QuestInitialize()
{
}

void NonePlayer::Update()
{
	Character::Update();

	
}

void NonePlayer::OnCollision(Collider * other)
{
	
}

//void NonePlayer::ShowQuestMark(Quest * pQuest)
//{
//	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
//	{
//		m_pMainQuestMarker->SetActive(true);
//		m_pSubQuestMarker->SetActive(false);
//
//	}
//	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
//	{
//		// 만약 mainquest marker가 떠있다면 sub quest marker는 무시된다.
//		if (m_pMainQuestMarker->GetActive() == true)
//		{
//			return;
//		}
//
//		m_pSubQuestMarker->SetActive(true);
//	}
//}
//
//void NonePlayer::RemoveQuestMark(Quest * pQuest)
//{
//	m_pMainQuestMarker->SetActive(false);
//	m_pSubQuestMarker->SetActive(false);
//}
//
//void NonePlayer::ShowQuestFinishMark(Quest * pQuest)
//{
//	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
//	{
//		m_pMainQuestFinishMarker->SetActive(true);
//		m_pSubQuestFinishMarker->SetActive(false);
//
//	}
//	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
//	{
//		// 만약 mainquest marker가 떠있다면 sub quest marker는 무시된다.
//		if (m_pMainQuestFinishMarker->GetActive() == true)
//		{
//			return;
//		}
//
//		m_pSubQuestFinishMarker->SetActive(true);
//	}
//}

//void NonePlayer::RemoveQuestFinishMark(Quest * pQuest)
//{
//	m_pMainQuestFinishMarker->SetActive(false);
//	m_pSubQuestFinishMarker->SetActive(false);
//}

void NonePlayer::DoInteract()
{

	for (auto& quest : m_quests)
	{
		if (quest->GetQuestState() == EQuestState::Open)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GetScene());
			scene->GetQuestManager()->ShowQuestDialog(this, quest);

			return;
		}
	}
}

void NonePlayer::AddQuest(Quest * pQuest)
{
	GameScene* scene = static_cast<GameScene*>(GetScene());
	assert(scene);
	scene->GetQuestManager()->AddQuest(pQuest);
	m_quests.push_back(pQuest);

}

