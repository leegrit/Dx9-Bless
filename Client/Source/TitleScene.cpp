#include "StandardEngineFramework.h"
#include "TitleScene.h"
#include "PathManager.h"
#include "TitleCamera.h"
#include "QuestTable.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "LightObject.h"

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
	//LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/DirectionalLight.json");

	/*m_pLogo = Sprite::Create(this, L"Sprite",
		PATH->AssetsPathW() + L"Logo/Bless", ELoopType::Infinity, 90, 10);
	m_pLogo->PlayAnimation();

	m_pLogo->m_pTransform->m_position = D3DXVECTOR3(0, 2.3f, -1);
	m_pLogo->m_pTransform->m_scale = D3DXVECTOR3(15, 7, 1);*/
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

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_NORMAL;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("TitleBGM",L"Warploading.mp3",  desc);

}

void TitleScene::Unload()
{
	SOUND->StopAll();
}

void TitleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void TitleScene::RenderGUI()
{
}
