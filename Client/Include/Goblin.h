#pragma once
#include "Enemy.h"

class Goblin final : public Enemy
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private:
	explicit Goblin(Scene* pScene, NavMesh* pNavMesh);
	virtual ~Goblin();

	//////////////////////////////////////////////////////////////////////////
	// INHERTIED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnDied() override;
	virtual UINT GetTargetLayer() override;
	virtual void OnCollision(Collider* other) override;
	virtual int GetAttackCount() override;
	virtual Collider * GetAttackCollider(int attackIndex) override;
	virtual float GetFocusColliderSize() override;
	virtual D3DXVECTOR3 GetFocusUIOffset() override;
	virtual int GetLevel() override;
	virtual std::wstring GetCharacterName() override;
	virtual void Reset() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
	void OnHitOthers(Collider* other);


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	StateController<Goblin>* GetState() { return &m_state; }


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private:
	/* For FSM */
	StateController<Goblin> m_state;

	/* For NormalAttack */
	Collider* m_pAttackCollider = nullptr;
	D3DXVECTOR3 m_colliderOffset;

	/* For Font */
	class NameFont * m_pNameFont = nullptr;

	float m_exp = 30;

private : /* Name ColorChange */
	float m_colorChangeElapsed = 0;
	float m_colorChangeDelay = 0.2f;
	bool m_bRedColor = false;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static Goblin * Create(Scene * pScene, NavMesh* pNavMesh, std::wstring dataPath);

};

