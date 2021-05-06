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
	return L"������";
}

std::wstring Elaine::GetSubTitle()
{
	return L"<��ȭ ����>";
}

bool Elaine::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowGeneralStoreUI();
	return true;
}
