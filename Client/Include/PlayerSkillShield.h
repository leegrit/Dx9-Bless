#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}
class ShieldEffect;
class PlayerController;
class PlayerSkillShield final :public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private:
	explicit PlayerSkillShield(GameObject * pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerSkillShield();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
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
private:
	void UpdateAction();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private:
	/* For Action Sequence */
	int m_seqIndex = 0;
	int m_animIndexes[1] = { 0 };

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;

private : /* Shield Effect */
	ShieldEffect* m_pCenterSLD = nullptr;
	ShieldEffect* m_pLeftSLD = nullptr;
	ShieldEffect* m_pRightSLD = nullptr;

private : /* Aura Effect */
	class Effect * m_pAuraEffect = nullptr;
	class Effect * m_pAuraLeftEffect = nullptr;
	class Effect * m_pAuraRightEffect = nullptr;
	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerSkillShield* Create(GameObject * pPlayer, PlayerController* pPlayerController);


};

