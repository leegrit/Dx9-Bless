#include "stdafx.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerNormalAttack.h"


Player::Player(Scene * pScene, NavMesh * pNavMesh)
	:Pawn(pScene, nullptr, pNavMesh)
{
}

Player::~Player()
{
}

void Player::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);

	
	PlayerController* pController = PlayerController::Create(this);
	AddComponent(pController);
	AddComponent(PlayerNormalAttack::Create(this, pController));
}

Player * Player::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Player* player = new Player(pScene, pNavMesh);
	player->Initialize(dataPath);
	return player;
}
