#pragma once
#include "NamedEnemy.h"
 
class HGoblin : public NamedEnemy
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit HGoblin(Scene* pScene, NavMesh* pNavMesh);
	virtual ~HGoblin();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual UINT GetTargetLayer() override;
	virtual void OnCollision(Collider* other) override;
	virtual int GetAttackCount() override;
	virtual Collider * GetAttackCollider(int attackIndex) override;
	virtual void OnHitOthers(Collider* other) override;
	virtual float GetFocusColliderSize() override;
	virtual D3DXVECTOR3 GetFocusUIOffset() override;
	virtual int GetLevel() override;
	virtual std::wstring GetCharacterName() override;



	//////////////////////////////////////////////////////////////////////////
	// CALLBACk
	//////////////////////////////////////////////////////////////////////////
public :
	void OnQuestAccept(void* pQuestIndex);

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public: /* For FSM */
	StateController<HGoblin> * GetState() { return &m_state; }
	void StopFSM();
	void PlayFSM();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private: /* For FSM */
	StateController<HGoblin> m_state;
	bool m_isActiveFSM;
	

	bool m_isPlayCinematic = false;
	bool m_bAccepted = false;
	float m_elapsed = 0;
	float m_cinematicDelay = 1.0f;
private : 
	class NameFont * m_pNameFont;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static HGoblin* Create(Scene* pScene, NavMesh* pNavMesh, std::wstring dataPath);


};

