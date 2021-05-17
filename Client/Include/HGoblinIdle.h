#pragma once
class HGoblinIdle : public IState<class HGoblin>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;
};

