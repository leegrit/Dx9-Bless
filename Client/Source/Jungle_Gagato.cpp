#include "stdafx.h"
#include "Jungle_Gagato.h"
#include "GameScene.h"
#include "UIManager.h"
#include "SoundManager.h"

Jungle_Gagato::Jungle_Gagato(Scene * pScene)
	:NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{
}

Jungle_Gagato::~Jungle_Gagato()
{
}

void Jungle_Gagato::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);
	SetAnimationSet(3);
}

void Jungle_Gagato::Update()
{
	NonePlayer::Update();
}

std::wstring Jungle_Gagato::GetCharacterName()
{
	return L"가가토\n<잡화 상인>";
}

std::wstring Jungle_Gagato::GetSubTitle()
{
	return L"";
}

bool Jungle_Gagato::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowGeneralStoreUI();

	SoundDesc desc2;
	desc2.channelMode = FMOD_LOOP_OFF;
	desc2.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc2.volume = 1;
	SOUND->PlaySound("AccNPC1", L"AccNPC1.wav", desc2);
	return true;
}

std::wstring Jungle_Gagato::GetOnlyCharacterName()
{
	return L"가가토";
}

D3DXVECTOR3 Jungle_Gagato::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 6, 10);
}
