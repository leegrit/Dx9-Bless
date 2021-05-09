#include "stdafx.h"
#include "Hieracon_Cora.h"

Hieracon_Cora::Hieracon_Cora(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{
}

Hieracon_Cora::~Hieracon_Cora()
{
}

void Hieracon_Cora::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);
}

void Hieracon_Cora::Update()
{
	NonePlayer::Update();
}

std::wstring Hieracon_Cora::GetCharacterName()
{
	return L"        레오니\n<그림자 순찰대장>";
}

std::wstring Hieracon_Cora::GetSubTitle()
{
	return L"";
}

std::wstring Hieracon_Cora::GetOnlyCharacterName()
{
	return L"레오니";
}

D3DXVECTOR3 Hieracon_Cora::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 7, 10);
}
