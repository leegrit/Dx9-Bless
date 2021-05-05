#include "stdafx.h"
#include "NonePlayer.h"
#include "Quest.h"
#include "Billboard.h"
#include "PathManager.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "ZoomInCamera.h"
#include "Client_Events.h"


NonePlayer::NonePlayer(Scene * scene, ESkinningType skinningType )
	:Character(scene, nullptr, skinningType)
{
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogOpen, std::to_string( GetInstanceID()),
		std::bind(&NonePlayer::OnDialogOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogEnd, std::to_string(GetInstanceID()),
		std::bind(&NonePlayer::OnDialogEnd, this, placeholders::_1));
}

NonePlayer::~NonePlayer()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, std::to_string(GetInstanceID()));
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, std::to_string(GetInstanceID()));
}

void NonePlayer::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);

	m_pZoomInCam = ZoomInCamera::Create(GetScene(), this, L"NPC_ZoomIn_" + std::to_wstring(GetInstanceID()));

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

void NonePlayer::OnDialogOpen(void * questIndex)
{
	int index = *static_cast<int*>(questIndex);

	for (auto& quest : m_quests)
	{
		if (quest->GetQuestIndex() == index)
		{
			m_originCamName = SCENE->GetSelectedCamera()->GetName();
			SCENE->SelectCamera(m_pZoomInCam->GetName());
			m_bZoom = true;
			SetCullable(false);
			SetViewFrustumCulled(false);
			return;
		}
	}
}

void NonePlayer::OnDialogEnd(void *questIndex)
{
	int index = *static_cast<int*>(questIndex);

	for (auto& quest : m_quests)
	{
		if (quest->GetQuestIndex() == index)
		{
			m_bZoom = false;
			SCENE->SelectCamera(m_originCamName);
			SetCullable(true);
			return;
		}
	}
}


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

