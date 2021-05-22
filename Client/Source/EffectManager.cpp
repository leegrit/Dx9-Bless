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
	for (int i = 0; i < 5; i++)
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
		if (m_afterEffectDescs[i].afterEffectOption & AfterEffectOption::AnimationDelay)
		{
			m_afterEffectDescs[i].curAnimElapsed += TIMER->getDeltaTime();
			if (m_afterEffectDescs[i].curAnimElapsed >= m_afterEffectDescs[i].animDelay
				&& m_afterEffectDescs[i].bAnimStarted == false)
			{
				m_afterEffectDescs[i].pPlayerAfterImage->SetAnimationSet(m_afterEffectDescs[i].animIndex);
				m_afterEffectDescs[i].bAnimStarted = true;
			}
		}
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
			if (m_afterEffectDescs[i].afterEffectOption & AfterEffectOption::RunAnimation)
			{
				m_afterEffectDescs[i].pPlayerAfterImage->ForcedUpdateAnimation();
			}
			if (m_afterEffectDescs[i].afterEffectOption & AfterEffectOption::ScaleEffect)
			{
				float scale = m_afterEffectDescs[i].originScale;
				float startScale = scale * m_afterEffectDescs[i].startScale;
				float endScale = scale * m_afterEffectDescs[i].endScale;
				float  t = (m_afterEffectDescs[i].elapsed * m_afterEffectDescs[i].scaleSpd) / m_afterEffectDescs[i].lifeTime;
				if (t >= 1.0f) t = 1.0;
				scale = MathUtils::lerp<float>(startScale, endScale, t);
				m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->m_scale = D3DXVECTOR3
				(
					scale, scale, scale
				);
			}
			if (m_afterEffectDescs[i].afterEffectOption & AfterEffectOption::FadeOut)
			{
				m_afterEffectDescs[i].alpha -= TIMER->getDeltaTime() * m_afterEffectDescs[i].fadeOutSpd;
				m_afterEffectDescs[i].pPlayerAfterImage->SetRimWidth(m_afterEffectDescs[i].alpha);

			}

			if (m_afterEffectDescs[i].elapsed >= m_afterEffectDescs[i].lifeTime)
			{
				m_afterEffectDescs[i].pPlayerAfterImage->SetActive(false);
				
				m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->m_scale
					= D3DXVECTOR3
					(
						m_afterEffectDescs[i].originScale,
						m_afterEffectDescs[i].originScale,
						m_afterEffectDescs[i].originScale
					);
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
		
		if (m_weaponAfterEffectDescs[i].afterEffectOption & AfterEffectOption::ScaleEffect)
		{
			float scale = m_weaponAfterEffectDescs[i].originScale;
			float startScale = scale * m_weaponAfterEffectDescs[i].startScale;
			float endScale = scale * m_weaponAfterEffectDescs[i].endScale;
			float  t = (m_weaponAfterEffectDescs[i].elapsed * m_weaponAfterEffectDescs[i].scaleSpd) / m_weaponAfterEffectDescs[i].lifeTime;
			if (t >= 1.0f) t = 1.0;
			scale = MathUtils::lerp<float>(startScale, endScale, t);
			std::cout << "scale : " << scale << std::endl;
			/*m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetScale
			(
				D3DXVECTOR3(scale, scale, scale)
			);*/
			m_weaponAfterEffectDescs[i].pWeaponAfterImage->m_pTransform->m_scale = D3DXVECTOR3
			(
				scale, scale, scale
			);
		}
		if (m_weaponAfterEffectDescs[i].afterEffectOption & AfterEffectOption::FadeOut)
		{
			m_weaponAfterEffectDescs[i].alpha -= TIMER->getDeltaTime() * m_weaponAfterEffectDescs[i].fadeOutSpd;
			m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetRimWidth(m_weaponAfterEffectDescs[i].alpha);

		}
		if (m_weaponAfterEffectDescs[i].elapsed >= m_weaponAfterEffectDescs[i].lifeTime)
		{

			m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetActive(false);
			m_weaponAfterEffectDescs[i].pWeaponAfterImage->m_pTransform->m_scale
				= D3DXVECTOR3
				(
					m_weaponAfterEffectDescs[i].originScale,
					m_weaponAfterEffectDescs[i].originScale,
					m_weaponAfterEffectDescs[i].originScale
				);
			m_weaponAfterEffectDescs.erase(m_weaponAfterEffectDescs.begin() + i);
			i--;
			continue;
		}
		m_weaponAfterEffectDescs[i].pWeaponAfterImage->SetActive(true);
	}

	for (int i = 0; i < m_customEffectDescs.size(); i++)
	{
		if (m_customEffectDescs[i]->elapsed == 0)
		{
			if(m_customEffectDescs[i]->onBegin)
				m_customEffectDescs[i]->onBegin(m_customEffectDescs[i]);
		}
		m_customEffectDescs[i]->elapsed += TIMER->getDeltaTime();
		if (m_customEffectDescs[i]->lifeTime <= m_customEffectDescs[i]->elapsed)
		{
			if (m_customEffectDescs[i]->onEnd)
				m_customEffectDescs[i]->onEnd(m_customEffectDescs[i]);
			SAFE_DELETE(m_customEffectDescs[i]);
			m_customEffectDescs.erase(m_customEffectDescs.begin() + i);
			i--;
		}
		else
		{
			m_customEffectDescs[i]->onUpdate(m_customEffectDescs[i]);
		}
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
			bool bUse = false;
			for (int j = 0; j < m_afterEffectDescs.size(); j++)
			{
				if (m_afterEffectDescs[j].pPlayerAfterImage->GetInstanceID() ==
					m_playerAfterImages[i]->GetInstanceID())
				{
					bUse = true;
					break;
				}
			}
			if (bUse == true)
				continue;
			desc.index = i;
			desc.pPlayerAfterImage = m_playerAfterImages[i];
			desc.pPlayerAfterImage->SetAnimationSet(desc.animIndex);
			desc.pPlayerAfterImage->SetAnimationPosition(desc.animPosition);
			desc.pPlayerAfterImage->SetRimWidth(1.0f);
			desc.pPlayerAfterImage->SetRimColor(desc.color);
			desc.pPlayerAfterImage->m_pTransform->SetPosition(PLAYER->m_pTransform->m_position);
			desc.pPlayerAfterImage->m_pTransform->m_rotationEuler = PLAYER->m_pTransform->m_rotationEuler;
			desc.pPlayerAfterImage->m_pTransform->SetScale(PLAYER->m_pTransform->m_scale);
			desc.pPlayerAfterImage->ForcedUpdateAnimation();
			desc.originScale = m_playerAfterImages[i]->m_pTransform->m_scale.x();
			m_afterEffectDescs.push_back(desc);
			if(pIndex)
				*pIndex = i;
			return i;
		}
		else
		{
			
		}
	}
	for (int j = 0; j < m_afterEffectDescs.size(); j++)
	{
		if (oldestElapsed <= m_afterEffectDescs[j].elapsed)
		{
			oldestElapsed = m_afterEffectDescs[j].elapsed;
			oldestDesc = m_afterEffectDescs[j];
			break;
		}
	}
	for (int i = 0; i < m_afterEffectDescs.size(); i++)
	{
		if (oldestDesc.index == m_afterEffectDescs[i].index)
		{
			desc.index = oldestDesc.index;
			desc.pPlayerAfterImage = oldestDesc.pPlayerAfterImage;
			desc.pPlayerAfterImage->SetAnimationSet(desc.animIndex);
			desc.pPlayerAfterImage->SetAnimationPosition(desc.animPosition);
			desc.pPlayerAfterImage->SetRimWidth(1.0f);
			desc.pPlayerAfterImage->SetRimColor(desc.color);
			desc.pPlayerAfterImage->m_pTransform->SetPosition(PLAYER->m_pTransform->m_position);
			desc.pPlayerAfterImage->m_pTransform->m_rotationEuler = PLAYER->m_pTransform->m_rotationEuler;
			desc.pPlayerAfterImage->m_pTransform->SetScale(PLAYER->m_pTransform->m_scale);
			desc.pPlayerAfterImage->ForcedUpdateAnimation();
			desc.originScale = desc.pPlayerAfterImage->m_pTransform->m_scale.x();

			m_afterEffectDescs[i].pPlayerAfterImage->m_pTransform->m_scale = D3DXVECTOR3(m_afterEffectDescs[i].originScale, m_afterEffectDescs[i].originScale, m_afterEffectDescs[i].originScale);
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
			desc.pWeaponAfterImage->Reset(desc.pOrigin);
			desc.pWeaponAfterImage->SetRimWidth(1.0f);
			desc.pWeaponAfterImage->SetRimColor(desc.color);
			desc.originScale = desc.pWeaponAfterImage->m_pTransform->m_scale.x();
			
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
			desc.pWeaponAfterImage->Reset(desc.pOrigin);
			desc.pWeaponAfterImage->SetRimWidth(1.0f);
			desc.pWeaponAfterImage->SetRimColor(desc.color);
			desc.originScale = desc.pWeaponAfterImage->m_pTransform->m_scale.x();
			
			m_weaponAfterEffectDescs[i].pWeaponAfterImage->m_pTransform->m_scale = D3DXVECTOR3
			(
				desc.originScale, desc.originScale, desc.originScale
			);
			m_weaponAfterEffectDescs.erase(m_weaponAfterEffectDescs.begin() + i);
			i--;
		}
	}
	m_weaponAfterEffectDescs.push_back(desc);


}

void EffectManager::AddCustomEffect(CustomEffectDesc * pDesc)
{
	for (int i = 0; i < m_customEffectDescs.size(); i++)
	{
		if (m_customEffectDescs[i]->key.compare(pDesc->key) == 0)
		{
			SAFE_DELETE(m_customEffectDescs[i]);
			m_customEffectDescs[i] = pDesc;
			return;
		}
	}
	m_customEffectDescs.push_back(pDesc);
}

bool EffectManager::RemoveCustomEffect(std::wstring key)
{
	for (int i = 0; i < m_customEffectDescs.size(); i++)
	{
		if (m_customEffectDescs[i]->key.compare(key) == 0)
		{
			SAFE_DELETE(m_customEffectDescs[i]);
			m_customEffectDescs.erase(m_customEffectDescs.begin() + i);
			i--;
			return true;
		}
	}
	return false;
}
