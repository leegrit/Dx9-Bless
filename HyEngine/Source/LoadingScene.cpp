#include "StandardEngineFramework.h"
#include "LoadingScene.h"
#include "SceneTransition.h"
#include "TextureLoader.h"

void HyEngine::LoadingScene::Update()
{
	// progress bar ����
	/*
	TODO
	ȭ�� ��ü�� load Screen���� ������
	�ε� �ٸ� �������Ѵ�.

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
