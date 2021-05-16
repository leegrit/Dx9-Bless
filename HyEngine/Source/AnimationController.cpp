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

	// ���� ����Ǵ� Ʈ�� ������ �������� �Լ�.
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	// ������ Ʈ�� ������ Position���� ���� Ʈ���� �� ������ ���� ���Ͽ� ��ȯ���� ������.
	// 0.1�� interval, �� ������ �ð��� �ִ� �뵵.
	if (trackInfo.Position >= m_period - endTime)
		return true;

	return false;
}

bool HyEngine::AnimationController::IsAnimationAfterTrack(double afterTime)
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	// ���� ����Ǵ� Ʈ�� ������ �������� �Լ�
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	// ������ Ʈ�� ������ position���� ���� Ʈ���� �� ������ ���� ���Ͽ� ��ȯ���� ������.
	// 0.1�� interval, ������ �ð��� �ִ� �뵵.
	if (trackInfo.Position >= afterTime)
		return true;

	return false;
}

const UINT & HyEngine::AnimationController::GetAnimationNum()
{
	// �ִϸ��̼��� �� ������ ��ȯ.
	return m_pAniCtrl->GetNumAnimationSets();
}

double HyEngine::AnimationController::GetCurAnimationPosition()
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	// ���� ����Ǵ� Ʈ�� ������ �������� �Լ�.
	m_pAniCtrl->GetTrackDesc(m_currentTrack, &trackInfo);

	return trackInfo.Position;
}

void HyEngine::AnimationController::SetAnimationSet(const UINT & index)
{
	// ���� �ִϸ��̼ǰ� ���� �ε����� ������
	// ���� �ٽ� Set�� ���� �ʿ䰡 ����.
	if (m_oldAniIndex == index)
		return;

	// �� Ʈ���� ��ȣ�� ���� �޶���Ѵ�. ��ġ�� �ȵȴ�.
	m_newTrack = m_currentTrack == 0 ? 1 : 0;

	LPD3DXANIMATIONSET pAs = NULL;

	// �ִϸ��̼� ���� �ε����� �������� ���
	// m_pAniCtrl->GetAnimationSetByName(); �ִϸ��̼� ���� ���ڿ��� ã�� �������� �Լ�
	m_pAniCtrl->GetAnimationSet(index, &pAs);
	// �ִϸ��̼��� ������ ������ üũ�ϱ� ���� �Լ�
	// �̶� ��ȯ�ϴ� ���� ���� �ִϸ��̼� Ʈ���� �����ǰ� ��ġ�ϴ� ��.
	m_period = pAs->GetPeriod();

	// 0�� Ʈ���� ���� �ִϸ��̼� ���� �����Ѵ�.
	m_pAniCtrl->SetTrackAnimationSet(m_newTrack, pAs);

	// �޽� �ȿ� ���Ե� ���� ����Ʈ�� ���� ȿ������ ������� �ʰڴٰ� ����� �������Ѵ�.
	// �̺�Ʈ ���� ������ ��ĩ ���� ������ �ȵǴ� ��쵵 �߻��ϱ� �����̴�.
	m_pAniCtrl->UnkeyAllTrackEvents(m_currentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_newTrack);

	// Ű ������ : �ִϸ��̼� �� ��� �� ��� ������ �ǹ��Ѵ�. (Ư�� �ð����� �����ִ� ���� ����)
	
	// ���� ����ǰ� �ִ� ������ ���� �Ѵ� �Լ�
	// �� ��° ���� : ���ڰ��� �ݵ�� double Ÿ���̾�� �Ѵ�. ����ǰ� �ִ� �ִϸ��̼� Ű �����ӿ� interval �� ����.
	m_pAniCtrl->KeyTrackEnable(m_currentTrack, FALSE, m_accTime + 0.25);

	// 0.25��� interval ������ ����Ǵ� Ű�������� �ӵ��� �����ϴ� �Լ�.
	m_pAniCtrl->KeyTrackSpeed(m_currentTrack, 1.f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	// �ִϸ��̼� �� �ռ� �ÿ� ����ġ�� �������ִ� �Լ�.
	m_pAniCtrl->KeyTrackWeight(m_currentTrack, 0.1f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->SetTrackEnable(m_newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_newTrack, 1.f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_newTrack, 0.9f, m_accTime, 0.25, D3DXTRANSITION_LINEAR);

	// AdvanceTime �Լ��� ȣ��Ǹ� �ִϸ��̼��� ����Ǵ� ���� 
	// ���������� �ð��� �����ϰ��ֱ� ������ �������ش�.
	m_pAniCtrl->ResetTime();
	m_accTime = 0.f;

	// ���� ������̴� Ʈ������ �� Ʈ������ ��ü�߱� ������ �ִϸ��̼� ��� ��ġ�� 0.0���� �ٲ۴�.
	m_pAniCtrl->SetTrackPosition(m_newTrack, 0.0);

	m_oldAniIndex = index;
	m_currentTrack = m_newTrack;
}

void HyEngine::AnimationController::PlayAnimationSet(const float & deltaTime)
{
	// �ִϸ��̼��� ����ϴ� �Լ�
	// �� ��° ���� : �ִϸ��̼� ���ۿ� ���� ����Ʈ �Ǵ� ���� ��ü�� �ּ�
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
