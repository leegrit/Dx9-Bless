#pragma once
class SoldierMove : public IState<class Soldier>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;

};

