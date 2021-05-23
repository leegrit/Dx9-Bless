#include "stdafx.h"
#include "HGoblin.h"
#include "HGoblinAttack.h"
#include "HGoblinDie.h"
#include "HGoblinDied.h"
#include "HGoblinHit.h"
#include "HGoblinIdle.h"
#include "HGoblinMove.h"
#include "NameFont.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "CinematicManager.h"
#include "QuestManager.h"
#include "Quest.h"
#include "UpdateDispatcher.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "MeshEffect.h"
#include "HGoblinAttack2.h"
#include "HGoblinSkAttack.h"


HGoblin::HGoblin(Scene * pScene, NavMesh * pNavMesh)
	: NamedEnemy(pScene, pNavMesh,D3DXVECTOR3(0, 15, 0), 10, ESkinningType::SoftwareSkinning)
{
	EventDispatcher::AddEventListener(QuestEvent::QuestAccept, std::to_string(GetInstanceID()),
		std::bind(&HGoblin::OnQuestAccept, this, placeholders::_1));

}

HGoblin::~HGoblin()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestAccept, std::to_string(GetInstanceID()));
	m_state.Release();
}

void HGoblin::Initialize(std::wstring dataPath)
{
	NamedEnemy::Initialize(dataPath);

	SetParams(10, 3000, 100);

	GameScene* pScene = static_cast<GameScene*>(GetScene());

	MeshEffectDesc swingDownEffectDesc;
	swingDownEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_cdwarrtrail_010_SM_CJH.X";
	swingDownEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	swingDownEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_004_TEX_CJH.tga";
	swingDownEffectDesc.fadeOut = true;
	swingDownEffectDesc.fadeOutFactor = 0.5f;
	swingDownEffectDesc.lifeTime = 1.0f;
	swingDownEffectDesc.isUVAnim = true;
	swingDownEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	swingDownEffectDesc.uvSpeed = 1;
	m_pSwingDownEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"SwingDownEffect", swingDownEffectDesc);
	m_pSwingDownEffect->SetRenderEffectOption(RenderEffectOption::Bloom);

	MeshEffectDesc swingEffectDesc;
	swingEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_cdwarrtrail_005_SM_CJH.X";
	swingEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	swingEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Firedust_01_Xclamp.tga";
	swingEffectDesc.fadeOut = true;
	swingEffectDesc.fadeOutFactor = 0.5f;
	swingEffectDesc.lifeTime = 1.0f;
	swingEffectDesc.isUVAnim = true;
	swingEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	swingEffectDesc.uvSpeed = 1;
	m_pSwingEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"SwingEffect", swingEffectDesc);
	m_pSwingEffect->SetRenderEffectOption(RenderEffectOption::Bloom);


	MeshEffectDesc skSwingDownEffectDesc;
	skSwingDownEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_cdwarrtrail_010_SM_CJH.X";
	skSwingDownEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	skSwingDownEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_004_TEX_CJH.tga";
	skSwingDownEffectDesc.fadeOut = true;
	skSwingDownEffectDesc.fadeOutFactor = 0.5f;
	skSwingDownEffectDesc.lifeTime = 1.0f;
	skSwingDownEffectDesc.isUVAnim = true;
	skSwingDownEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	skSwingDownEffectDesc.uvSpeed = 1;
	m_pSKSwingDownEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"SKSwingDownEffect", skSwingDownEffectDesc);
	m_pSKSwingDownEffect->SetRenderEffectOption(RenderEffectOption::Bloom);

	MeshEffectDesc skSwingEffectDesc;
	skSwingEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_cdwarrtrail_005_SM_CJH.X";
	skSwingEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	skSwingEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Firedust_01_Xclamp.tga";
	skSwingEffectDesc.fadeOut = true;
	skSwingEffectDesc.fadeOutFactor = 0.5f;
	skSwingEffectDesc.lifeTime = 1.0f;
	skSwingEffectDesc.isUVAnim = true;
	skSwingEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	skSwingEffectDesc.uvSpeed = 1;
	m_pSKSwingEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"SKSwingEffect", skSwingEffectDesc);
	m_pSKSwingEffect->SetRenderEffectOption(RenderEffectOption::Bloom);


	m_state.Add<HGoblinAttack>(this, "Attack");
	m_state.Add<HGoblinAttack2>(this, "Attack2");
	m_state.Add<HGoblinSkAttack>(this, "SKAttack");
	m_state.Add<HGoblinDie>(this, "Die");
	m_state.Add<HGoblinHit>(this, "Hit");
	m_state.Add<HGoblinIdle>(this, "Idle");
	m_state.Add<HGoblinMove>(this, "Move");
	m_state.Add<HGoblinDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"홉 고블린", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 16, 0), -40, D3DXCOLOR(1, 1, 0, 1));

	ShowHPBar();
}

void HGoblin::Update()
{
	NamedEnemy::Update();

	if (m_isActiveFSM)
	{
		m_state.Update();
	}

	m_pSwingDownEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, -6))
	);
	m_pSwingDownEffect->SetOriginRot
	(
		m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(-22, -90, 0)
	);
	m_pSwingDownEffect->SetOriginScale(D3DXVECTOR3(1, 1, 1));

	m_pSwingEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(-5, -2, 0))
	);
	m_pSwingEffect->SetOriginRot
	(
		m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0,12)
	);
	m_pSwingEffect->SetOriginScale(D3DXVECTOR3(1, 1, 1));

	m_pSKSwingDownEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, -6))
	);
	m_pSKSwingDownEffect->SetOriginRot
	(
		m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -90, 0)
	);
	m_pSKSwingDownEffect->SetOriginScale(D3DXVECTOR3(1, 1, 1));

	m_pSKSwingEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(9.4, 28, 0))
	);
	m_pSKSwingEffect->SetOriginRot
	(
		m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(6, 0, 180)
	);
	m_pSKSwingEffect->SetOriginScale(D3DXVECTOR3(1, 1, 1));
}

void HGoblin::Render()
{
	NamedEnemy::Render();

	m_pNameFont->RenderFont();
}

UINT HGoblin::GetTargetLayer()
{
	return Layer::Player;
}

void HGoblin::OnCollision(Collider * other)
{
}

int HGoblin::GetAttackCount()
{
	return 1;
}

Collider * HGoblin::GetAttackCollider(int attackIndex)
{
	Collider * pAttackCollider = nullptr;
	if (attackIndex == 0)
	{
		pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
			std::bind(&HGoblin::OnHitOthers, this, placeholders::_1));
		pAttackCollider->SetOffset(D3DXVECTOR3(0, 0, 10));
	}
	else /* 한종류밖에 없음 */
		assert(false);

	return pAttackCollider;
}

void HGoblin::OnHitOthers(Collider * other)
{
	AddHitOthers(other->GetGameObject());
}

float HGoblin::GetFocusColliderSize()
{
	return 20.0f;
}

D3DXVECTOR3 HGoblin::GetFocusUIOffset()
{
	return D3DXVECTOR3(0, 10, 0);
}

int HGoblin::GetLevel()
{
	return 30;
}

std::wstring HGoblin::GetCharacterName()
{
	return L"홉 고블린";
}

void HGoblin::OnQuestAccept(void * pQuestIndex)
{
	int index = *static_cast<int*>(pQuestIndex);
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	Quest * pQuest = pScene->GetQuestManager()->GetQuest(index);
	if (pQuest->GetQuestName().compare(L"말하는 고블린") == 0)
	{
		
		UpdateDispatcher::Dispatch([&]()->UpdateDispatcher::UpdateState 
		{
			m_elapsed += TIMER->getDeltaTime();
			if (m_elapsed >= m_cinematicDelay)
			{
				m_isPlayCinematic = true;
				GameScene* pScene = static_cast<GameScene*>(SCENE);
				pScene->GetCinematicManager()->PlayCinematic(L"HGoblinCinematic");


				return UpdateDispatcher::UpdateState::End;
			}
			return UpdateDispatcher::UpdateState::Continue;
		}, []() {});
	}
}

void HGoblin::StopFSM()
{
	m_isActiveFSM = false;
}

void HGoblin::PlayFSM()
{
	m_isActiveFSM = true;
}

HGoblin * HGoblin::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	HGoblin* boss = new HGoblin(pScene, pNavMesh);
	boss->Initialize(dataPath);
	return boss;
}
