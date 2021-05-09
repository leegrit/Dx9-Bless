#include "stdafx.h"
#include "Character.h"
#include "Quest.h"
#include "Billboard.h"
#include "PathManager.h"
#include "Client_Events.h"
#include "GameScene.h"



Character::Character(Scene * scene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius, ESkinningType skinningType)
	: Pawn(scene, nullptr, pNavMesh, skinningType)
{
	m_pCollider = SphereCollider::Create(EColliderType::Static, this, colRadius, Layer::Default,
		std::bind(&Character::OnCollision, this, placeholders::_1));
	m_pCollider->SetOffset(colPosOffset);
}
Character::Character(Scene * scene, NavMesh * pNavMesh, ESkinningType skinningType)
	: Pawn(scene, nullptr, pNavMesh, skinningType)
{
	m_pCollider = nullptr;
}

Character::~Character()
{
	Object::Destroy(m_pCollider);
}

void Character::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);

	m_pMainQuestMarker = HyEngine::Billboard::Create(GetScene(), this, L"MainQuestMarker", EBillboardType::Y);
	m_pMainQuestMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"UI/StatusGauge_4.png");
	m_pMainQuestMarker->m_pTransform->SetScale(3, 3, 1);
	m_pMainQuestMarker->SetActive(false);

	m_pSubQuestMarker = HyEngine::Billboard::Create(GetScene(), this, L"SubQuestMarker", EBillboardType::Y);
	m_pSubQuestMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"UI/quest mark_question mark5_12.png");
	m_pSubQuestMarker->m_pTransform->SetScale(3, 3, 1);
	m_pSubQuestMarker->SetActive(false);

	m_pMainQuestFinishMarker = HyEngine::Billboard::Create(GetScene(), this, L"MainQuestFinishMarker", EBillboardType::Y);
	m_pMainQuestFinishMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"UI/BLUINameTag_I1_36.png");
	m_pMainQuestFinishMarker->m_pTransform->SetScale(10, 10, 1);
	m_pMainQuestFinishMarker->SetActive(false);

	m_pSubQuestFinishMarker = HyEngine::Billboard::Create(GetScene(), this, L"SubQuestFinishMarker", EBillboardType::Y);
	m_pSubQuestFinishMarker->SetDiffuseTexture(PATH->AssetsPathW() + L"UI/BLUINameTag_I1_37.png");
	m_pSubQuestFinishMarker->m_pTransform->SetScale(10, 10, 1);
	m_pSubQuestFinishMarker->SetActive(false);
}

void Character::Update()
{
	Pawn::Update();

	GameScene* pScene = static_cast<GameScene*>(SCENE);

	//юс╫ц
	if(m_pMainQuestMarker)
		m_pMainQuestMarker->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3(7, 17, 0)));
	if(m_pSubQuestMarker)
		m_pSubQuestMarker->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3(7, 17, 0)));
	if (m_pMainQuestFinishMarker)
		m_pMainQuestFinishMarker->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3(7, 17, 0)));
	if (m_pSubQuestFinishMarker)
		m_pSubQuestFinishMarker->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3(7, 17, 0)));
}

void Character::Render()
{
	Pawn::Render();
}

bool Character::IsDamaged() const
{
	return m_isDamaged;
}

bool Character::IsDied() const
{
	return m_isDied;
}

float Character::GetMoveSpeed() const
{
	return m_moveSpeed;
}

float Character::GetMaxHP() const
{
	return m_maxHP;
}

float Character::GetCurHP() const
{
	return m_curHP;
}

float Character::GetMaxMP() const
{
	return m_maxMP;
}

float Character::GetCurMP() const
{
	return m_curMP;
}

void Character::SetParams(float moveSpd, float maxHP, float maxMP)
{
	m_moveSpeed = moveSpd;
	m_maxHP = maxHP;
	m_curHP = maxHP;
	m_maxMP = maxMP;
	m_curMP = maxMP;
}

void Character::SetDamagedState(bool isDamaged)
{
	m_isDamaged = isDamaged;
}



void Character::OnDamaged(GameObject* pSender, float damage, bool isCritical)
{
}

void Character::OnDied()
{
}

void Character::OnHPChanged()
{
}

void Character::OnMPChanged()
{
}

void Character::SendDamage(GameObject * sender, float damage, bool isCritical )
{
	if (m_isDied == true)
		return;


	float resultHP = m_curHP - damage;
	if (resultHP <= 0)
	{
		m_curHP = 0;
	}
	else
		m_curHP = resultHP;
	OnHPChanged();
	if (m_curHP <= 0)
	{
		m_isDied = true;
		EventDispatcher::TriggerEvent(BattleEvent::CharacterDie, static_cast<void*>(this));
		OnDied();
	}
	else
	{
		m_isDamaged = true;
		EventDispatcher::TriggerEvent(BattleEvent::CharacterDamaged, static_cast<void*>(this));
		OnDamaged(sender, damage, isCritical);
	}
}

bool Character::UseMP(float value)
{
	if (m_isDied == true)
		return false;
	if (m_curMP <= 0)
		return false;

	OnMPChanged();

	float temp = m_curMP - value;
	if (0 >= temp)
	{
		m_curMP = 0;
		return true;
	}
	else
	{
		m_curMP -= temp;
		return true;
	}
}

void Character::ShowQuestMark(Quest * pQuest)
{
	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
	{
		m_pMainQuestMarker->SetActive(true);
	}
	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
	{
		m_pSubQuestMarker->SetActive(true);
	}
}

void Character::RemoveQuestMark(Quest * pQuest)
{
	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
	{
		m_pMainQuestMarker->SetActive(false);
	}
	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
	{
		m_pSubQuestMarker->SetActive(false);
	}
}

void Character::ShowQuestFinishMark(Quest * pQuest)
{
	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
	{
		m_pMainQuestFinishMarker->SetActive(true);
	}
	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
	{
		m_pSubQuestFinishMarker->SetActive(false);
	}
}

void Character::RemoveQuestFinishMark(Quest * pQuest)
{
	if (pQuest->GetQuestImportance() == EQuestImportance::Main)
	{
		m_pMainQuestFinishMarker->SetActive(false);
	}
	else if (pQuest->GetQuestImportance() == EQuestImportance::Sub)
	{
		m_pSubQuestFinishMarker->SetActive(false);
	}
}
