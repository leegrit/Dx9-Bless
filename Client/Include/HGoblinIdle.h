#pragma once
class HGoblinIdle : public IState<class HGoblin>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;

private :
	float atkProb = 35; // Attack ���� Ȯ��
	float atk2Prob = 35; // Attack2 ���� Ȯ��
	float skAtkProb = 30; // ��ų ���� Ȯ��
};

