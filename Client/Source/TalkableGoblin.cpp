#include "stdafx.h"
#include "TalkableGoblin.h"

TalkableGoblin::TalkableGoblin(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::HardwareSkinning)
{
}

TalkableGoblin::~TalkableGoblin()
{

}

void TalkableGoblin::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(8);
}

void TalkableGoblin::Update()
{
	NonePlayer::Update();
}

std::wstring TalkableGoblin::GetCharacterName()
{
	return L"���";
}

std::wstring TalkableGoblin::GetSubTitle()
{
	return L"<���ϴ� ���>";
}

TalkableGoblin * TalkableGoblin::Create(Scene * pScene, std::wstring dataPath)
{
	TalkableGoblin* npc = new TalkableGoblin(pScene);
	npc->Initialize(dataPath);
	return npc;
}
