#pragma once
#include "Component.h"
#include "Client_Enumerators.h"


namespace HyEngine
{
	class DynamicMesh;
}

using namespace HyEngine;


class PlayerController final : public Component
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit PlayerController(GameObject* pOwner);
	virtual ~PlayerController();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	// Inherited via Component
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;



	//////////////////////////////////////////////////////////////////////////
	// GETTER & SETTER
	//////////////////////////////////////////////////////////////////////////
public :
	EPlayerState GetState() const;
	void SetState(EPlayerState playerState);

	void SetHorse(DynamicMesh* pDynamicMesh);
	void SetUnWeaponMesh(DynamicMesh* pDynamicMesh);

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHOD
	//////////////////////////////////////////////////////////////////////////
private :
	/* For Control */
	void UpdateMovement();
	void UpdateRotation();
	void UpdateAction();

	/* For Animation */
private :
	void SetAnimationSet(int index);
	bool IsAnimationEnd();


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	/* For PlayerState */
	EPlayerState m_playerState;

	/* For Movement */
	float m_speed;
	D3DXVECTOR3 m_mouseCenter;
	float m_horseSpeed;

	/* For Horse Ride */
private :
	DynamicMesh* m_pPegasus = nullptr;
	bool m_bSummonPegasus = false;
	bool m_bCanclePegasus = false;
	float m_delay = 1.0f;
	float m_summonElapsed = 0;

	/* For More Animation */
private :
	DynamicMesh* m_pPlayerUW = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static PlayerController* Create(GameObject* pOwner);
};

