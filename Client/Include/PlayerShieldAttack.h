#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}

class PlayerController;
class PlayerShieldAttack : public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit PlayerShieldAttack(GameObject* pPlayer, PlayerController * pPlayerController);
	virtual ~PlayerShieldAttack();

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
	int m_animIndexes[1] = { /*22,*/ /*26,*/  29 };//,23, 24};
												   // 데미지 배율
	float m_damageScale[3] = { 1.5f, 1.5f, 3.0f };
	class PlayerStatusData * m_pPlayerStatusData = nullptr;
	class PlayerBuffInfo * m_pPlayerBuffInfo = nullptr;
	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;
	bool m_bFinalSendDamage[4] = { false, false, false, false };

private : /* For Effect */
	Effect * m_pShieldEffect = nullptr;
	Effect * m_pWaveEffect = nullptr;
	Effect * m_pWindEffect = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerShieldAttack* Create(GameObject * pPlayer, PlayerController* pPlayerController);

};

