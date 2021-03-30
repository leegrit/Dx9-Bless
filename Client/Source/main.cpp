#include "stdafx.h"
#include "SampleScene.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR pScmdl, int iCmdShow)
{

	Application application(L"Bless");

	EngineConfig engineConfig;

	engineConfig.scenes.push_back(new SampleScene());
	engineConfig.defaultSceneIndex = 0;

	if (application.Init(hInst, iCmdShow, engineConfig))
	{
		application.Run();
	}
	application.Exit();
	return 0;
}