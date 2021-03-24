#include "StandardEngineFramework.h"
#include "SceneTransition.h"
#include "UpdateDispatcher.h"
using namespace HyEngine;

void HyEngine::SceneTransition::Transit(Scene* currentScene, Scene * nextScene, std::function<void()> onCompleted)
{
	// 로딩중에 또 호출하면 안됨
	assert(m_bLoading == false);
	m_bLoading = true;

	if (currentScene)
		currentScene->UnloadScene();
	ENGINE->ShowLoadingScene(this);


	 m_pLoader = new SceneLoader();

	 m_pLoader->LoadAsync(nextScene);
	UpdateDispatcher::Dispatch([&]()->UpdateDispatcher::UpdateState
	{
		assert(m_pLoader != nullptr);
		LoadingScene* loadingScene = dynamic_cast<LoadingScene*>(Engine::Get()->GetActiveScene());
		assert(loadingScene != nullptr);

		loadingScene->UpdateLoadInfo(m_pLoader->GetCurrentLoadCount(), m_pLoader->GetTotalLoadCount());

		if (m_pLoader->IsFinished())
		{
			// update 종료 
			return UpdateDispatcher::End;
		}
		return UpdateDispatcher::Continue;
	}, [=]() // on Completed
	{
		ENGINE->HideLoadingScene();
		onCompleted();
		// 모두 완료되면 정리해줌
		SAFE_DELETE(m_pLoader);
		m_bLoading = false;
		m_currentLoadCount = 0;
		m_totalLoadCount = 0;
	});
}
