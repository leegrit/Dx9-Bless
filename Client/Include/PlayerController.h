#pragma once
#include "Component.h"


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

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static PlayerController* Create(GameObject* pOwner);
};

