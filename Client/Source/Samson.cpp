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
	return L"ġŸŸ\n<�׸��� �������>";
}

std::wstring Samson::GetSubTitle()
{
	return L"";
}

std::wstring Samson::GetOnlyCharacterName()
{
	return L"ġŸŸ";
}

D3DXVECTOR3 Samson::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
