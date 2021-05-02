#include "stdafx.h"
#include "SampleNPC.h"
#include "Billboard.h"
#include "TestQuest.h"

SampleNPC::SampleNPC(Scene * pScene)
	: NonePlayer(pScene)
{
}

SampleNPC::~SampleNPC()
{
}

void SampleNPC::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);


	SetAnimationSet(50);


}

void SampleNPC::QuestInitialize()
{
	NonePlayer::QuestInitialize();

	TestQuest * testQuest = new TestQuest();
	testQuest->Initialize(this);
	AddQuest(testQuest);
}

void SampleNPC::Update()
{
	NonePlayer::Update();
}

