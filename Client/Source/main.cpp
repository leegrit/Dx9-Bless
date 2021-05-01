#include "stdafx.h"
#include "SampleScene.h"
#include "SampleLoadingScene.h"
#include "TitleScene.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR pScmdl, int iCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	//_CrtSetBreakAlloc(6287);
	Application* application = new Application(L"Bless");

	EngineConfig engineConfig;

	engineConfig.scenes.push_back(new TitleScene());
	engineConfig.scenes.push_back(new SampleScene());
	engineConfig.defaultSceneIndex = 0;
	engineConfig.loadingScene = new SampleLoadingScene();
	if (application->Init(hInst, iCmdShow, engineConfig))
	{
		application->Run();
	}
	application->Exit();

	SAFE_DELETE(application);

	return 0;
}