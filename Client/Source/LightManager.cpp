#include "stdafx.h"
#include "LightManager.h"
#include "Light.h"
#include "ObjectContainer.h"
#include "GameScene.h"

LightManager::LightManager(GameScene * pScene)
{
	m_pScene = pScene;
}

LightManager::~LightManager()
{
}

void LightManager::Initialize()
{
	for (int i = 0; i < m_dynamicLightCount; i++)
	{
		auto light = new Light();
		light->Type() = ELightType::POINT;
		light->SetActive(false);
		DynamicLightInfo info;
		info.elapsed = 0;
		info.duration = 0;
		info.key = L"";
		info.pLight = light;
		m_pScene->GetObjectContainer()->AddLight(light);
		m_lightInfos.push_back(info);
	}
}

void LightManager::Update()
{
	for (int i = 0; i < m_lightInfos.size(); i++)
	{
		if (m_lightInfos[i].pLight->GetActive() == true)
		{
			m_lightInfos[i].elapsed += TIMER->getDeltaTime();
			if (m_lightInfos[i].elapsed >= m_lightInfos[i].duration)
			{
				m_lightInfos[i].elapsed = 0;
				m_lightInfos[i].pLight->SetActive(false);
				continue;
			}
		}
	}
}

void LightManager::GenerateLight(std::wstring key, D3DXVECTOR3 position, D3DXCOLOR diffuse, float specularPower, float range, float constant, float linear, float quadratic, float duration)
{
	for (int i = 0; i < m_lightInfos.size(); i++)
	{
		if (m_lightInfos[i].pLight->GetActive() == false)
		{
			m_lightInfos[i].key = key;
			m_lightInfos[i].pLight->Position() = position;
			m_lightInfos[i].pLight->Diffuse() = diffuse;
			m_lightInfos[i].pLight->SpecularPower() = specularPower;
			m_lightInfos[i].pLight->Range() = range;
			m_lightInfos[i].pLight->Constant() = constant;
			m_lightInfos[i].pLight->Linear() = linear;
			m_lightInfos[i].pLight->Quadratic() = quadratic;
			m_lightInfos[i].elapsed = 0;
			m_lightInfos[i].duration = duration;
			m_lightInfos[i].pLight->SetActive(true);
			return;
		}
	}
}

