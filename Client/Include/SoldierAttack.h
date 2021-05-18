#pragma once
class SoldierAttack : public IState<class Soldier>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;

private:
	float m_elapsed = 0.0f;
	bool m_isAttacked = false;
};

