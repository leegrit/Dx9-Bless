#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL Effect : public GameObject
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
		// SETTER
		//////////////////////////////////////////////////////////////////////////
	public : /* Original Transform */
		void SetOriginPos(D3DXVECTOR3 pos);
		void SetOriginRot(D3DXVECTOR3 rot);
		void SetOriginScale(D3DXVECTOR3 scale);

	public : /* Start Transform */
		void SetStartPos(D3DXVECTOR3 pos);
		void SetStartRot(D3DXVECTOR3 rot);
		void SetStartScale(D3DXVECTOR3 scale);

	public : /* End Transform */
		void SetEndPos(D3DXVECTOR3 pos);
		void SetEndRot(D3DXVECTOR3 rot);
		void SetEndScale(D3DXVECTOR3 scale);

	public : /* Fade In Out */
		void SetFadeIn(bool fadeIn);
		void SetFadeOut(bool fadeOut);
		void SetFadeInFactor(float factor);
		void SetFadeOutFactor(float factor);

	public : /* Time */
		void SetLifeTime(float time);
		void SetLoopTime(float time);

	public :/* Repeat */
		void SetRepeat(bool isRepeat);

	public : /* UV */
		void SetUVAnimation(bool isAnimation);
		void SetUVDirection(D3DXVECTOR2 uvDirection);
		void SetUVSpeed(float speed);

	


		//////////////////////////////////////////////////////////////////////////
		// GETTER 
		//////////////////////////////////////////////////////////////////////////
	public :
		float GetAlpha();
		D3DXVECTOR2 GetUVOffset();

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		void Reset(std::function<void()> onCompleted = nullptr);


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

		/* UV Animation */
	private :
		bool m_bUVAnim;
		D3DXVECTOR2 m_uvDir;
		D3DXVECTOR2 m_uvOffset;
		float m_uvSpeed;

		/* LifeTime */
	private :
		float m_lifeTime;
		float m_loopTime;
		float m_curLifeTime;
		float m_totalLifeTime;

		/* Repeat */
	private :
		bool m_isRepeat;

	private :
		std::function<void()> m_onCompleted;
	};
}

