#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}

class PlayerController;
class PlayerNormalAttack final : public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
private :
	explicit PlayerNormalAttack(GameObject * pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerNormalAttack();

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
	virtual UINT GetTargetLayer() const override;
	virtual int GetIdleAnimIndex() const override;

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHOD
	//////////////////////////////////////////////////////////////////////////
private :
	void UpdateAction();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	/* For Action Sequence */
	int m_seqIndex = 0;
	int m_animIndexes[3] = { 22, 23, 1 };

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;

private : /* Effect */
	Effect * m_pSwordTrail = nullptr;
	Effect* m_pSwordTrail_Second = nullptr;
	Effect* m_pSwordTrail_Third = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static PlayerNormalAttack* Create(GameObject * pPlayer, PlayerController* pPlayerController);
};

