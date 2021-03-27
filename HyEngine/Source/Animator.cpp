#include "StandardEngineFramework.h"
#include "Animator.h"

HyEngine::Animator::Animator(GameObject * owner)
	:Component(BehaviourType::Update, owner, L"Animator")
{

}

HyEngine::Animator::~Animator()
{
}

void HyEngine::Animator::Initialize()
{
}

void HyEngine::Animator::Update()
{
}

void HyEngine::Animator::LateUpdate()
{
}

void HyEngine::Animator::OnEnable()
{
}

void HyEngine::Animator::OnDisable()
{
}
