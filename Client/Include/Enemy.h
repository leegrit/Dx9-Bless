#pragma once
#include "Character.h"

namespace HyEngine
{
	class Effect;
}

enum class EEnemyHitType
{
	SwordLeft,
	SwordRight
};

using namespace HyEngine;

class Enemy abstract : public Character
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Enemy(Scene* scene, NavMesh* pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius, ESkinningType skinningType);
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
	virtual void OnEnable() override;
	virtual void OnDisable() override;

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual UINT GetTargetLayer() PURE;
	virtual void OnCollision(Collider* other) PURE;
	virtual void OnHitOthers(Collider* other) PURE;
	virtual int GetAttackCount() PURE;
	virtual Collider* GetAttackCollider(int attackIndex) PURE;
	virtual float GetFocusColliderSize() PURE;
	virtual D3DXVECTOR3 GetFocusUIOffset() PURE;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void AddHitOthers(GameObject* other);
	void SendDamageToOthers(float damage);
	void ClearHitOthers();

	void PlayHitAnimation(EEnemyHitType);

	GameObject* GetTarget() const;
	void SetTarget(GameObject* pTarget);
	const std::vector<GameObject*>& GetTargets() const;

	//////////////////////////////////////////////////////////////////////////
	// PROTECTED
	//////////////////////////////////////////////////////////////////////////
protected :
	void ShowHPBar();


private : /* For FSM */
	// 필드에 존재하는 적을 미리 저장해둔다.
	GameObject* m_pTarget = nullptr;
	std::vector<GameObject* > m_targets;

private :
	/* For Action */
	std::vector<Collider*> m_attackColliders;
	int m_attackCount;
	std::vector<GameObject*> m_hitOthers;

	/* For HP */
	bool m_bShowHP = false;
	class EnemyHPBar * m_pHpBarBillboard = nullptr;
	class Billboard * m_pHPHitBar = nullptr;

	/* For Focus */
	Collider * m_pFocusCollider;

private : /* hit reaction */
	bool m_hited = false;
	float m_hitElapsed = 0;
	float m_reactionDuration = 0.2f;

private : /* Hit Effect */
	Effect * m_pLeftSwordHitEffect;
	Effect * m_pRightSwordHitEffect;
	class Sprite* m_pHitEffect;
	Effect* m_pLeftBloodEffect;
	Effect* m_pRightBloodEffect;
	class Sprite * m_pHitEffect2;


};

