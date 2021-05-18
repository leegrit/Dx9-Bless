#pragma once
#include "Pawn.h"
#include "IQuestTarget.h"


namespace HyEngine
{
	class Billboard;
}
using namespace HyEngine;


class Character abstract : public Pawn, public IQuestTarget
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected:
	explicit Character(Scene* scene, NavMesh* pNavMesh, D3DXVECTOR3 colPosOffest, float colRadius, ESkinningType skinningType = ESkinningType::SoftwareSkinning);
	explicit Character(Scene* scene, NavMesh* pNavMesh, ESkinningType skinningType = ESkinningType::SoftwareSkinning);
	virtual ~Character();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void Render() override;
	/* For Quest */
	virtual void ShowQuestMark(Quest * pQuest) override;
	virtual void RemoveQuestMark(Quest * pQuest) override;
	virtual void ShowQuestFinishMark(Quest * pQuest) override;
	virtual void RemoveQuestFinishMark(Quest * pQuest) override;

	//////////////////////////////////////////////////////////////////////////
	// GETTER
	//////////////////////////////////////////////////////////////////////////
public:
	/* For Status */
	bool IsDamaged() const;
	bool IsDied() const;
	float GetMoveSpeed() const;
	float GetMaxHP() const;
	float GetCurHP() const;
	float GetMaxMP() const;
	float GetCurMP() const;
	std::vector<GameObject*>& GetHitOthers();
	void IncreaseHP(float hp);
	void IncreaseMP(float mp);

	//////////////////////////////////////////////////////////////////////////
	// SETTER
	//////////////////////////////////////////////////////////////////////////
public :
	void SetParams(float moveSpd, float maxHP, float maxMP);
	void SetDamagedState(bool isDamaged);

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void OnCollision(Collider* other) PURE;
	virtual std::wstring GetCharacterName() 
	{
		return std::wstring();
	};
	virtual int GetLevel() 
	{
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
protected :
	virtual void OnDamaged(GameObject* pSender, float damage, bool isCritical);
	virtual void OnDied();
	virtual void OnHPChanged();
	virtual void OnMPChanged();


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void SendDamage(GameObject* sender, float damage, bool isCritical = false);
	bool UseMP(float value);

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	Collider* m_pCollider;
	bool m_isDamaged = false;
	bool m_isDied = false;

	


	/* Status */
	float m_moveSpeed;
	float m_maxHP;
	float m_curHP;
	float m_maxMP;
	float m_curMP;

private : /* For Quest */
	class HyEngine::Billboard* m_pMainQuestMarker = nullptr;
	class HyEngine::Billboard* m_pSubQuestMarker = nullptr;
	class HyEngine::Billboard * m_pMainQuestFinishMarker = nullptr;
	class HyEngine::Billboard* m_pSubQuestFinishMarker = nullptr;



};

