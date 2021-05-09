#include "stdafx.h"
#include "Leoni.h"

Leoni::Leoni(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Leoni::~Leoni()
{

}

void Leoni::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(0);
}

void Leoni::Update()
{
	NonePlayer::Update();
}

std::wstring Leoni::GetCharacterName()
{
	return L"코라";
}

std::wstring Leoni::GetSubTitle()
{
	return L"<그림자 순찰대장>";
}

std::wstring Leoni::GetOnlyCharacterName()
{
	return L"레오니";
}
