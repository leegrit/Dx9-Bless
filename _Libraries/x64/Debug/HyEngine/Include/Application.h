#pragma once


extern HWND g_hWnd;

class ENGINE_DLL Application
{
public :
	struct WorkspaceDirectories
	{
		std::wstring m_resources;
		std::wstring m_shaders;
		std::wstring m_textures;
	};

	static WorkspaceDirectories s_workSpaceDirectories;
public:
	Application(LPCWSTR appName);
	~Application();

	bool Init(HINSTANCE hInstance, int nCmdShow, EngineConfig engineConfig);
	void Run();
	void Exit();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	void UpdateWindowDimensions(int w, int h);
private :
	void InitWindow(EngineConfig config);
	void ShutdownWindows();

	void CalculateFrameStatistics();

private :
	void InitLoggingService();


private :
	LPCWSTR m_appName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	int m_windowWidth, m_windowHeight;

	// º¸·ù
	bool m_bMouseCaptured;
	bool m_bAppWantsExit;

	int m_fps;
	double m_mspf;
	const double m_dt;
	const double m_maxSkipFrames;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Application *g_pAppHandle = nullptr;