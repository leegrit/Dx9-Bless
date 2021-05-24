#pragma once
#include "ActionComponent.h"

class PlayerController;
class PlayerAction abstract : public ActionComponent
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected:
	explicit PlayerAction(DWORD behaviourType, GameObject* pOwner, PlayerController * pPlayerController, std::wstring name);
	virtual ~PlayerAction();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnHitOthers(Collider* other) override;
	virtual void OnSequenceStart(int seqIndex) override;
	virtual void OnActionTimeElapsed(int seqIndex, float elapsed) override;
	virtual void OnActionEnd() override;

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual UINT GetTargetLayer() const PURE;
	virtual int GetIdleAnimIndex() const PURE;
	


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	float GetCoolTime();
	float GetCurCoolTime();
	PlayerController* GetPlayerController();

	//////////////////////////////////////////////////////////////////////////
	// PROTECTED METHOD
	//////////////////////////////////////////////////////////////////////////
protected:
	void SetParams(float atkDelay, int seqCount, float coolTime, float atkRange, float damage, bool bKnockBack, D3DXVECTOR3 colOffset);
	void SetManaDemand(float manaDemand);
	
	bool DoAction(int animIndex);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	PlayerController* m_pPlayerController = nullptr;


	/* For Attack parameters */
	float m_coolTime;
	float m_curCoolTime;

	float m_manaDemand = 0; // ���� �䱸��

};

