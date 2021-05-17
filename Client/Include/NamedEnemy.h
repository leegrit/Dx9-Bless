#pragma once
#include "Enemy.h"

class NamedEnemy :public Enemy
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit NamedEnemy(Scene* pScene, NavMesh* pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius, ESkinningType skinningType);
	virtual ~NamedEnemy();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual UINT GetTargetLayer() PURE;
	virtual void OnCollision(Collider* other) PURE;
	virtual int GetAttackCount() PURE;
	virtual Collider * GetAttackCollider(int attackIndex) PURE;
	virtual void OnHitOthers(Collider* other) PURE;
	virtual void OnDamaged(GameObject* pSender, float damage, bool isCritical) override;


};

