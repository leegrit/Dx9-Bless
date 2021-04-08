#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Effect : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Effect(Scene* scene, std::wstring name, int editID);
		explicit Effect(Scene* scene, std::wstring name);
		virtual ~Effect();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public: 
		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType)override;

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	protected :
		/* Origin */
		D3DXVECTOR3 m_originPos;
		D3DXVECTOR3 m_originRot;
		D3DXVECTOR3 m_originScale;

		/* Start */
		D3DXVECTOR3 m_startPos;
		D3DXVECTOR3 m_startRot;
		D3DXVECTOR3 m_startScale;

		/* End */
		D3DXVECTOR3 m_endPos;
		D3DXVECTOR3 m_endRot;
		D3DXVECTOR3 m_endScale;

		/* Fade In Out */
		bool m_fadeIn;
		bool m_fadeOut;

		/* LifeTime */
		float m_lifeTime;
		float m_loopTime;
		float m_curLifeTime;
		float m_totalLifeTime;

		/* Repeat */
		bool m_isRepeat;
	};
}

