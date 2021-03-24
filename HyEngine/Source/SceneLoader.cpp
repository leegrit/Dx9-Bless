#include "StandardEngineFramework.h"
#include "SceneLoader.h"

HyEngine::SceneLoader::SceneLoader()
{
	m_isFinished = false;
	m_currentLoadCount = 0;
	m_totalLoadCount = 0;
}

HyEngine::SceneLoader::~SceneLoader()
{
	WaitForSingleObject(m_threadHandle, INFINITE);
	CloseHandle(m_threadHandle);
}

void HyEngine::SceneLoader::LoadAsync(Scene * scene)
{
	assert(m_isFinished == false);
	m_pCurrentLoadingScene = scene;

	m_threadHandle = (HANDLE)_beginthreadex(0, 0, ThreadMain, this, 0, 0);
	assert(m_threadHandle != nullptr);
}

unsigned HyEngine::SceneLoader::ThreadMain(void * pArg)
{
	auto sceneLoader = (SceneLoader*)pArg;
	assert(sceneLoader != nullptr);
	assert(sceneLoader->m_pCurrentLoadingScene != nullptr);
	assert(sceneLoader->m_isFinished == false);


	// TODO : CriticalSection

	// �� scene ������ LoadAsync �Լ�����
	// ���ҽ� �ε��� ������ �ݹ��Լ��� ���� ���� �ε�� ������ �� ������ �Ѱ��ش�.
	sceneLoader->m_pCurrentLoadingScene->LoadAsync([&](int currentCount, int totalCount)->void
	{
		sceneLoader->SetCurrentLoadCount(currentCount);
		sceneLoader->SetTotalLoadCount(totalCount);
	});
	sceneLoader->m_isFinished = true;

	_endthreadex(0);
	return 0;
}
