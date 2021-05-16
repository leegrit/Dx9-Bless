#include "stdafx.h"
#include "Liurens.h"
#include "GameScene.h"
#include "UIManager.h"

Liurens::Liurens(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Liurens::~Liurens()
{
}

void Liurens::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Liurens::Update()
{
	NonePlayer::Update();
}

std::wstring Liurens::GetCharacterName()
{
	return L"���췻��\n<������ ����>";
}

std::wstring Liurens::GetSubTitle()
{
	return L"";
}

bool Liurens::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowEquipShopUI();
	return true;
}

std::wstring Liurens::GetOnlyCharacterName()
{
	return L"���췻��";
}

D3DXVECTOR3 Liurens::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
