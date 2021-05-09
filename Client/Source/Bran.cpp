#include "stdafx.h"
#include "Bran.h"

Bran::Bran(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Bran::~Bran()
{
}

void Bran::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(14);
}

void Bran::Update()
{
	NonePlayer::Update();

}

std::wstring Bran::GetCharacterName()
{
	return L"        브란\n<그림자 순찰대원>";
}

std::wstring Bran::GetSubTitle()
{
	return L"";
}

Bran * Bran::Create(Scene * pScene, std::wstring dataPath)
{
	Bran* obj = new Bran(pScene);
	obj->Initialize(dataPath);
	return obj;
}

std::wstring Bran::GetOnlyCharacterName()
{
	return L"브란";
}
