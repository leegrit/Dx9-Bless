#include "stdafx.h"
#include "HGoblinCinematicTrack.h"
#include "ZoomInCamera.h"
#include "HGoblin.h"
#include "SoundManager.h"
HGoblinCinematicTrack::HGoblinCinematicTrack(GameObject * pHGoblin)
	: CinematicTrack()
{

	ZoomInCamera * zoomInCam = ZoomInCamera::Create(SCENE, pHGoblin, L"HGoblin_ZoomCam");
	zoomInCam->SetOffset(D3DXVECTOR3(0, 30, 50));
	m_pCinematicCamera = zoomInCam;
	
	m_pHGoblin = dynamic_cast<HGoblin*>( pHGoblin);
	assert(m_pHGoblin);

}

HGoblinCinematicTrack::~HGoblinCinematicTrack()
{
}

bool HGoblinCinematicTrack::TrackUpdate()
{
	assert(m_pHGoblin);

	bool isEnd =m_pHGoblin->IsAnimationSetEnd();
	return isEnd;
}

void HGoblinCinematicTrack::OnBegin()
{
	m_originCamName = SCENE->GetSelectedCamera()->GetName();
	SCENE->SelectCamera(m_pCinematicCamera->GetName());

	m_pHGoblin->StopFSM();
	m_pHGoblin->SetAnimationSet(7);

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_NORMAL;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->StopSound("BGM");
	SOUND->PlaySound("BGM", L"BossBattle.mp3", desc);
}

void HGoblinCinematicTrack::OnEnd()
{
	m_pHGoblin->PlayFSM();
	SCENE->SelectCamera(m_originCamName);
}



