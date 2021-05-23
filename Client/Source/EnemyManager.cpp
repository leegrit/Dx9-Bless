#include "stdafx.h"
#include "EnemyManager.h"
#include "ObjectContainer.h"
#include "GameScene.h"
#include "Enemy.h"

EnemyManager::EnemyManager(GameScene * pScene)
{
	m_pScene = pScene;
	assert(m_pScene);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize()
{
	for (auto enemy : m_pScene->GetObjectContainer()->GetOpaqueObjectAll())
	{
		Enemy* pEnemy = dynamic_cast<Enemy*>(enemy);
		if (pEnemy == nullptr) continue;


		m_enemies.push_back(pEnemy);
	}
}

void EnemyManager::Update()
{
	for (auto enemy : m_enemies)
	{
		if (enemy->IsDied())
		{
			enemy->ResurrectionElapsed() += TIMER->getDeltaTime();
			if (enemy->ResurrectionElapsed() >= enemy->GetResurrectionDelay())
			{
				enemy->Reset();
			}
		}
	}
}
