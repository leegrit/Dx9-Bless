#include "stdafx.h"
#include "BlessLoadingScene.h"
#include "TitleCamera.h"
#include "PathManager.h"
BlessLoadingScene::BlessLoadingScene()
	:LoadingScene()
{

}

BlessLoadingScene::~BlessLoadingScene()
{
}

void BlessLoadingScene::Update()
{
}

void BlessLoadingScene::Load()
{
	auto cam = TitleCamera::Create(this, L"TitleCamera");
	SelectCamera(L"TitleCamera");

	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/BLUIWarCitadelOwnership_I4E_0.png", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(WinMaxWidth, WinMaxHeight, 1), L"1");
}

void BlessLoadingScene::Unload()
{
}

void BlessLoadingScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void BlessLoadingScene::LateLoadScene()
{
}
