#include "stdafx.h"
#include "Elaine.h"
#include "GameScene.h"
#include "UIManager.h"

Elaine::Elaine(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{

}

Elaine::~Elaine()
{
}

void Elaine::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);
	SetAnimationSet(50);
}

void Elaine::Update()
{
	NonePlayer::Update();
}

std::wstring Elaine::GetCharacterName()
{
	return L"엘레인";
}

std::wstring Elaine::GetSubTitle()
{
	return L"<잡화 상인>";
}

bool Elaine::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowGeneralStoreUI();
	return true;
}
