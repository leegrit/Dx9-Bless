#include "stdafx.h"
#include "ActorManager.h"
#include "ObjectContainer.h"
#include "GameScene.h"
#include "Character.h"

ActorManager::ActorManager(GameScene * pScene)
{
	assert(pScene);
	m_pScene = pScene;
}

ActorManager::~ActorManager()
{
}

void ActorManager::Initialize()
{
	for (auto character : m_pScene->GetObjectContainer()->GetOpaqueObjectAll())
	{
		Character* pCharacter = dynamic_cast<Character*>(character);
		if (pCharacter == nullptr) continue;


		m_actors.push_back(pCharacter);
	}
}

void ActorManager::Update()
{
}
