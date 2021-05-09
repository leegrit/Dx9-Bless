#pragma once
#include "Character.h"

namespace HyEngine
{
	class ProgressBar;
	class MeshHierarchy;
	class AnimationController;
}

using namespace HyEngine;

class Player final : public Character
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit Player(Scene* pScene, NavMesh* pNavMesh);
	virtual ~Player();




	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void OnCollision(Collider * other) override;
	virtual void OnDamaged(GameObject* pSender, float damage, bool isCritical);
	virtual void OnHPChanged();
	virtual void OnMPChanged();
	virtual void Update() override;
	virtual void Render() override;


	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :
	void OnExpChanged(void*);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	DynamicMesh* m_pPlayerUW = nullptr;
	bool m_bPutInWeapon = false;
	bool m_bPutOutWeapon = false;
	bool m_isUnWeapon = false;

	DynamicMesh* m_pPegasus = nullptr;
	bool m_bMount = false;


	class PlayerController* m_pPlayerController = nullptr;

	float m_beginElapsed = 0;
	float m_endElapsed = 0;
	float m_delay = 0.5f;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static Player* Create(Scene* pScene, NavMesh* pNavMesh, std::wstring dataPath);

public :
	ProgressBar* m_pHPBarUI = nullptr;
	ProgressBar* m_pMPBarUI = nullptr;
	ProgressBar* m_pExpBarUI = nullptr;
};

