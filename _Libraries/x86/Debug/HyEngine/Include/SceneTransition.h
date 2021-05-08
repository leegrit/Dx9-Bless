#pragma once
#include "SceneLoader.h"
namespace HyEngine
{
	class SceneTransition
	{
	public:
		void Transit(Scene* currentScene, Scene* nextScene, std::function<void()> onCompleted);
		inline void SetCurrentLoadCount(int count) { assert(m_pLoader != nullptr); m_pLoader->SetCurrentLoadCount(count); }
		inline void SetTotalLoadCount(int count) { assert(m_pLoader != nullptr); m_pLoader->SetTotalLoadCount(count); }
		inline int GetCurrentLoadCount() const { assert(m_pLoader != nullptr); return m_pLoader->GetCurrentLoadCount(); }
		inline int GetTotalLoadCount() const { assert(m_pLoader != nullptr); return m_pLoader->GetTotalLoadCount(); }
		inline float GetProgressRate() const { assert(m_pLoader != nullptr); m_pLoader->GetProgressRate(); }
		inline bool IsLoading() { return m_bLoading; }
	private :
		int m_currentLoadCount;
		int m_totalLoadCount;
		class SceneLoader* m_pLoader = nullptr;
		bool m_bLoading = false;
	};
}

