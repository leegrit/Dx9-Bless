#include "StandardEngineFramework.h"
#include "SoundManager.h"
#include "PathManager.h"
#include "CString.h"

IMPLEMENT_SINGLETON(SoundManager)

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	for (auto& Mypair : m_sounds)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_sounds.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void SoundManager::Initialize()
{
	FMOD_System_Create(&m_pSystem);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, MAX_CHANNEL, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		m_soundPool[i].channelID = i;
		m_soundPool[i].tag = "";
		m_soundPool[i].volume = 1;
		m_soundPool[i].isPlaying = false;
	}
}

void SoundManager::Update()
{
	assert(m_pSystem);
	FMOD_System_Update(m_pSystem);

	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		FMOD_BOOL bPlay = FALSE;
		FMOD_Channel_IsPlaying(m_pChannels[i], &bPlay);

		m_soundPool[i].isPlaying = bPlay;
	}
}

bool SoundManager::PlaySound(std::string tag, TCHAR * pFileName, SoundDesc desc)
{
	auto iter = find_if(m_sounds.begin(), m_sounds.end(), [&](auto& iter)
	{
		return !lstrcmp(pFileName, iter.first);
	});

	if (iter == m_sounds.end())
		return false;

	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_soundPool[i].isPlaying == false)
		{
			m_soundPool[i].tag = tag;
			m_soundPool[i].volume = desc.volume;
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannels[i]);
			FMOD_Channel_SetMode(m_pChannels[i], desc.channelMode);
			FMOD_Channel_SetVolume(m_pChannels[i], desc.volume);
			return true;
		}
	}
	SEND_LOG_WARNING("Full FMOD Channel");
	return false;
}

bool SoundManager::StopSound(std::string tag)
{
	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_soundPool[i].tag.compare(tag) == 0)
		{
			FMOD_Channel_Stop(m_pChannels[i]);
			return true;
		}
	}
	SEND_LOG_WARNING("Not Found Tag in StopSound Function, TAG : " + tag);
	return false;
}

void SoundManager::StopAll()
{
	for (int i = 0; i < MAX_CHANNEL; i++) 
	{
		FMOD_Channel_Stop(m_pChannels[i]);
	}
}

bool SoundManager::IsPlaying(std::string tag)
{
	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_soundPool[i].tag.compare(tag) == 0)
		{
			return m_soundPool[i].isPlaying;
		}
	}
	SEND_LOG_WARNING("Not Found Tag in IsPlaying Function, TAG : " + tag);
	return false;
}

bool SoundManager::SetVolume(std::string tag, float volume)
{
	for (int i = 0; i < MAX_CHANNEL; i++)
	{
		if (m_soundPool[i].tag.compare(tag) == 0)
		{
			 m_soundPool[i].volume = volume;
			 FMOD_Channel_SetVolume(m_pChannels[i], volume);
			 return true;
		}
	}
	SEND_LOG_WARNING("Not Found Tag in SetVolume Function, TAG : " + tag);
	return false;
}

void SoundManager::LoadSoundFile()
{
	_finddata_t fd;

	char path[45];
	//strcpy_s(path,45, (PATH->AssetsPath() + "Sound/*").c_str());

	std::string temp = (PATH->AssetsPath() + "Sound/*.*");
	CString::Replace(&temp, "/", "\\");
	intptr_t  handle = _findfirst(temp.c_str(), &fd);
	/*if (handle = _findfirst(temp.c_str(), &fd) == -1L)
	{
		int a = 0;
	}*/
	std::string onlyPath = PATH->AssetsPath() + "Sound/";
	char fullPath[128] = "";

	int result = 0;
	while (result != -1)
	{
		strcpy_s(fullPath, onlyPath.c_str());
		strcat_s(fullPath, fd.name);
		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, fullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_sounds.emplace(pSoundKey, pSound);
		}
		result = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pSystem);
	_findclose(handle);
}
