#include "stdafx.h"
#include "Hieracon_Cora.h"

Hieracon_Cora::Hieracon_Cora(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{
}

Hieracon_Cora::~Hieracon_Cora()
{
}

void Hieracon_Cora::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(50);
}

void Hieracon_Cora::Update()
{
	NonePlayer::Update();
}

std::wstring Hieracon_Cora::GetCharacterName()
{
	return L"�ڶ�";
}

std::wstring Hieracon_Cora::GetSubTitle()
{
	return L"<�׸��� ��������>";
}
