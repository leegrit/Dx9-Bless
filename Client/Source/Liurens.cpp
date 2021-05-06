#include "stdafx.h"
#include "Liurens.h"
#include "GameScene.h"
#include "UIManager.h"

Liurens::Liurens(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{

}

Liurens::~Liurens()
{
}

void Liurens::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(50);
}

void Liurens::Update()
{
	NonePlayer::Update();
}

std::wstring Liurens::GetCharacterName()
{
	return L"리우렌스";
}

std::wstring Liurens::GetSubTitle()
{
	return L"무기점 상인";
}

bool Liurens::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowEquipShopUI();
	return true;
}
