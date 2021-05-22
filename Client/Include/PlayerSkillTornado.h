#pragma once
#include "PlayerAction.h"

namespace HyEngine
{
	class Effect;
}

class PlayerSkillTornado final : public PlayerAction
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	explicit PlayerSkillTornado(GameObject * pPlayer, PlayerController* pPlayerController);
	virtual ~PlayerSkillTornado();

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
private:
	void UpdateAction();

	//////////////////////////////////////////////////////////////////////////
	// VARIALBES
	//////////////////////////////////////////////////////////////////////////
private :
	/* For Action Sequence */
	int m_seqIndex = 0;
	int m_animIndexes[1] = {24/*37*/ };

	/* For Attack Logic */
	bool m_bSendDamage = false;
	std::vector<GameObject*> m_hitEnemies;


private: /* Effect */
	int m_testIndex;

private : /* Tornado Effect */
	Effect * m_pTornadoEffect = nullptr;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static PlayerSkillTornado* Create(GameObject * pPlayer, PlayerController* pPlayerController);
};

