#include "stdafx.h"
#include "CinematicManager.h"
#include "Client_Events.h"
#include "CinematicTrack.h"


CinematicManager::CinematicManager(GameScene * pScene)
{
}

CinematicManager::~CinematicManager()
{
}

void CinematicManager::Initialize()
{
}

void CinematicManager::Update()
{
	if (m_pCurrentTrack)
	{
		bool isFinish = m_pCurrentTrack->TrackUpdate();
		if (isFinish)
		{
			m_pCurrentTrack->OnEnd();
			EventDispatcher::TriggerEvent(GameEvent::EndCinematic, (void*)m_pCurrentTrack);
			m_pCurrentTrack = nullptr;
			m_isPlayCinematic = false;
		}
	}
}

void CinematicManager::AddCinematic(std::wstring key, CinematicTrack * pCinematicTrack)
{
	m_cinematics.insert(std::make_pair(key, pCinematicTrack));
}

void CinematicManager::PlayCinematic(std::wstring key)
{
	auto track = m_cinematics[key];
	assert(track);
	m_pCurrentTrack = track;
	m_cinematics.erase(key);
	EventDispatcher::TriggerEvent(GameEvent::BeginCinematic, &track);
	m_pCurrentTrack->OnBegin();
	m_isPlayCinematic = true;
}

bool CinematicManager::IsCinematic()
{
	return m_isPlayCinematic;
}
