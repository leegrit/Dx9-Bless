#include "StandardEngineFramework.h"
#include "NonePlayer.h"

NonePlayer::NonePlayer(Scene * scene)
	:Character(scene, nullptr)
{

}

NonePlayer::~NonePlayer()
{
}

void NonePlayer::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);

}

void NonePlayer::Update()
{
	Character::Update();
}

void NonePlayer::OnCollision(Collider * other)
{
}
