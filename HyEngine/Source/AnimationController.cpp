#include "StandardEngineFramework.h"
#include "AnimationController.h"

HyEngine::AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl),
	m_currentTrack(0),
	m_newTrack(1),
	m_oldAniIndex(99),
	m_accTime(0.f)
{
	m_pAniCtrl->AddRef();
}

HyEngine::AnimationController::AnimationController(const AnimationController & rhs)
	: m_currentTrack(rhs.m_currentTrack),
	m_accTime(rhs.m_accTime),
	m_newTrack(rhs.m_newTrack),
	m_oldAniIndex(rhs.m_oldAniIndex)
{
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(),
		rhs.m_pAniCtrl->GetMaxNumAnimationSets(),
		rhs.m_pAniCtrl->GetMaxNumTracks(),
		rhs.m_pAniCtrl->GetMaxNumEvents(),
		&m_pAniCtrl);
}

HyEngine::AnimationController::~AnimationController()
{
	SAFE_RELEASE(m_pAniCtrl);
}

bool HyEngine::AnimationController::IsAnimationSetEnd(double endTime)
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	// 현재 재생되는 트랙 정보를 가져오는 함수.
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	// 가져온 트랙 정보의 Position값과 현재 트랙의 끝 지점을 서로 비교하여 반환값을 나눈다.
	// 0.1은 interval, 즉 보간할 시간을 주는 용도.
	if (trackInfo.Position >= m_period - endTime)
		return true;

	return false;
}

bool HyEngine::AnimationController::IsAnimationAfterTrack(double afterTime)
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	// 현재 재생되는 트랙 정보를 가져오는 함수
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	// 가져온 트랙 정보의 position값과 현재 트랙의 끝 지점을 서로 비교하여 반환값을 나눈다.
	// 0.1은 interval, 보간할 시간을 주는 용도.
	if (trackInfo.Position >= afterTime)
		return true;

	return false;
}

const UINT & HyEngine::AnimationController::GetAnimationNum()
{
	// 애니메이션의 총 개수를 반환.
	return m_pAniCtrl->GetNumAnimationSets();
}

double HyEngine::AnimationController::GetCurAnimationPosition()
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	// 현재 재생되는 트랙 정보를 가져오는 함수.
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	return trackInfo.Position;
}

void HyEngine::AnimationController::SetAnimationSet(const UINT & index)
{
	// 이전 애니메이션과 같은 인덱스가 들어오면
	// 굳이 다시 Set을 해줄 필요가 없다.
	if (m_oldAniIndex == index)
		return;

	// 각 트랙의 번호가 서로 달라야한다. 겹치면 안된다.
	m_newTrack = m_currentTrack == 0 ? 1 : 0;

	LPD3DXANIMATIONSET pAs = NULL;

	// 애니메이션 셋을 인덱스로 가져오는 방법
	// m_pAniCtrl->GetAnimationSetByName(); 애니메이션 셋을 문자열로 찾아 가져오는 함수
	m_pAniCtrl->GetAnimationSet(index, &pAs);
	// 애니메이션이 끝나는 지점을 체크하기 위한 함수
	// 이때 반환하는 값은 현재 애니메이션 트랙의 포지션과 일치하는 값.
	m_period = pAs->GetPeriod();

	// 0번 트랙에 얻어온 애니메이션 셋을 세팅한다.
	m_pAniCtrl->SetTrackAnimationSet(m_newTrack, pAs);

	// 메쉬 안에 삽입된 각종 이펙트와 같은 효과들을 사용하지 않겠다고 명령을 내려야한다.
	// 이벤트 정보 때문에 자칫 선형 보간이 안되는 경우도 발생하기 때문이다.
	m_pAniCtrl->UnkeyAllTrackEvents(m_currentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_newTrack);

	// 키 프레임 : 애니메이션 셋 재생 중 재생 지점을 의미한다. (특정 시간에서 멈춰있는 동작 상태)
	
	// 현재 진행되고 있는 동작을 끄고 켜는 함수
	// 세 번째 인자 : 인자값은 반드시 double 타입이어야 한다. 재생되고 있던 애니메이션 키 프레임에 interval 값 제공.
	m_pAniCtrl->KeyTrackEnable(m_currentTrack, FALSE, m_accTime + 0.25);

	// 0.25라는 interval 값동안 재생되던 키프레임의 속도를 제어하는 함수.
	m_pAniCtrl->KeyTrackSpeed(m_currentTrack, 1.f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	// 애니메이션 셋 합성 시에 가중치를 지정해주는 함수.
	m_pAniCtrl->KeyTrackWeight(m_currentTrack, 0.1f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->SetTrackEnable(m_newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_newTrack, 1.f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_newTrack, 0.9f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	// AdvanceTime 함수가 호출되면 애니메이션이 재생되는 동안 
	// 내부적으로 시간을 누적하고있기 때문에 리셋해준다.
	m_pAniCtrl->ResetTime();
	m_accTime = 0.f;

	// 기존 재생중이던 트랙에서 새 트랙으로 교체했기 때문에 애니메이션 재생 위치를 0.0으로 바꾼다.
	m_pAniCtrl->SetTrackPosition(m_newTrack, 0.0);

	m_oldAniIndex = index;
	m_currentTrack = m_newTrack;
}

void HyEngine::AnimationController::PlayAnimationSet(const float & deltaTime)
{
	// 애니메이션을 재생하는 함수
	// 두 번째 인자 : 애니메이션 동작에 맞춰 이펙트 또는 사운드 객체의 주소
	HRESULT hr;
	hr=  m_pAniCtrl->AdvanceTime(deltaTime * m_speedFactor, NULL);
	assert(SUCCEEDED(hr));
	m_accTime += (deltaTime * m_speedFactor);
}

const UINT HyEngine::AnimationController::GetCurAnimationIndex()
{
	return m_oldAniIndex;
}

void HyEngine::AnimationController::SetAnimationSpeed(float speedFactor)
{
	m_speedFactor = speedFactor;
}

float HyEngine::AnimationController::GetAnimationSpeed()
{
	return m_speedFactor;
}
