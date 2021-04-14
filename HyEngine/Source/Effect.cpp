#include "StandardEngineFramework.h"
#include "Effect.h"
#include "EffectData.h"


HyEngine::Effect::Effect(Scene * scene, std::wstring name, int editID)
	: GameObject(ERenderType::RenderAlpha, scene, nullptr, name),
	m_startPos(0, 0, 0),
	m_endPos(0, 0, 0),
	m_startRot(0, 0, 0),
	m_endRot(0, 0, 0),
	m_fadeIn (false),
	m_fadeOut(false),
	m_lifeTime(0),
	m_curLifeTime(0),
	m_totalLifeTime(0),
	m_loopTime(0),
	m_isRepeat(false)
{
	m_originPos = m_pTransform->m_position.operator D3DXVECTOR3();
	m_originRot = m_pTransform->m_rotationEuler.operator D3DXVECTOR3();
	m_originScale = m_pTransform->m_scale.operator D3DXVECTOR3();
	SetEditID(editID);
}

HyEngine::Effect::Effect(Scene * scene, std::wstring name)
	:GameObject(ERenderType::RenderAlpha, scene, nullptr, name),
	m_startPos(0, 0, 0),
	m_endPos(0, 0, 0),
	m_startRot(0, 0, 0),
	m_endRot(0, 0, 0),
	m_fadeIn(false),
	m_fadeOut(false),
	m_lifeTime(0),
	m_curLifeTime(0),
	m_totalLifeTime(0),
	m_loopTime(0),
	m_isRepeat(false)
{
	m_originPos = m_pTransform->m_position.operator D3DXVECTOR3();
	m_originRot = m_pTransform->m_rotationEuler.operator D3DXVECTOR3();
	m_originScale = m_pTransform->m_scale.operator D3DXVECTOR3();

}

HyEngine::Effect::~Effect()
{

}

void HyEngine::Effect::OnEnable()
{
	GameObject::OnEnable();
	m_curLifeTime = 0;
	m_totalLifeTime = 0;
	m_originPos = m_pTransform->m_position.operator D3DXVECTOR3();
	m_originRot = m_pTransform->m_rotationEuler.operator D3DXVECTOR3();
	m_originScale = m_pTransform->m_scale.operator D3DXVECTOR3();
}

void HyEngine::Effect::OnDisable()
{
	GameObject::OnDisable();
}

void HyEngine::Effect::Update()
{
	GameObject::Update();

	if (IS_EDITOR)
	{
		m_curLifeTime += EDIT_TIMER->getDeltaTime();
		m_totalLifeTime += EDIT_TIMER->getDeltaTime();
	}
	else
	{
		m_curLifeTime += TIMER->getDeltaTime();
		m_totalLifeTime += TIMER->getDeltaTime();
	}

	/* Die */
// 	if (m_totalLifeTime >= m_loopTime)
// 	{
// 		SetActive(false);
// 		return;
// 	}

	/* Reset */
	if (m_curLifeTime >= m_lifeTime)
	{
		m_curLifeTime = 0;
	}


	float factor = m_curLifeTime / m_lifeTime;

	/* Update Position */
	D3DXVECTOR3 position = MathUtils::lerp<D3DXVECTOR3>(m_originPos + m_startPos, m_originPos + m_endPos, factor);
	m_pTransform->SetPosition(position);

	/* Update Rotation */
	D3DXVECTOR3 rotation = MathUtils::lerp<D3DXVECTOR3>(m_originRot +  m_startRot, m_originRot + m_endRot, factor);
	m_pTransform->SetRotationEuler(rotation);

	/* Update Scale */
	D3DXVECTOR3 scale = MathUtils::lerp<D3DXVECTOR3>(m_originScale + m_startScale, m_originScale + m_endScale, factor);
	m_pTransform->SetScale(scale);

	// TODO : Fade In Out


}

void HyEngine::Effect::Render()
{
	GameObject::Render();
}

void HyEngine::Effect::UpdatedData(EDataType dataType)
{
	GameObject::UpdatedData(dataType);

	if (dataType == EDataType::EffectData)
	{
		assert(m_pEffectData);

		/* Copy start info */
		memcpy(&m_startPos, &m_pEffectData->startPos, sizeof(D3DXVECTOR3));
		memcpy(&m_startRot, &m_pEffectData->startRot, sizeof(D3DXVECTOR3));
		memcpy(&m_startScale, &m_pEffectData->startScale, sizeof(D3DXVECTOR3));

		/* Copy end info */
		memcpy(&m_endPos, &m_pEffectData->endPos, sizeof(D3DXVECTOR3));
		memcpy(&m_endRot, &m_pEffectData->endRot, sizeof(D3DXVECTOR3));
		memcpy(&m_endScale, &m_pEffectData->endScale, sizeof(D3DXVECTOR3));

		/* fade */
		m_fadeIn = m_pEffectData->fadeIn;
		m_fadeOut = m_pEffectData->fadeOut;

		/* Time */
		m_lifeTime = m_pEffectData->lifeTime;
		m_loopTime = m_pEffectData->loopTime;

		/* Repeat */
		m_isRepeat = m_pEffectData->isRepeat;
	}
}
