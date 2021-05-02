#include "StandardEngineFramework.h"
#include "TitleScene.h"
#include "PathManager.h"
#include "TitleCamera.h"
#include "QuestTable.h"
void TitleScene::Update()
{
	if (KEYBOARD->Up(VK_SPACE))
	{
		ENGINE->SwitchScene(1);
	}
}

void TitleScene::Load()
{
	//////////////////////////////////////////////////////////////////////////
	// CAMERA
	//////////////////////////////////////////////////////////////////////////
	auto cam = TitleCamera::Create(this, L"TitleCamera");
	SelectCamera(L"TitleCamera");

	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/Character_Lobby_D_KSU.tga", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(WinMaxWidth, WinMaxHeight, 1), L"1");

	ScriptableData * data = ENGINE->GetScriptableData(L"QuestTable");
	if (data == nullptr)
	{
		QuestTable* table = new QuestTable();
		table->Initialize();
		ENGINE->AddScriptableData(L"QuestTable", table);
	}
	else
	{

	}

}

void TitleScene::Unload()
{
}

void TitleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void TitleScene::RenderGUI()
{
}
