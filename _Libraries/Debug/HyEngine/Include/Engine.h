#pragma once


struct EngineDesc
{
	std::vector<Scene*> scenes;
};

struct FontInfo
{
	TCHAR textBuff[256];
	D3DXMATRIX matTrans;
	D3DCOLOR textColor;
};
namespace HyEngine
{
	class ENGINE_DLL Engine
	{
		friend class Application;

		DECLARE_SINGLETON(Engine)
	private:
		Engine();
		~Engine();

	public:
		bool Initialize(HWND hWnd, EngineConfig engineConfig);
		void Exit();

		// Load the required resources
		bool Load();

		// The basic Logic works in this function.
		void SimulateFrame();
		// The basic Render works in this function.
		void RenderFrame();

		// Engine Pause
		inline void Pause() { m_bIsPaused = true; }
		inline void Unpause() { m_bIsPaused = false; }

		// Input
		inline IO::Mouse* GetMouse() const { return m_pMouse; }
		inline IO::Keyboard* GetKeyboard() const { return m_pKeyboard; }
		inline Timer* GetTimer() const { return m_pTimer; }
	public:
		class Scene* GetActiveScene();
		void SwitchScene(int sceneNumber);
		void ShowLoadingScene(class SceneTransition* sceneTransiion);
		void HideLoadingScene();

		void AddScriptableData(std::wstring key, class ScriptableData* data);
		class ScriptableData* GetScriptableData(std::wstring key);

		void DrawText(const TCHAR* text, D3DXVECTOR3 position , D3DXVECTOR3 scale, D3DCOLOR color);
		void DrawTextFormat(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, const TCHAR* text, int args, ... );

		/* For Shader */
	public :
		bool InsertShader(std::wstring key, std::wstring path);
		bool TryGetShader(std::wstring key, _Out_ ID3DXEffect** ppShader);
	private:


		// ???? ???̴? > ?
		bool LoadShaders();

		void LoadScenes();


		//void RenderUI();
		void RenderDebug();
		void RenderFont();


		bool inline IsLoading() const { return m_bLoading; }


		// TOGGLES
		void inline TogglePause() { m_bIsPaused = !m_bIsPaused; }
	private:
		// static 
		static Settings::Engine sEngineSettigns;

		IO::Keyboard *m_pKeyboard;
		IO::Mouse *m_pMouse;
		Timer *m_pTimer;

		//class Camera* m_pCamera;
	private:

		// engine state
		bool m_bIsPaused;

		int m_currentLevel;
		// THREADED LOADING
		bool m_bLoading;

	private:

		class Renderer * m_pRenderer;

		EngineConfig engineConfig;
		class Scene* m_pActiveScene;
		class LoadingScene* m_pLoadingScene;
		std::vector<Scene*> m_scenes;
		class SceneTransition* m_pSceneTransition = nullptr;

	private :
		std::queue<std::function<void()>> m_eventQueue;
		std::unordered_map<std::wstring, class ScriptableData*> m_scriptableDatas;

		std::vector<FontInfo> m_fontInfos;

		/* For Shader */
		std::unordered_map<std::wstring, ID3DXEffect*> m_shaderMap;
	};

}