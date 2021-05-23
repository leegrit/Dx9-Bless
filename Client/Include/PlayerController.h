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
	enum class ECollectStep { CollectBegin, Collecting, CollectEnd, DONE};
	enum class EFormChangeStep {Begin, End, Done};
public:
	enum class EFormStat {Weapon, UnWeapon};
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
	EFormStat GetFormState();
	void SetFormState(EFormStat formState);
	void SetState(EPlayerState playerState);

	void SetHorse(DynamicMesh* pDynamicMesh);
	void SetUnWeaponMesh(DynamicMesh* pDynamicMesh);
	bool IsMovable();

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :
	void OnBeginCollect(void* collectType);
	void OnEndCollect(void* collectType);
	void OnShopOpen(void*);
	void OnShopClose(void*);

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHOD
	//////////////////////////////////////////////////////////////////////////
private :
	/* For Control */
	void UpdateMovement();
	void UpdateRotation();
	void UpdateAction();

private : /* Action */
	void RideAction();
	void CollectAction();
	void FormChangeAction();


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
	class Sprite* m_pSummonEffect = nullptr;


private : /* For FormChange */
	bool m_bChangeToUnweapon = false;
	bool m_bChangeToWeapon = false;
	EFormChangeStep m_formChangeStep = EFormChangeStep::Done;
	float m_formChangeDelay = 0.2f;
	float m_formChangeElapsed = 0;
	EFormStat m_formState = EFormStat::Weapon;
	
	

private : /* For Collect Action */
	bool m_bCollecting = false;
	float m_collectBeginElapsed = 0;
	float m_collectEndElapsed = 0;
	float m_collectToWeaponDelay = 0.3f;
	float m_collectDelay = 1.8f;
	bool m_bWeaponState = false;
	bool m_bUnWeaponState = false;
	ECollectMotionType m_collectType;
	ECollectStep m_collectStep = ECollectStep::DONE;

	/* For More Animation */
private :
	DynamicMesh* m_pPlayerUW = nullptr;

private : /* For Sound */
	bool m_bLeftWalkSound = false;
	bool m_bRightWalkSound = false;
	float m_walkDelay = 0.42f;
	float m_walkElapsed = 0;

private:
	bool m_bShopOpen = false;
	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static PlayerController* Create(GameObject* pOwner);
};

