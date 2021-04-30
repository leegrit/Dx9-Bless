#pragma once

class DummyBossHit : public IState<class DummyBoss>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;
};

