#include "stdafx.h"
#include "Guido.h"

Guido::Guido(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{

}

Guido::~Guido()
{
}

void Guido::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(0);
}

void Guido::Update()
{
	NonePlayer::Update();


}

Guido * Guido::Create(Scene * pScene, std::wstring dataPath)
{
	Guido* npc = new Guido(pScene);
	npc->Initialize(dataPath);
	return npc;
}

std::wstring Guido::GetCharacterName()
{
	return L"��Ƹ�";
}

std::wstring Guido::GetSubTitle()
{
	return L"<����>";
}

std::wstring Guido::GetOnlyCharacterName()
{
	return L"��Ƹ�";
}
