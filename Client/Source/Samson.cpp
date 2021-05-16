#include "stdafx.h"
#include "Samson.h"

Samson::Samson(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{
}

Samson::~Samson()
{
}

void Samson::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Samson::Update()
{
	NonePlayer::Update();
}

std::wstring Samson::GetCharacterName()
{
	return L"치타타\n<그림자 순찰대원>";
}

std::wstring Samson::GetSubTitle()
{
	return L"";
}

std::wstring Samson::GetOnlyCharacterName()
{
	return L"치타타";
}

D3DXVECTOR3 Samson::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
