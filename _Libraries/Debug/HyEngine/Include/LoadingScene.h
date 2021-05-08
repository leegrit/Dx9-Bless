#pragma once
#include "Scene.h"
namespace HyEngine
{

	class ENGINE_DLL LoadingScene : public Scene
	{
	public :
		// Inherited via Scene
		virtual void Update() override;
		virtual void Load() override;
		virtual void Unload() override;
		virtual void LoadAsync(std::function<void(int, int)> onProgress) override;

		virtual void LateLoadScene() override;

		inline void UpdateLoadInfo(int currentLoadCount, int totalCount) { m_currentLoadCount = currentLoadCount; m_totalLoadCount = totalCount; }

		void Initialize();
		void SetSceneTransition(class SceneTransition* sceneTransition);

		inline int GetCurrentLoadCount() { return m_currentLoadCount; }
		inline int GetTotalLoadCount() { return m_totalLoadCount; }
	private :
		class SceneTransition* m_pSceneTransition;
		std::vector<IDirect3DTexture9* > m_textures;

	protected:
		int m_currentLoadCount= 0;
		int m_totalLoadCount = 0;
	};

}

