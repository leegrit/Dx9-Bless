#include "stdafx.h"
#include "Elaine.h"
#include "GameScene.h"
#include "UIManager.h"
#include "SoundManager.h"

Elaine::Elaine(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Elaine::~Elaine()
{
}

void Elaine::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);
	SetAnimationSet(3);
}

void Elaine::Update()
{
	NonePlayer::Update();
}

std::wstring Elaine::GetCharacterName()
{
	return L"가가토\n<잡화 상인>";
}

std::wstring Elaine::GetSubTitle()
{
	return L"";
}

bool Elaine::DoInteract()
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

std::wstring Elaine::GetOnlyCharacterName()
{
	return L"가가토";
}

D3DXVECTOR3 Elaine::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 6, 10);
}
