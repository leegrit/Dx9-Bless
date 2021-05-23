#include "stdafx.h"
#include "SummonProgressBar.h"
#include "PathManager.h"
#include "ProgressBar.h"

SummonProgressBar::SummonProgressBar(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{

}

SummonProgressBar::~SummonProgressBar()
{
}

void SummonProgressBar::Initialize()
{
	m_pFillBack = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/StatusGauge_0.png",
		D3DXVECTOR3(0, -148.16 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(300, 15, 1),
		L"SummonProgressBar_FillBack");

	m_pFill = ProgressBar::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BossGauge_2.png",
		D3DXVECTOR3(0, -148.8 - 60, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(250, 7, 1),
		L"SummonProgressBar_Fill");
}

void SummonProgressBar::Update()
{
	if (m_bShow == false)
		return;

	m_pFill->SetAmount(m_amount);
}

void SummonProgressBar::Render()
{
}

void SummonProgressBar::Show(float amount)
{
	m_bShow = true;
	m_amount = amount;

	m_pFillBack->SetActive(true);
	m_pFill->SetActive(true);
}

void SummonProgressBar::Hide()
{
	m_bShow = false;

	m_pFillBack->SetActive(false);
	m_pFill->SetActive(false);
}

SummonProgressBar * SummonProgressBar::Create(Scene * pScene, std::wstring name)
{
	SummonProgressBar * ui = new SummonProgressBar(pScene, name);
	ui->Initialize();
	return ui;
}
