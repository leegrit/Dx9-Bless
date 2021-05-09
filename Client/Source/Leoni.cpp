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

	SetAnimationSet(3);
}

void Leoni::Update()
{
	NonePlayer::Update();
}

std::wstring Leoni::GetCharacterName()
{
	return L"�ڶ�";
}

std::wstring Leoni::GetSubTitle()
{
	return L"<�׸��� ��������>";
}

std::wstring Leoni::GetOnlyCharacterName()
{
	return L"������";
}

D3DXVECTOR3 Leoni::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 5, 10);
}
