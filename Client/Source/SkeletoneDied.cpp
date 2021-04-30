#include "StandardEngineFramework.h"
#include "SkeletoneDied.h"
#include "Skeletone.h"


void SkeletoneDied::Enter()
{
	m_component->SetAnimationSet(18);
}

void SkeletoneDied::Update()
{

}

void SkeletoneDied::Late_Update()
{
}

void SkeletoneDied::Exit()
{
}
