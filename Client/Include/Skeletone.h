#pragma once
#include "Enemy.h"

class Skeletone final : public Enemy
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit Skeletone(Scene* pScene, NavMesh* pNavMesh);
	virtual ~Skeletone();

	//////////////////////////////////////////////////////////////////////////
	// INHERTIED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;

	virtual UINT GetTargetLayer() override;
	virtual void OnCollision(Collider* other) override;
	virtual int GetAttackCount() override;
	virtual Collider * GetAttackCollider(int attackIndex) override;


	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
	void OnHitOthers(Collider* other);


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	StateController<Skeletone>* GetState() { return &m_state; }


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	/* For FSM */
	StateController<Skeletone> m_state;

	/* For NormalAttack */
	Collider* m_pAttackCollider = nullptr;
	D3DXVECTOR3 m_colliderOffset;

	/* For Font */
	class NameFont * m_pNameFont = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static Skeletone * Create(Scene * pScene, NavMesh* pNavMesh, std::wstring dataPath);



};

