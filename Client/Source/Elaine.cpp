#include "stdafx.h"
#include "Elaine.h"
#include "GameScene.h"
#include "UIManager.h"

Elaine::Elaine(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Elaine::~Elaine()
{
}

void Elaine::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);
	SetAnimationSet(3);
}

void Elaine::Update()
{
	NonePlayer::Update();
}

std::wstring Elaine::GetCharacterName()
{
	return L"        가가토\n<잡화 상인>";
}

std::wstring Elaine::GetSubTitle()
{
	return L"";
}

bool Elaine::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowGeneralStoreUI();
	return true;
}

std::wstring Elaine::GetOnlyCharacterName()
{
	return L"가가토";
}
