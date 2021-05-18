#pragma once
class GoblinIdle : public IState<class Goblin>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;

private :

};

