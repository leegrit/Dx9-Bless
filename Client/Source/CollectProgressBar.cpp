#include "stdafx.h"
#include "CollectProgressBar.h"
#include "PathManager.h"
#include "ProgressBar.h"
CollectProgressBar::CollectProgressBar(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

CollectProgressBar::~CollectProgressBar()
{
}

void CollectProgressBar::Initialize()
{
	m_pFillBack = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/StatusGauge_0.png",
		D3DXVECTOR3(0, -148.16, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(300, 15, 1),
		L"CollectProgressBar_FillBack");
	
	m_pFill = ProgressBar::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BossGauge_2.png",
		D3DXVECTOR3(0, -148.8, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(250, 7, 1),
		L"CollectProressBar_Fill");
}

void CollectProgressBar::Update()
{
	if (m_bShow == false)
		return;

	m_pFill->SetAmount(m_amount);
}

void CollectProgressBar::Render()
{
}

void CollectProgressBar::Show(float amount)
{
	m_bShow = true;
	m_amount = amount;

	m_pFillBack->SetActive(true);
	m_pFill->SetActive(true);
}

void CollectProgressBar::Hide()
{
	m_bShow = false;

	m_pFillBack->SetActive(false);
	m_pFill->SetActive(false);
}

CollectProgressBar * CollectProgressBar::Create(Scene * pScene, std::wstring name)
{
	CollectProgressBar * ui = new CollectProgressBar(pScene, name);
	ui->Initialize();
	return ui;
}
