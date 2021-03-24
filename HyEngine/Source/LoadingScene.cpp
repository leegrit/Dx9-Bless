#include "StandardEngineFramework.h"
#include "LoadingScene.h"
#include "SceneTransition.h"
#include "TextureLoader.h"

void HyEngine::LoadingScene::Update()
{
	// progress bar 조정
	/*
	TODO
	화면 전체를 load Screen으로 가리고
	로딩 바를 만들어야한다.

	*/
}

void HyEngine::LoadingScene::Load()
{
}

void HyEngine::LoadingScene::Unload()
{
}

void HyEngine::LoadingScene::LoadAsync(std::function<void(int, int)> onProgress)
{	

}

void HyEngine::LoadingScene::LateLoadScene()
{
}

void HyEngine::LoadingScene::Initialize()
{
}

void HyEngine::LoadingScene::SetSceneTransition(SceneTransition * sceneTransition)
{
	this->m_pSceneTransition = sceneTransition;
}
