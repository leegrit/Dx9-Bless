#include "StandardEngineFramework.h"
#include "Effect.h"
#include "EffectData.h"


HyEngine::Effect::Effect(Scene * scene, std::wstring name, int editID)
	: GameObject(ERenderType::RenderAlpha, scene, nullptr, name),
	m_startPos(0, 0, 0),
	m_endPos(0, 0, 0),
	m_startRot(0, 0, 0),
	m_endRot(0, 0, 0),
	m_startScale(0, 0, 0),
	m_endScale(0, 0, 0),
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
	m_uvOffset = D3DXVECTOR2(0, 0);
	SetEditID(editID);
}

HyEngine::Effect::Effect(Scene * scene, std::wstring name)
	:GameObject(ERenderType::RenderAlpha, scene, nullptr, name),
	m_startPos(0, 0, 0),
	m_endPos(0, 0, 0),
	m_startRot(0, 0, 0),
	m_endRot(0, 0, 0),
	m_startScale(0, 0, 0),
	m_endScale(0, 0, 0),
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

	m_uvOffset = D3DXVECTOR2(0, 0);
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
		if(m_onCompleted)
			m_onCompleted();
		Reset();
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


	/* UV Anim */
	if (m_bUVAnim)
	{
		D3DXVECTOR2 normalizedDir;
		D3DXVec2Normalize(&normalizedDir, &m_uvDir);
		D3DXVECTOR2 offset;
		if (IS_EDITOR)
		{
			offset = normalizedDir * EDIT_TIMER->getDeltaTime() *m_uvSpeed;
		}
		else
		{
			offset = normalizedDir * TIMER->getDeltaTime() *m_uvSpeed;
		}
		m_uvOffset += offset;
		m_uvOffset = D3DXVECTOR2(m_uvOffset.x - (int)m_uvOffset.x, m_uvOffset.y - (int)m_uvOffset.y);

	}


	// TODO : Fade In Out
	if (m_fadeIn)
	{
		if (m_curLifeTime <= m_lifeTime * m_fadeInFactor)
		{
			m_curAlpha = m_curLifeTime / (m_lifeTime * m_fadeInFactor);
		}
		/*else
		{
			m_curAlpha = 1;
		}*/
	}
	else
	{
		m_curAlpha = 1;
	}
	if (m_fadeOut)
	{
		if (m_curLifeTime >= m_lifeTime - (m_lifeTime * m_fadeOutFactor))
		{
			m_curAlpha = (m_lifeTime - m_curLifeTime) / (m_lifeTime * m_fadeOutFactor);

		}
		/*else
		{

		}*/
	}
	else if (m_fadeIn == false)
	{
		m_curAlpha = 1;
	}

}

void HyEngine::Effect::Render()
{
	GameObject::Render();
}

void HyEngine::Effect::UpdatedData(EDataType dataType)
{
	GameObject::UpdatedData(dataType);
	if (dataType == EDataType::GameObjectData)
	{
		SetOriginPos(m_pTransform->m_position.operator D3DXVECTOR3());
		SetOriginRot(m_pTransform->m_rotationEuler.operator D3DXVECTOR3());
		SetOriginScale(m_pTransform->m_scale.operator D3DXVECTOR3());
	}
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

		m_bUVAnim = m_pEffectData->uvAnimation;
		m_uvDir = D3DXVECTOR2(m_pEffectData->uvDirection.x, m_pEffectData->uvDirection.y);
		m_uvSpeed = m_pEffectData->uvMoveSpeed;

		/* Time */
		m_lifeTime = m_pEffectData->lifeTime;
		m_loopTime = m_pEffectData->loopTime;

		/* Repeat */
		m_isRepeat = m_pEffectData->isRepeat;
	}
}

void HyEngine::Effect::SetOriginPos(D3DXVECTOR3 pos)
{ 
	m_originPos = pos;
}

void HyEngine::Effect::SetOriginRot(D3DXVECTOR3 rot)
{
	m_originRot = rot;
}

void HyEngine::Effect::SetOriginScale(D3DXVECTOR3 scale)
{
	m_originScale = scale;
}

void HyEngine::Effect::SetStartPos(D3DXVECTOR3 pos)
{
	m_startPos = pos;
}

void HyEngine::Effect::SetStartRot(D3DXVECTOR3 rot)
{
	m_startRot = rot;
}

void HyEngine::Effect::SetStartScale(D3DXVECTOR3 scale)
{
	m_startScale = scale;
}

void HyEngine::Effect::SetEndPos(D3DXVECTOR3 pos)
{
	m_endPos = pos;
}

void HyEngine::Effect::SetEndRot(D3DXVECTOR3 rot)
{
	m_endRot = rot;
}

void HyEngine::Effect::SetEndScale(D3DXVECTOR3 scale)
{
	m_endScale = scale;
}

void HyEngine::Effect::SetFadeIn(bool fadeIn)
{
	m_fadeIn = fadeIn;
}

void HyEngine::Effect::SetFadeOut(bool fadeOut)
{
	m_fadeOut = fadeOut;
}

void HyEngine::Effect::SetFadeInFactor(float factor)
{
	m_fadeInFactor = factor;
}

void HyEngine::Effect::SetFadeOutFactor(float factor)
{
	m_fadeOutFactor = factor;
}

void HyEngine::Effect::SetLifeTime(float time)
{
	m_lifeTime = time;
}

void HyEngine::Effect::SetLoopTime(float time)
{
	m_loopTime = time;
}

void HyEngine::Effect::SetRepeat(bool isRepeat)
{
	m_isRepeat = isRepeat;
}

void HyEngine::Effect::SetUVAnimation(bool isAnimation)
{
	m_bUVAnim = isAnimation;
}

void HyEngine::Effect::SetUVDirection(D3DXVECTOR2 uvDirection)
{
	m_uvDir = uvDirection;
}

void HyEngine::Effect::SetUVSpeed(float speed)
{
	m_uvSpeed = speed;
}



float HyEngine::Effect::GetAlpha()
{
	return m_curAlpha;
}

D3DXVECTOR2 HyEngine::Effect::GetUVOffset()
{
	return m_uvOffset;
}

void HyEngine::Effect::Reset(std::function<void()> onCompleted)
{
	m_curLifeTime = 0;
	m_uvOffset = D3DXVECTOR2(0, 0);
	m_onCompleted = onCompleted;
}
