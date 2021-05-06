#include "stdafx.h"
#include "Elroy.h"

Elroy::Elroy(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{

}

Elroy::~Elroy()
{
}

void Elroy::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(50);
}

void Elroy::Update()
{
	NonePlayer::Update();


}

std::wstring Elroy::GetCharacterName()
{
	return L"엘로이";
}

std::wstring Elroy::GetSubTitle()
{
	return L"<기술 교관>";
}
