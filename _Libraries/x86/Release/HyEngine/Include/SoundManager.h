#pragma once

// ä�� ���� 32��

#define MAX_CHANNEL 32

struct ChannelInfo
{
	DWORD channelID;
	std::string tag;
	bool isPlaying;
	float volume;
};

enum class EVolumeTYPE
{
	RelativeVolume, // ������� ��ġ�� �Ҹ��� �۾����� Ŀ����.
	AbsoluteVolume, // ��ġ�� ������� ������ �������� ���´�.
};

struct SoundDesc
{
	EVolumeTYPE volumeType;
	float volume;
	D3DXVECTOR3 soundPosition;
	DWORD channelMode; // FMOD_LOOP_NORMAL, FMOD_LOOP_OFF

};

class ENGINE_DLL SoundManager
{
	DECLARE_SINGLETON(SoundManager)

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
private :
	SoundManager();
	~SoundManager();
	
	//////////////////////////////////////////////////////////////////////////
	// INITIALIZER
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize();

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Update();

	/* SoundTag�� Key������ �Ѵ�. */
	bool PlaySound(std::string tag, TCHAR* pFileName, SoundDesc desc);

	bool StopSound(std::string tag);
	void StopAll();

	bool IsPlaying(std::string tag);
	bool SetVolume(std::string tag, float volume);

private :
	void LoadSoundFile();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	std::unordered_map<TCHAR*, FMOD_SOUND*> m_sounds;

private : /* For Sound Infos */

private : /* For FMOD */
	FMOD_SYSTEM* m_pSystem;
	FMOD_CHANNEL* m_pChannels[MAX_CHANNEL];

	ChannelInfo m_soundPool[MAX_CHANNEL];
};

#define SOUND SoundManager::Get()