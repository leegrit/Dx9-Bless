#include "stdafx.h"
#include "SkillIconUI.h"
#include "SkillProgressUI.h"
#include "PathManager.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerSkillInfo.h"

SkillIconUI::SkillIconUI(Scene * pScene, std::wstring IconFilePath, std::wstring grayIconFilePath, D3DXVECTOR3 position, int skillIndex, std::wstring name)
	:GameObject(ERenderType::None, pScene, nullptr, name)
{
	m_skillIndex = skillIndex;
	m_amount = 0;

	m_pFullEffectUI = UIPanel::Create(pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/SkillIconBase/SkillIconBase_1.png", position,
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), name + L"_Full");
	//m_pFullEffectUI->SetAlpha(0.7f);
	m_pFullEffectUI->SetRenderQueue(32800);
	m_pFillIcon = SkillProgressUI::Create(pScene, PATH->ResourcesPathW() + L"Assets/UI/black.png" /*IconFilePath*/, position, D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(45, 45, 1), name + L"_Fill");
	m_pFillIcon->SetAlpha(0.7f);
	m_pFillIcon->SetRenderQueue(2900);
	m_pFillBack = UIPanel::Create(pScene, IconFilePath /*grayIconFilePath*/, position,
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), name + L"_FillBack");
	m_pFillBack->SetRenderQueue(3000);
}

SkillIconUI::~SkillIconUI()
{
}

void SkillIconUI::Initialize()
{
	Player* pPlayer = static_cast<Player*>(PLAYER);

	m_pSkill = pPlayer->GetPlayerSkill(m_skillIndex);
	assert(m_pSkill);
}

void SkillIconUI::Update()
{

	if (m_pSkill)
	{
		m_amount = m_pSkill->GetCurCoolTime() / m_pSkill->GetCoolTime();
	}

	


	if (m_amount >= 1.0f)
	{
		m_amount = 1;
		m_pFullEffectUI->SetActive(true);
	}
	else
		m_pFullEffectUI->SetActive(false);


	PlayerSkillInfo* pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
	if (pPlayerSkillInfo->isLock[m_skillIndex] == true)
	{
		m_pFullEffectUI->SetActive(false);
		m_pFillIcon->SetActive(false);
		m_pFillBack->SetActive(false);
	}
	else
	{
		m_pFillIcon->SetActive(true);
		m_pFillBack->SetActive(true);
	}

	m_pFillIcon->SetAmount(m_amount);
}

void SkillIconUI::Render()
{
	assert(false);
}

void SkillIconUI::OnEnable()
{
	if(m_amount >= 1.0f)
		m_pFullEffectUI->SetActive(true);
	m_pFillIcon->SetActive(true);
	m_pFillBack->SetActive(true);
}

void SkillIconUI::OnDisable()
{
	m_pFullEffectUI->SetActive(false);
	m_pFillIcon->SetActive(false);
	m_pFillBack->SetActive(false);
}

SkillIconUI * SkillIconUI::Create(Scene * pScene, std::wstring IconFilePath, std::wstring grayIconFilePath, D3DXVECTOR3 position, int skillIndex, std::wstring name)
{
	SkillIconUI * ui = new SkillIconUI(pScene, IconFilePath, grayIconFilePath, position, skillIndex, name);
	ui->Initialize();
	return ui;
}
