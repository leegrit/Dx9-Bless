#include "stdafx.h"
#include "Elroy.h"

Elroy::Elroy(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Elroy::~Elroy()
{
}

void Elroy::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Elroy::Update()
{
	NonePlayer::Update();


}

std::wstring Elroy::GetCharacterName()
{
	return L"        티티아나\n<기술 교관>";
}

std::wstring Elroy::GetSubTitle()
{
	return L"<기술 교관>";
}

std::wstring Elroy::GetOnlyCharacterName()
{
	return L"티티아나";
}
