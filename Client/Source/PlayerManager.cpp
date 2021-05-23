#include "stdafx.h"
#include "PlayerManager.h"
#include "GameScene.h"
#include "Player.h"

PlayerManager::PlayerManager(Scene * pScene)
{
	m_pScene = static_cast<GameScene*>(pScene);
	assert(m_pScene);
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Initialize()
{
}

void PlayerManager::Update()
{
	/* Form Change */
	//if (KEYBOARD->Up('R'))
	//{
	//	m_pOriginPlayer->SetAnimationSet(1); // put in weapon
	//	
	//	m_bPutInWeapon = true;
	//}

	//if (m_bPutInWeapon == true)
	//{
	//	bool isEnd = m_pOriginPlayer->IsAnimationSetEnd();
	//	if (isEnd == true)
	//	{
	//		/* Do Form Change */
	//		m_pOriginPlayer->SetActive(false);
	//		m_pUnWeaponPlayer->SetActive(true);
	//	}
	//}
}
