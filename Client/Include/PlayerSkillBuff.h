#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}
class PlayerController;
class PlayerSkillBuff final : public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
private:
	explicit PlayerSkillBuff(GameObject * pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerSkillBuff();

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
	int m_animIndexes[1] = { 46 };

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;

private : /* For Effect */
	bool m_bPlayAfterImage = nullptr;


private :
	class PlayerBuffInfo* m_pPlayerBuffInfo = nullptr;
	//bool m_bBuff = false;
	float m_buffElapsed = 0.0f;
	float m_buffDuration = 20.0f;
	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerSkillBuff* Create(GameObject * pPlayer, PlayerController* pPlayerController);
};

