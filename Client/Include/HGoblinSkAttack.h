#pragma once

class HGoblinSkAttack : public IState<class HGoblin>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;

private:
	float m_elapsed = 0.0f;
	bool m_isAttacked = false;
	bool m_isAttacked2 = false;
};

