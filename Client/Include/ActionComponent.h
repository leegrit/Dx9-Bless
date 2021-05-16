#pragma once
#include "Component.h"
using namespace HyEngine;
class ActionComponent abstract: public Component
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit ActionComponent(DWORD type, GameObject* pOwner, std::wstring name);
	virtual ~ActionComponent();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;


	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void OnHitOthers(Collider* other) PURE;
	virtual void OnSequenceStart(int seqIndex) PURE;
	virtual void OnActionTimeElapsed(int seqIndex, float elapsed) PURE;
	virtual UINT GetTargetLayer() const PURE;
	virtual void OnActionEnd() PURE;
	virtual int  GetIdleAnimIndex() const PURE;

	//////////////////////////////////////////////////////////////////////////
	// GETTER
	//////////////////////////////////////////////////////////////////////////
public :
	float GetAttackDamage(bool isCritical = false)const;
	bool IsAttackState() const;

	//////////////////////////////////////////////////////////////////////////
	// PROTECTED METHOD
	//////////////////////////////////////////////////////////////////////////
protected :
	void SetParams(float atkDelay, int seqCount, float atkRange, float damage, bool bKnockBack, D3DXVECTOR3 colOffset);
	bool DoAction(int animIndex);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	/* For Collider */
	Collider* m_pAttackCollider = nullptr;
	D3DXVECTOR3 m_colliderOffset;

	/* For Attack parameters */
	float m_attackDelay;
	int m_attackSeqCount;
	int m_curSequence;
	int m_nextSequence;
	float m_attackRange;
	float m_damage;
	bool m_bKnockBack;
	bool m_bNextAttack;
	bool m_bAttackState; // 공격중인지
	float m_attackElapsed;

	/* For Animation */
	int m_nextAnimIndex;
};

