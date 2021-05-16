#include "stdafx.h"
#include "EffectManager.h"
#include "MeshEffect.h"
#include "GameScene.h"
#include "PlayerAfterImage.h"
#include "PathManager.h"
#include "WeaponAfterImage.h"

EffectManager::EffectManager(GameScene * pScene)
{
	m_pScene = pScene;
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	for (int i = 0; i < 3; i++)
	{
		PlayerAfterImage* pAfterImage = PlayerAfterImage::Create(m_pScene, nullptr, PATH->DatasPathW() + L"HierarchyData/Hieracon_Player.json", ESkinningType::HardwareSkinning);
		pAfterImage->SetActive(false);
		pAfterImage->SetRenderEffectOption(RenderEffectOption::RimLight);
		pAfterImage->SetRimWidth(1.0f);
		m_playerAfterImages.push_back(pAfterImage);
	}

	/* For Weapon After Image */
	for (int i = 0; i < 10; i++)
	{
		WeaponAfterImage * pWeaponAfterImage = WeaponAfterImage::Create
		(
			m_pScene, PLAYER,
			PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW_9000/OSW_9000.x",
			L"Bip01-R-Finger22"
		);
		pWeaponAfterImage->SetActive(false);
		pWeaponAfterImage->SetRenderEffectOption(RenderEffectOption::RimLight);
		pWeaponAfterImage->SetRimWidth(1.0f);
		m_weaponAfterImages.push_back(pWeaponAfterImage);

	}
}

void EffectManager::Update()
{
	for (int i = 0; i < m_afterEffectDescs.size(); i++)
	{
		assert(m_afterEffectDescs[i].pPlayerAfterImage);
		if (m_afterEffectDescs[i].isPlay == false)
		{
			m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->SetPosition(PLAYER->m_pTransform->m_position);
			m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->m_rotationEuler = PLAYER->m_pTransform->m_rotationEuler;
			m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->SetScale(PLAYER->m_pTransform->m_scale);
			m_afterEffectDescs[i].pPlayerAfterImage->ForcedUpdateAnimation();
		}
	}

	for (int i = 0; i < m_afterEffectDescs.size(); i++)
	{
		assert(m_afterEffectDescs[i].pPlayerAfterImage);
		if (m_afterEffectDescs[i].isPlay)
		{
			m_afterEffectDescs[i].elapsed += TIMER->getDeltaTime();
			if (m_afterEffectDescs[i].elapsed >= m_afterEffectDescs[i].lifeTime)
			{
				m_afterEffectDescs[i].pPlayerAfterImage->SetActive(false);
				m_afterEffectDescs.erase(m_afterEffectDescs.begin() + i);
				i--;

				continue;
			}
			m_afterEffectDescs[i].pPlayerAfterImage->SetActive(true);
		}
	}

	for (int i = 0; i < m_weaponAfterEffectDescs.size(); i++)
	{
		m_weaponAfterEffectDescs[i].elapsed += TIMER->getDeltaTime();
		if (m_weaponAfterEffectDescs[i].elapsed >= m_weaponAfterEffectDescs[i].lifeTime)
		{
			m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetActive(false);
			m_weaponAfterEffectDescs.erase(m_weaponAfterEffectDescs.begin() + i);
			i--;
			continue;
		}
		m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetActive(true);
	}
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

Effect * EffectManager::AddEffect(std::wstring key, Effect * pEffect)
{
	m_effects.insert(std::make_pair(key, pEffect));

	return pEffect;
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

int EffectManager::AddAfterEffect(AfterEffectDesc desc, int * pIndex)
{
	AfterEffectDesc oldestDesc;
	int oldestElapsed = 0;
	for (int i = 0; i < m_playerAfterImages.size(); i++)
	{
		if (m_playerAfterImages[i]->GetActive() == false)
		{
			desc.index = i;
			desc.pPlayerAfterImage = m_playerAfterImages[i];
			m_playerAfterImages[i]->SetAnimationSet(desc.animIndex);
			m_playerAfterImages[i]->SetRimWidth(1.0f);
			m_playerAfterImages[i]->SetRimColor(desc.color);
			m_afterEffectDescs.push_back(desc);
			if(pIndex)
				*pIndex = i;
			return i;
		}
		else
		{
			for (int j = 0; j < m_afterEffectDescs.size(); j++)
			{
				if (oldestElapsed <= m_afterEffectDescs[j].elapsed)
				{
					oldestElapsed = m_afterEffectDescs[j].elapsed;
					oldestDesc = m_afterEffectDescs[j];
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_afterEffectDescs.size(); i++)
	{
		if (oldestDesc.index == m_afterEffectDescs[i].index)
		{
			desc.index = oldestDesc.index;
			desc.pPlayerAfterImage = oldestDesc.pPlayerAfterImage;
			oldestDesc.pPlayerAfterImage->SetAnimationSet(desc.animIndex);
			oldestDesc.pPlayerAfterImage->SetRimWidth(1.0f);
			oldestDesc.pPlayerAfterImage->SetRimColor(desc.color);

			m_afterEffectDescs.erase(m_afterEffectDescs.begin() + i);
			i--;
			break;
		}
	}
	m_afterEffectDescs.push_back(desc);
	if (pIndex)
		*pIndex = desc.index;
	return desc.index;
}

void EffectManager::PlayAffterEffect(int index)
{
	for (UINT i = 0; i < m_afterEffectDescs.size(); i++)
	{
		if (m_afterEffectDescs[i].index == index)
		{
			m_afterEffectDescs[i].isPlay = true;
			return;
		}
	}
}

void EffectManager::PlayerWeaponAffterEffect(WeaponAfterEffectDesc desc)
{
	WeaponAfterEffectDesc oldestAfterImageDesc;
	float oldestElapsed = 0;
	for (int i = 0; i < m_weaponAfterImages.size(); i++)
	{
		if (m_weaponAfterImages[i]->GetActive() == false)
		{
			desc.pWeaponAfterImage = m_weaponAfterImages[i];
			desc.index = i;
			desc.pWeaponAfterImage->SetWorldMatrix(desc.worldMat);
			desc.pWeaponAfterImage->SetRimWidth(1.0f);
			desc.pWeaponAfterImage->SetRimColor(desc.color);
			m_weaponAfterEffectDescs.push_back(desc);
			return;
		}
		else
		{
			for (int j = 0; j < m_weaponAfterEffectDescs.size(); j++)
			{
					if (oldestElapsed <= m_weaponAfterEffectDescs[i].elapsed)
					{
						oldestElapsed = m_weaponAfterEffectDescs[i].elapsed;
						oldestAfterImageDesc = m_weaponAfterEffectDescs[i];
						break;
					}
				
			}
		}
	}

	for (int i = 0; i < m_weaponAfterEffectDescs.size(); i++)
	{
		if (m_weaponAfterEffectDescs[i].index == oldestAfterImageDesc.index)
		{
			desc.pWeaponAfterImage = m_weaponAfterEffectDescs[i].pWeaponAfterImage;
			desc.index = m_weaponAfterEffectDescs[i].index;
			desc.pWeaponAfterImage->SetWorldMatrix(desc.worldMat);
			desc.pWeaponAfterImage->SetRimWidth(1.0f);
			desc.pWeaponAfterImage->SetRimColor(desc.color);

			m_weaponAfterEffectDescs.erase(m_weaponAfterEffectDescs.begin() + i);
			i--;
		}
	}
	m_weaponAfterEffectDescs.push_back(desc);


}
