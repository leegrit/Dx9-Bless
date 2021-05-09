#include "stdafx.h"
#include "EnemyScreenHPBar.h"
#include "PathManager.h"
#include "ProgressBar.h"
#include "Enemy.h"


EnemyScreenHPBar::EnemyScreenHPBar(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr ,name)
{

}

EnemyScreenHPBar::~EnemyScreenHPBar()
{
}

void EnemyScreenHPBar::Initialize()
{
	m_pIcon = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/EnemyHP/BLUITarget_I11_3.png",
		D3DXVECTOR3(-197.6, 252.24 + 50, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"EnemyScreenHPBar_Icon");

	m_pFillBack = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/EnemyHP/BLUITarget_I11_1.png",
		D3DXVECTOR3(0, 247.2 + 50, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(350, 15, 1),
		L"EnemyScreenHPBar_FillBack");

	m_pBloodMark = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/EnemyHP/BLUITarget_I11_4.png",
		D3DXVECTOR3(-28, 245.6 + 50, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(441.2, 60, 1),
		L"EnemyScreenHPBar_BloodMark");

	m_pFill = ProgressBar::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/EnemyHP/BLUITarget_I11_0.png",
		D3DXVECTOR3(-9.5, 246.5 +50, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(330, 5, 1),
		L"EnemyScreenHPBar_Fill");

	m_pIcon->SetActive(false);
	m_pFillBack->SetActive(false);
	m_pBloodMark->SetActive(false);
	m_pFill->SetActive(false);

}

void EnemyScreenHPBar::Update()
{
	if (m_bShow == false)
		return;

	float amount = m_pFocusedEnemy->GetCurHP() / m_pFocusedEnemy->GetMaxHP();
	m_pFill->SetAmount(amount);

	ENGINE->DrawTextW(std::to_wstring( m_pFocusedEnemy->GetLevel()).c_str(), D3DXVECTOR3(304.5, 75.5, 0), D3DXVECTOR3(1.2f, 1.2f, 1.2f), D3DXCOLOR(1, 1, 1, 1));

	if (amount == 1)
	{
		ENGINE->DrawTextW(m_pFocusedEnemy->GetCharacterName().c_str(), D3DXVECTOR3(454, 53, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		m_pBloodMark->SetAlpha(0);
	}
	else
	{
		ENGINE->DrawTextW(m_pFocusedEnemy->GetCharacterName().c_str(), D3DXVECTOR3(454, 53, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(0.8, 0, 0, 1));

	
	
		if (m_bFadeIn == true)
		{
			m_curAlpha += TIMER->getDeltaTime() * 3;

			if (m_curAlpha >= 1)
			{
				m_curAlpha = 1;
				m_bFadeIn = false;
			}
		}
		else if (m_bFadeIn == false)
		{
			m_curAlpha -= TIMER->getDeltaTime() * 0.6f;
			if (m_curAlpha <= 0)
			{
				m_curAlpha = 0;
				m_bFadeIn = true;
			}
		}
		m_pBloodMark->SetAlpha(m_curAlpha);
	}

	m_lastAmount = amount;
}

void EnemyScreenHPBar::Render()
{
	assert(false);
}

void EnemyScreenHPBar::Show(GameObject * pFocusedEnemy)
{
	m_bShow = true;
	m_pIcon->SetActive(true);
	m_pFillBack->SetActive(true);
	m_pBloodMark->SetActive(true);
	m_pFill->SetActive(true);

	m_pFocusedEnemy = static_cast<Enemy*>( pFocusedEnemy);
}

void EnemyScreenHPBar::Hide()
{
	m_bShow = false;
	m_pIcon->SetActive(false);
	m_pFillBack->SetActive(false);
	m_pBloodMark->SetActive(false);
	m_pFill->SetActive(false);
	m_pFocusedEnemy = nullptr;
}

EnemyScreenHPBar * EnemyScreenHPBar::Create(Scene * pScene, std::wstring name)
{
	EnemyScreenHPBar * ui = new EnemyScreenHPBar(pScene, name);
	ui->Initialize();
	return ui;
}
