#include "stdafx.h"
#include "EffectManager.h"
#include "MeshEffect.h"
#include "GameScene.h"

EffectManager::EffectManager(GameScene * pScene)
{
	m_pScene = pScene;
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
}

void EffectManager::Update()
{
}

Effect* EffectManager::AddEffect(std::wstring key, MeshEffectDesc desc)
{
	MeshEffect * pMeshEffect = MeshEffect::Create((Scene*)m_pScene);
	pMeshEffect->SetStartPos(desc.startPos);
	pMeshEffect->SetStartRot(desc.startRot);
	pMeshEffect->SetStartScale(desc.startScale);

	pMeshEffect->SetEndPos(desc.endPos);
	pMeshEffect->SetEndRot(desc.endRot);
	pMeshEffect->SetEndScale(desc.endScale);

	pMeshEffect->SetFadeIn(desc.fadeIn);
	pMeshEffect->SetFadeOut(desc.fadeOut);
	pMeshEffect->SetFadeInFactor(desc.fadeInFactor);
	pMeshEffect->SetFadeOutFactor(desc.fadeOutFactor);

	pMeshEffect->SetLifeTime(desc.lifeTime);
	pMeshEffect->SetLoopTime(desc.loopTime);

	pMeshEffect->SetRepeat(desc.isRepeat);

	pMeshEffect->SetUVAnimation(desc.isUVAnim);
	pMeshEffect->SetUVDirection(desc.uvDirection);
	pMeshEffect->SetUVSpeed(desc.uvSpeed);

	pMeshEffect->SetEffectMesh(desc.meshPath);
	pMeshEffect->SetDiffuseTexture(desc.diffusePath);
	pMeshEffect->SetAlphaMaskTexture(desc.alphaMaskPath);

	pMeshEffect->SetActive(false);

	m_effects.insert(std::make_pair(key, pMeshEffect));

	return pMeshEffect;
}

Effect * EffectManager::GetEffect(std::wstring key)
{
	return m_effects[key];
}

void EffectManager::PlayEffect(std::wstring key)
{
	Effect* pEffect = m_effects[key];
	if (pEffect)
	{
		pEffect->SetActive(true);
		pEffect->Reset([=]() 
		{
			pEffect->SetActive(false);
		});
	}
}
