#include "stdafx.h"
#include "HieraconScene.h"
#include "SampleLoadingScene.h"
#include "TitleScene.h"
#include "BlessLoadingScene.h"
#include "AncientTowerScene.h"
#include "ArbaJungleScene.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR pScmdl, int iCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	//_CrtSetBreakAlloc(6287);
	Application* application = new Application(L"Bless");

	EngineConfig engineConfig;
	engineConfig.bFullScreen = true;

	engineConfig.scenes.push_back(new TitleScene());
	engineConfig.scenes.push_back(new HieraconScene());
	engineConfig.scenes.push_back(new ArbaJungleScene());
	engineConfig.scenes.push_back(new AncientTowerScene());
	engineConfig.defaultSceneIndex = 0;
	engineConfig.loadingScene = new BlessLoadingScene();
	if (application->Init(hInst, iCmdShow, engineConfig))
	{
		application->Run();
	}
	application->Exit();

	SAFE_DELETE(application);

	return 0;
}