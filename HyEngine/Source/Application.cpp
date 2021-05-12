#include "StandardEngineFramework.h"
#include "Application.h"
#include "Gui.h"

HWND g_hWnd;

Application::Application(LPCWSTR appName)
	: 
	m_appName(appName),
	m_bAppWantsExit(false),
	m_dt(1 / (double)60),
	m_maxSkipFrames(10)
{
	// LOG
	InitLoggingService();

	Engine::Create();

}


Application::~Application()
{
	Gui::Destroy();
	Engine::Destroy();
}

bool Application::Init(HINSTANCE hInstance, int nCmdShow, EngineConfig engineConfig)
{
	m_hInstance = hInstance;



	
	// WINDOW
	InitWindow();
	ShowWindow(m_hWnd, nCmdShow);

	// ENGINE
	ENGINE->Initialize(m_hWnd, engineConfig);
	Gui::Create();
	ENGINE->Load();


	return true;
}

void Application::Run()
{
	TIMER->reset();
	double accumulatedTime = 0.0f;
	int nLoops = 0;

	MSG msg = {};

	while (!m_bAppWantsExit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			if (KEYBOARD->Up(VK_ESCAPE))
			{
				{
					m_bAppWantsExit = true;
				}
			}

			if (msg.message == WM_QUIT/* && !ENGINE->IsLoading()*/)
			{
				m_bAppWantsExit = true;
			}

			TIMER->tick();
			//std::cout << TIMER->getDeltaTime() << std::endl;
			if (!ENGINE->m_bIsPaused)
			{
				// compute fps
				CalculateFrameStatistics();

				// accumulate the elapsed time since the last frame
				accumulatedTime += TIMER->getUnscaleDeltaTime();

				if (accumulatedTime >= m_dt)
				{
					//accumulatedTime -= m_dt;
					accumulatedTime = 0;
					ENGINE->SimulateFrame();
					ENGINE->RenderFrame();
				}
				//ENGINE->RenderFrame();
	// 			nLoops = 0;
	// 			while (accumulatedTime >= m_dt && nLoops < m_maxSkipFrames)
	// 			{
	// 				ENGINE->SimulateFrame();
	// 
	// 				accumulatedTime -= m_dt;
	// 				nLoops++;
	// 			}

				// peek into the future and generate the output
				//ENGINE->RenderFrame();
			}
		}
	}

}

void Application::Exit()
{
	ENGINE->Exit();
	ShutdownWindows();
}

LRESULT Application::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	const Settings::Window& settings = Engine::sEngineSettigns.window;

	switch (umsg)
	{
	case WM_CLOSE :
		// Log 
		m_bAppWantsExit = true;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		// TODO :LOG
		break;
	case WM_ACTIVATE :
		//if (LOWORD(wparam) == WA_INACTIVE)
		//{
		//	// TODO : LOG

		//	MOUSE->CaptureMouse(false);
		//	ENGINE->Pause();
		//	TIMER->stop();
		//}
		//else
		//{
		//	MOUSE->CaptureMouse(true);
		//	ENGINE->Unpause();
		//	TIMER->start();
		//}
		break;
	case WM_ENTERSIZEMOVE :
		ENGINE->Pause();
		// todo : resizing
		TIMER->stop();
		break;
	case WM_EXITSIZEMOVE:
		ENGINE->Unpause();
		// todo : resizing 
		TIMER->start();
		// TODO : ONRESIZE()
		break;
	case WM_GETMINMAXINFO :
		((MINMAXINFO*)lparam)->ptMinTrackSize.x = WinMinWidth;
		((MINMAXINFO*)lparam)->ptMinTrackSize.y = WinMinHeight;
		break;
	/*case WM_SETCURSOR:
		SetCursor(NULL);

		break;*/
	/*case WM_MOUSEMOVE :
		POINT	ptMouse = { WinMaxWidth >> 1, WinMaxHeight >> 1 };

		ClientToScreen(g_hWnd, &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);
		break;*/
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	MOUSE->InputProc(umessage, wparam, lparam);
	Gui::Get()->MsgProc(hwnd, umessage, wparam, lparam);
	switch (umessage)
	{
	case WM_DESTROY:	// Check if the window is being destroyed.
		PostQuitMessage(0);
		return 0;
		
	case WM_QUIT:		// Check if the window is being closed.
		PostQuitMessage(0);
		return 0;
	default: // All other messages pass to the message handler in the system class.
		return g_pAppHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	//return DefWindowProc(hwnd, umessage, wparam, lparam);
}


void Application::UpdateWindowDimensions(int w, int h)
{
	m_windowHeight = h;
	m_windowWidth = w;
}

void Application::InitWindow()
{
	g_pAppHandle = this;
	
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = m_appName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);


	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

#ifdef FULL_SCREEN
	m_hWnd = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		m_appName,
		m_appName,
		WS_EX_TOPMOST | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		0,//CW_USEDEFAULT,
		0, //CW_USEDEFAULT,
		WinMaxWidth,//CW_USEDEFAULT,
		WinMaxHeight,//CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		m_hInstance,
		NULL
	);
#else
	RECT		rc{ 0, 0, WinMaxWidth, WinMaxHeight };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


	m_hWnd = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		m_appName,
		m_appName,
		/*WS_CLIPSIBLINGS | WS_CLIPCHILDREN | */WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		(HMENU)NULL,
		m_hInstance,
		NULL
	);

#endif

	/*RECT rect = { 0, 0, (LONG)WinMaxWidth, (LONG)WinMaxHeight };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)WinMaxWidth) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)WinMaxHeight) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	MoveWindow
	(
		m_hWnd,
		centerX, centerY,
		rect.right - rect.left, rect.bottom - rect.top,
		true
	);*/

	ShowWindow(m_hWnd, SW_SHOWNORMAL);//윈도우창을 보이게해주는것
	SetForegroundWindow(m_hWnd);//실행시켰을때 제일위로 올라오게하는것
	SetFocus(m_hWnd);//포커스 , 키보드나 마우스를 눌렀을때 조작이되는창.

	ShowCursor(true);

	::g_hWnd = m_hWnd;
}

void Application::ShutdownWindows()
{
	ShowCursor(true);
	 ServiceLocator::Clear();
	if (Engine::sEngineSettigns.window.fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_appName, m_hInstance);
	m_hInstance = NULL;

	// Release the pointer to this class.
	g_pAppHandle = nullptr;

	return;
}

void Application::CalculateFrameStatistics()
{
	static int nFrames;				    // number of frames seen
	static double elapsedTime;		    // time since last call
	nFrames++;

	// compute average statistics over one second
	if ((TIMER->getTotalTime() - elapsedTime) >= 1.0)
	{
		// set fps and mspf
		m_fps = nFrames;
		m_mspf = 1000.0 / (double)m_fps;

		// reset
		nFrames = 0;
		elapsedTime += 1.0;
	}
	ENGINE->SetFPS(m_fps);
}

void Application::InitLoggingService()
{
	// create file Logger
	std::shared_ptr<Logger<FileLogPolicy >> engineLogger = 
		std::make_shared<Logger<FileLogPolicy >>(L"engine.log");

	// set name of current thread
	engineLogger->setThreadName("mainThread");

	// register the logging service
	 ServiceLocator::provideFileLoggingService(engineLogger);


#ifdef _DEBUG
	// print starting message
	 ServiceLocator::getFileLogger()->print<SeverityType::info>("The file logger was created successfully.");
#endif
}
