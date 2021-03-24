#pragma once



namespace HyEngine
{
	// �� Ŭ������ ��ȸ���̴�.
	// Scene �ε��� �� ��� �� �������� �Ǹ� ����������Ѵ�.
	// �� ����ϸ� �ȵ�
	class SceneLoader
	{
	public :
		SceneLoader();
		~SceneLoader();
		inline bool IsFinished()const { return m_isFinished; }
		inline void SetCurrentLoadCount(int count) { m_currentLoadCount = count; }
		inline void SetTotalLoadCount(int count) { m_totalLoadCount = count; }
		inline int GetCurrentLoadCount() const { return m_currentLoadCount; }
		inline int GetTotalLoadCount() const { return m_totalLoadCount; }
		inline float GetProgressRate() const { return m_totalLoadCount ? (float)m_currentLoadCount / m_totalLoadCount : 0; }
		void LoadAsync(class Scene* scene);
	private :
		static unsigned _stdcall ThreadMain(void* pArg);
	private :
		HANDLE m_threadHandle;
		class Scene* m_pCurrentLoadingScene;
		int m_currentLoadCount;
		int m_totalLoadCount;
		bool m_isFinished = false;
	};
}

