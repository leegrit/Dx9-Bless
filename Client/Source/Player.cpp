#include "stdafx.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerNormalAttack.h"
#include "PlayerInfo.h"
#include "ExpTable.h"
#include "GameScene.h"
#include "UIManager.h"
#include "ProgressBar.h"
#include "Client_Events.h"

Player::Player(Scene * pScene, NavMesh * pNavMesh)
	:Character(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 8)
{
	SetLayer(Layer::Player);

	SetSkinningType(ESkinningType::HardwareSkinning);


	EventDispatcher::AddEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()),
		std::bind(&Player::OnExpChanged, this, placeholders::_1));
}

Player::~Player()
{
	EventDispatcher::RemoveEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()));
}

void Player::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);
	SetParams(50, 1000, 1000);
	
	PlayerController* pController = PlayerController::Create(this);
	AddComponent(pController);
	AddComponent(PlayerNormalAttack::Create(this, pController));

}

Player * Player::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Player* player = new Player(pScene, pNavMesh);
	player->Initialize(dataPath);
	return player;
}

void Player::OnCollision(Collider * other)
{
}

void Player::OnDamaged(GameObject * pSender, float damage, bool isCritical)
{
	GameScene* scene = static_cast<GameScene*>(SCENE);
	scene->GetUIManager()->PushDamageFont(damage, true, isCritical, m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)));

}

void Player::OnHPChanged()
{
	if (m_pHPBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pHPBarUI = static_cast<HyEngine::ProgressBar*>(scene->GetUIManager()->GetStaticUI(L"PlayerHP_Fill"));
	}
	m_pHPBarUI->SetAmount(GetCurHP() / GetMaxHP());
}

void Player::OnMPChanged()
{
	if (m_pHPBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pMPBarUI = static_cast<ProgressBar*>( scene->GetUIManager()->GetStaticUI(L"PlayerMP_Fill"));
	}
	m_pMPBarUI->SetAmount(GetCurMP() / GetMaxMP());
}

void Player::OnExpChanged( void*) 
{
	if (m_pExpBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pExpBarUI = static_cast<ProgressBar*>(scene->GetUIManager()->GetStaticUI(L"PlayerExp_Fill"));
	}
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	float amount;
	if (pScene->GetPlayerInfo()->level == 1)
	{
		amount = pScene->GetPlayerInfo()->exp / pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1];
	}
	else
	{
		// º¸Á¤Ä¡
		float temp = pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 2];
		amount = pScene->GetPlayerInfo()->exp - temp / pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1] - temp;
	}
	m_pExpBarUI->SetAmount(amount);
}
