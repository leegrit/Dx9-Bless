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
		// GETTER 
		//////////////////////////////////////////////////////////////////////////
	public :
		float GetAlpha();

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
	private :
		bool m_fadeIn;
		bool m_fadeOut;
		// fade in out 비율
		// 만약 값이 0.2, 총 시간이 2초면 
		// 0.4초동안 fade in out
		float m_fadeInFactor = 0.2f;
		float m_fadeOutFactor = 0.2f;
		float m_curAlpha = 1;


		/* LifeTime */
	private :
		float m_lifeTime;
		float m_loopTime;
		float m_curLifeTime;
		float m_totalLifeTime;

		/* Repeat */
	private :
		bool m_isRepeat;
	};
}

