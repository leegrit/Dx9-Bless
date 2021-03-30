#include "stdafx.h"
#include "SampleScene.h"
#include "SampleCamera.h"
void SampleScene::Update()
{
}

void SampleScene::Load()
{
	auto camera = SampleCamera::Create(this, nullptr, L"SampleCamera");
}

void SampleScene::Unload()
{
}

void SampleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}
