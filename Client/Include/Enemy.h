#pragma once
#include "Character.h"
using namespace HyEngine;

class Enemy abstract : public Character
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Enemy(Scene* scene, NavMesh* pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius);
	virtual ~Enemy();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnDamaged(GameObject* pSender, float damage, bool isCritical) override;
	virtual void OnDied() override;

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual UINT GetTargetLayer() PURE;
	virtual void OnCollision(Collider* other) PURE;
	virtual void OnHitOthers(Collider* other) PURE;
	virtual int GetAttackCount() PURE;
	virtual Collider* GetAttackCollider(int attackIndex) PURE;


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void AddHitOthers(GameObject* other);
	void SendDamageToOthers(float damage);
	void ClearHitOthers();


	//////////////////////////////////////////////////////////////////////////
	// PROTECTED
	//////////////////////////////////////////////////////////////////////////
protected :
	void ShowHPBar();


private :
	/* For Action */
	std::vector<Collider*> m_attackColliders;
	int m_attackCount;
	std::vector<GameObject*> m_hitOthers;

	/* For HP */
	bool m_bShowHP = false;
	class EnemyHPBar * m_pHpBarBillboard = nullptr;

};

