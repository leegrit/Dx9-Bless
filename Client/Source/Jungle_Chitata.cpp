#include "stdafx.h"
#include "Jungle_Chitata.h"

Jungle_Chitata::Jungle_Chitata(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{
}

Jungle_Chitata::~Jungle_Chitata()
{
}

void Jungle_Chitata::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Jungle_Chitata::Update()
{
	NonePlayer::Update();
}

std::wstring Jungle_Chitata::GetCharacterName()
{
	return L"치타타\n<그림자 순찰대원>";
}

std::wstring Jungle_Chitata::GetSubTitle()
{
	return L"";
}

std::wstring Jungle_Chitata::GetOnlyCharacterName()
{
	return L"치타타";
}

D3DXVECTOR3 Jungle_Chitata::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
