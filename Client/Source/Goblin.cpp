#include "stdafx.h"
#include "Goblin.h"
#include "NameFont.h"
#include "Client_Events.h"
#include "GoblinAttack.h"
#include "GoblinDie.h"
#include "GoblinDied.h"
#include "GoblinHit.h"
#include "GoblinIdle.h"
#include "GoblinMove.h"
#include "GameScene.h"
#include "ItemInfo.h"
#include "InteractManager.h"
#include "PathManager.h"

Goblin::Goblin(Scene * pScene, NavMesh * pNavMesh)
	:Enemy(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5, ESkinningType::HardwareSkinning)
{
	SetLayer(Layer::Enemy);

	//SetSkinningType(ESkinningType::HardwareSkinning);
}

Goblin::~Goblin()
{
	m_state.Release();
}

void Goblin::Initialize(std::wstring dataPath)
{
	Enemy::Initialize(dataPath);
	SetLayer(Layer::Enemy);

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
		std::bind(&Goblin::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);

	
	SetParams(10, 500, 100);
	m_state.Add<GoblinAttack>(this, "Attack");
	m_state.Add<GoblinDie>(this, "Die");
	m_state.Add<GoblinHit>(this, "Hit");
	m_state.Add<GoblinIdle>(this, "Idle");
	m_state.Add<GoblinMove>(this, "Move");
	m_state.Add<GoblinDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"���", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 16, 0), -40, D3DXCOLOR(1, 1, 0, 1));

	ShowHPBar();

	SetDissolveTexture(PATH->AssetsPathW() + L"Texture/dissolveMap.jpg");
	SetDissolveAmount(0.0f);
	SetFringeAmount(0.01f);
}

void Goblin::Update()
{
	Enemy::Update();
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	//m_pNameFont->SetOffset(D3DXVECTOR3(0, 18, 0));
	//m_pNameFont->SetCenterOffset(-20);

	if (IsDied())
	{
		m_pNameFont->SetColor(D3DXCOLOR(0.2f,0.2f, 0.2f, 1));
	}
	else if (GetCurHP() != GetMaxHP())
	{
		m_colorChangeElapsed += TIMER->getDeltaTime();
		if (m_colorChangeElapsed >= m_colorChangeDelay)
		{
			m_colorChangeElapsed = 0;
			m_bRedColor = !m_bRedColor;
		}
		if (m_bRedColor)
		{
			m_pNameFont->SetColor(D3DXCOLOR(1, 0, 0, 1));
		}
		else
		{
			m_pNameFont->SetColor(D3DXCOLOR(1, 0.5f, 0, 1));
		}
	}
	m_state.Update();
}

void Goblin::Render()
{
	Enemy::Render();

	m_pNameFont->RenderFont();
}

UINT Goblin::GetTargetLayer()
{
	return Layer::Player;
}

void Goblin::OnCollision(Collider * other)
{

}

void Goblin::OnHitOthers(Collider * other)
{
	/* ���⼭ �������� ���� Ÿ���� �����Ѵ�. */
	AddHitOthers(other->GetGameObject());
}

void Goblin::OnDied()
{
	Enemy::OnDied();

	ItemInfo leaderPiece;
	leaderPiece.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/GoblinLeader.jpg";
	leaderPiece.itemName = L"��� ����";
	leaderPiece.itemType = EItemType::Spoils;
	leaderPiece.typeText = L"���";
	leaderPiece.effectText = L"ǰ���� ������ ��� �����̴�.";
	leaderPiece.itemDescription = L"ǰ���� ������ ��� �����̴�.";
	leaderPiece.salePrice = 30;

	SpoilsObjectDesc desc;
	desc.key = L"Goblin.Spoils";
	desc.position = m_pTransform->m_position.operator D3DXVECTOR3();
	desc.itemInfo1 = leaderPiece;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	pScene->GetInteractManager()->DropSpoils(desc);

	EventDispatcher::TriggerEvent(GameEvent::SendExp, (float*)&m_exp);
}

Goblin * Goblin::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Goblin * obj = new Goblin(pScene, pNavMesh);
	obj->Initialize(dataPath);
	return obj;
}

float Goblin::GetFocusColliderSize()
{
	return 20;
}

D3DXVECTOR3 Goblin::GetFocusUIOffset()
{
	return D3DXVECTOR3(0, 5, 0);
}

int Goblin::GetLevel()
{
	return 13;
}

std::wstring Goblin::GetCharacterName()
{
	return L"���";
}

void Goblin::Reset()
{
	Enemy::Reset();
	m_state.Set("Idle");
}

int Goblin::GetAttackCount()
{
	/* Goblin�� ���� ������ 1���� */
	return 1;
}

Collider * Goblin::GetAttackCollider(int attackIndex)
{
	Collider* attackCollider = nullptr;
	if (attackIndex == 0)
	{
		attackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 5, Layer::Player,
			std::bind(&Goblin::OnHitOthers, this, placeholders::_1));
		attackCollider->SetOffset(D3DXVECTOR3(0, 0, 5));
	}
	else /* 1�����ۿ� ���� */
		assert(false);

	return attackCollider;
}

