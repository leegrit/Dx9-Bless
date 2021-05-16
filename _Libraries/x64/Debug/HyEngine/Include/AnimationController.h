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

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		LPD3DXANIMATIONCONTROLLER m_pAniCtrl;
		UINT m_currentTrack; // ���� �ִϸ��̼��� Ʈ��

		// ���� �ִϸ��̼��� �ε�����.
		// ������ �� ���� ���� �ִϸ��̼��� �ε������ 
		// ������ �ʿ���� ������ ����ó���� ����Ѵ�.
		UINT m_oldAniIndex; 

		// ������ ���� �ִϸ��̼� Ʈ��.
		// ������ �̸� �ִϸ��̼��� �ε� �� ���¿���
		// ������ ������ �����ϴ� ����� ����Ѵ�.
		// ���� Ʈ���� �ϳ� �� �ʿ��ϴ�.
		UINT m_newTrack;

		// ������Ű�� ���� �ð���.
		FLOAT m_accTime; 

		// �ִϸ��̼��� ������ ����(Position)
		DOUBLE m_period;

	};
}

