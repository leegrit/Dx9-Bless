#include "StandardEngineFramework.h"
#include "SampleLoadingScene.h"

SampleLoadingScene::SampleLoadingScene()
	:LoadingScene()
{
}

SampleLoadingScene::~SampleLoadingScene()
{
}

void SampleLoadingScene::Update()
{
}

void SampleLoadingScene::Load()
{

}

void SampleLoadingScene::Unload()
{
}

void SampleLoadingScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void SampleLoadingScene::LateLoadScene()
{
}
