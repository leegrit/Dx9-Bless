#include "stdafx.h"
#include "Liurens.h"
#include "GameScene.h"
#include "UIManager.h"
#include "SoundManager.h"

Liurens::Liurens(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Liurens::~Liurens()
{
}

void Liurens::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Liurens::Update()
{
	NonePlayer::Update();
}

std::wstring Liurens::GetCharacterName()
{
	return L"리우렌스\n<무기점 상인>";
}

std::wstring Liurens::GetSubTitle()
{
	return L"";
}

bool Liurens::DoInteract()
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	pScene->GetUIManager()->ShowEquipShopUI();

	SoundDesc desc2;
	desc2.channelMode = FMOD_LOOP_OFF;
	desc2.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc2.volume = 1;
	SOUND->PlaySound("WeaponNPC3", L"WeaponNPC3.wav", desc2);

	return true;
}

std::wstring Liurens::GetOnlyCharacterName()
{
	return L"리우렌스";
}

D3DXVECTOR3 Liurens::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
