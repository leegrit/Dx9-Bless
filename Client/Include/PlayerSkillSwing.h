#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}

class PlayerController;
class PlayerSkillSwing : public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private:
	explicit PlayerSkillSwing(GameObject * pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerSkillSwing();

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
	int m_animIndexes[1] = { /*22,*/ /*26,*/  24 };//,23, 24};
	// 데미지 배율
	float m_damageScale[3] = { 0.8f, 1.5f, 3.0f };
	class PlayerStatusData * m_pPlayerStatusData = nullptr;
	class PlayerBuffInfo * m_pPlayerBuffInfo = nullptr;
	class PlayerEquipData * m_pPlayerEquipData = nullptr;

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;
	bool m_bFinalSendDamage[4] = { false, false, false, false};

private : /* For Effect */
	
	bool m_bPlayAfterImage = false;
	bool m_bFinalAfterImage[4] = { false, false, false, false };
	int m_afterImageIndex = 0;
	/* For Final Attack */
	float m_afterImageDuration = 0.0f;
	float m_afterImageDelay = 0.1f;

private : /* FirstAction Effect */
	Effect * m_pFirstActionTrail = nullptr;

private : /* SecondAction Effect */
	Effect* m_pSecondActionTrail = nullptr;

private : /* ThirdAction Effect */
	Effect* m_pEffect0 = nullptr;
	Effect* m_pEffect1 = nullptr;

	Effect * m_pSwingEffect = nullptr;

private : /* FourthAction Effect */
	Effect * m_pFourthActionTrail = nullptr;

private : /* ThirdAction AfterImage */
	std::vector<int> m_thirdActionAfterImageIndex;
	std::vector<bool> m_thirdActionSeq;

	float m_atkSpeed = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerSkillSwing* Create(GameObject * pPlayer, PlayerController* pPlayerController);

};

