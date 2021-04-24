#include "StandardEngineFramework.h"
#include "LightObject.h"
#include "Light.h"
#include "ObjectContainer.h"
#include "LightData.h"
#include "HierarchyData.h"
#include "Deserializer.h"


HyEngine::LightObject::LightObject(Scene * scene, GameObject * parent, int editID)
	:GameObject(ERenderType::None, scene, parent, L"Light")
{
	SetEditID(editID);
}

HyEngine::LightObject::LightObject(Scene * scene, GameObject * parent)
	: GameObject(ERenderType::None, scene, parent, L"Light")
{
}

HyEngine::LightObject::~LightObject()
{
	Object::Destroy(m_pLight);
}

void HyEngine::LightObject::Initialize()
{
	/* �̸� ��� �� �� ���� �� ��� ����ǰ� �Ѵ�.*/
	m_pLight = new Light();
	GetScene()->GetObjectContainer()->AddLight(m_pLight);
}

void HyEngine::LightObject::Initialize(std::wstring dataPath)
{
	m_pLight = new Light();
	GetScene()->GetObjectContainer()->AddLight(m_pLight);

	std::shared_ptr<HierarchyData> data = Deserializer::Deserialize(dataPath);

	InsertGameData(data->gameObjectData);
	InsertLightData(data->lightData);
}

void HyEngine::LightObject::Update()
{
	GameObject::Update();
	if (GetViewFrustumCulled() == true)
	{
		m_pLight->SetActive(false);
	}
	else
	{
		m_pLight->SetActive(true);
	}
}

void HyEngine::LightObject::UpdatedData(EDataType dataType)
{
	/* Intensity�� ��� ������� �ʴ´�. �Ŀ� ���� ����*/
	if (dataType == EDataType::LightData)
	{
		m_pLight->Type() = (ELightType)m_pLightData->lightType;
		m_pLight->Direction() = D3DXVECTOR3
		(
			m_pLightData->direction.x, 
			m_pLightData->direction.y,
			m_pLightData->direction.z
		);
		m_pLight->Position() = D3DXVECTOR3
		(
			m_pLightData->position.x,
			m_pLightData->position.y,
			m_pLightData->position.z
		);
		m_pLight->Ambient() = D3DXCOLOR
		(
			m_pLightData->ambient.r,
			m_pLightData->ambient.g,
			m_pLightData->ambient.b,
			m_pLightData->ambient.a
		);
		m_pLight->AmbientIntensity() = m_pLightData->ambientIntensity;
		m_pLight->Diffuse() = D3DXCOLOR
		(
			m_pLightData->diffuse.r,
			m_pLightData->diffuse.g,
			m_pLightData->diffuse.b,
			m_pLightData->diffuse.a
		);
		m_pLight->DiffuseIntensity() = m_pLightData->diffuseIntensity;
		m_pLight->Specular() = D3DXCOLOR
		(
			m_pLightData->specular.r,
			m_pLightData->specular.g,
			m_pLightData->specular.b,
			m_pLightData->specular.a
		);
		m_pLight->SpecularIntensity() = m_pLightData->specularIntensity;
		m_pLight->SpecularPower() = m_pLightData->specularPower;
		m_pLight->Range() = m_pLightData->range;
		m_pLight->Cone() = m_pLightData->cone;
		m_pLight->Constant() = m_pLightData->constant;
		m_pLight->Linear() = m_pLightData->linear;
		m_pLight->Quadratic() = m_pLightData->quadratic;
	}
}

void HyEngine::LightObject::OnEnable()
{
	GameObject::OnEnable();
	m_pLight->SetActive(true);
}

void HyEngine::LightObject::OnDisable()
{
	GameObject::OnDisable();
	m_pLight->SetActive(false);
}

Light * HyEngine::LightObject::GetLight()
{
	return m_pLight;
}
