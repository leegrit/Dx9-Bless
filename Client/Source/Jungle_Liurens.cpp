#include "stdafx.h"
#include "Jungle_Liurens.h"
#include "GameScene.h"
#include "UIManager.h"
#include "SoundManager.h"

Jungle_Liurens::Jungle_Liurens(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Jungle_Liurens::~Jungle_Liurens()
{
}

void Jungle_Liurens::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);
	SetAnimationSet(3);
}

void Jungle_Liurens::Update()
{
	NonePlayer::Update();
}

std::wstring Jungle_Liurens::GetCharacterName()
{
	return L"리우렌스\n<무기점 상인>";
}

std::wstring Jungle_Liurens::GetSubTitle()
{
	return L"";
}

bool Jungle_Liurens::DoInteract()
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

std::wstring Jungle_Liurens::GetOnlyCharacterName()
{
	return L"리우렌스";
}

D3DXVECTOR3 Jungle_Liurens::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
