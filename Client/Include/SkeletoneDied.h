#pragma once

class SkeletoneDied : public IState<class Skeletone>
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Exit() override;
};

