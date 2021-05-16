#pragma once

namespace HyEngine
{

	class ENGINE_DLL AnimationController
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	public:
		explicit AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl);
		explicit AnimationController(const AnimationController& rhs);
		virtual ~AnimationController();


		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHODS
		//////////////////////////////////////////////////////////////////////////
	public :
		inline LPD3DXANIMATIONCONTROLLER GetAnimationSet() { return m_pAniCtrl; }
		bool IsAnimationSetEnd(double endTime = 0.1);
		bool IsAnimationAfterTrack(double afterTime);
		const UINT& GetAnimationNum();
		double GetCurAnimationPosition();

	public :
		void SetAnimationSet(const UINT& index);
		void PlayAnimationSet(const float& deltaTime);
		const UINT GetCurAnimationIndex();

	public :
		void SetAnimationSpeed(float speedFactor);
		float GetAnimationSpeed();

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		LPD3DXANIMATIONCONTROLLER m_pAniCtrl;
		UINT m_currentTrack; // 현재 애니메이션의 트랙

		// 예전 애니메이션의 인덱스값.
		// 보간할 때 만약 같은 애니메이션의 인덱스라면 
		// 보간이 필요없기 때문에 예외처리에 사용한다.
		UINT m_oldAniIndex; 

		// 보간할 다음 애니메이션 트랙.
		// 보간은 미리 애니메이션이 로드 된 상태에서
		// 서로의 정점을 보간하는 방식을 사용한다.
		// 따라서 트랙이 하나 더 필요하다.
		UINT m_newTrack;

		// 누적시키기 위한 시간값.
		FLOAT m_accTime; 

		// 애니메이션이 끝나는 시점(Position)
		DOUBLE m_period;


		float m_speedFactor = 1;
	};
}

