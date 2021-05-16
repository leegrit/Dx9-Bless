#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}
class PlayerController;
class PlayerSkillStab: public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit PlayerSkillStab(GameObject* pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerSkillStab();

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
private:
	/* For Action Sequence */
	int m_seqIndex = 0;
	int m_animIndexes[3] = { 26, 25, 28 };

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;

private: /* For Effect */
	Effect* m_pEffect0 = nullptr;
	Effect* m_pEffect1 = nullptr;

	bool m_bPlayAfterImage = false;
	int m_afterImageIndex = 0;

private : /* FirstAction Effect */
	Effect * m_pFirstActionTrail = nullptr;

private : /* SecondAction Effect */
	Effect * m_pSecondActionTrail = nullptr;

private : /* ThirdAction Effect */
	Effect* m_pThridActionTrail = nullptr;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerSkillStab* Create(GameObject * pPlayer, PlayerController* pPlayerController);


};

