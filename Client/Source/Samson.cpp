#include "stdafx.h"
#include "Samson.h"

Samson::Samson(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{
}

Samson::~Samson()
{
}

void Samson::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(50);
}

void Samson::Update()
{
	NonePlayer::Update();
}

std::wstring Samson::GetCharacterName()
{
	return L"���";
}

std::wstring Samson::GetSubTitle()
{
	return L"<�׸��� �������>";
}
