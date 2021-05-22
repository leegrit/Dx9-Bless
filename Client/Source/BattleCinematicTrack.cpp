#include "stdafx.h"
#include "BattleCinematicTrack.h"
#include "StaticCamera.h"
#include "SoundManager.h"
BattleCinematicTrack::BattleCinematicTrack(std::vector<GameObject*> actors)
	: CinematicTrack()
{
	StaticCamera* pCam = StaticCamera::Create(SCENE, D3DXVECTOR3(189, 55, 353), D3DXVECTOR3(27, 1497, 0));
	m_pCinematicCamera = pCam;

	m_actors = actors;
}

BattleCinematicTrack::~BattleCinematicTrack()
{
}

bool BattleCinematicTrack::TrackUpdate()
{
	m_elapsed += TIMER->getDeltaTime();
	if (m_elapsed > m_duration)
	{
		m_elapsed = 0;
		return true;
	}
	return false;
}

void BattleCinematicTrack::OnBegin()
{
	m_originCamName = SCENE->GetSelectedCamera()->GetName();
	SCENE->SelectCamera(m_pCinematicCamera->GetName());

	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->SetActive(true);
	}

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_NORMAL;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->StopSound("BGM");
	SOUND->PlaySound("BGM", L"MediumBattleLoop.mp3", desc);
}

void BattleCinematicTrack::OnEnd()
{
	SCENE->SelectCamera(m_originCamName);
	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->SetActive(false);
	}
}
