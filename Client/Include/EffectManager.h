#pragma once

namespace HyEngine
{
	class Effect;
}

namespace AfterEffectOption
{
	static DWORD ScaleEffect = 1;
	static DWORD FadeOut = 2;

}

struct AfterEffectDesc
{
	friend class EffectManager;
public:
	int animIndex;
	float lifeTime;
	D3DXCOLOR color;

private :
	float elapsed = 0;
	int index = -1;
	class PlayerAfterImage* pPlayerAfterImage = nullptr;
	bool isPlay = false;
};
struct WeaponAfterEffectDesc
{
	friend class EffectManager;
public:
	float lifeTime;
	D3DXCOLOR color;
	D3DXMATRIX worldMat;
private:
	float elapsed = 0;
	int index = -1;
	class WeaponAfterImage* pWeaponAfterImage = nullptr;
	bool isPlay = false;
};


struct MeshEffectDesc
{
	/* start offset */
	D3DXVECTOR3 startPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 startRot = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 startScale = D3DXVECTOR3(0, 0, 0);
	
	/* end offset */
	D3DXVECTOR3 endPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 endRot = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 endScale = D3DXVECTOR3(0, 0, 0);

	/* Fade In Out */
	bool fadeIn = false;
	bool fadeOut = false;
	float fadeInFactor = 0.2f;
	float fadeOutFactor = 0.2f;

	/* Time */
	float lifeTime = 1.0f;
	float loopTime = 1.0f;

	/* Repeat */
	bool isRepeat = false;

	/* UV */
	bool isUVAnim = false;
	D3DXVECTOR2 uvDirection = D3DXVECTOR2(0, 0);
	float uvSpeed = 0;

	/* Mesh Path */
	std::wstring meshPath;
	 
	/* Texture Path */
	std::wstring diffusePath;
	std::wstring alphaMaskPath;
};

class PlayerAfterImage;
class WeaponAfterImage;
class EffectManager
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	EffectManager(class GameScene* pScene);
	~EffectManager();

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHID
	//////////////////////////////////////////////////////////////////////////
public:
	void Initialize();
	void Update();

public :
	Effect* AddEffect(std::wstring key, MeshEffectDesc desc);
	Effect* AddEffect(std::wstring, Effect* pEffect);
	Effect* GetEffect(std::wstring key);

	void PlayEffect(std::wstring key);

	//////////////////////////////////////////////////////////////////////////
	// FOR AFTER EFFECT
	//////////////////////////////////////////////////////////////////////////
public : 
	int AddAfterEffect(AfterEffectDesc desc, _Out_ int* pIndex); // return index
	void PlayAffterEffect(int index);

	//////////////////////////////////////////////////////////////////////////
	// FOR WEAPON AFTER EFFECT
	//////////////////////////////////////////////////////////////////////////
public :
	void PlayerWeaponAffterEffect(WeaponAfterEffectDesc desc);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	class GameScene* m_pScene = nullptr;

private : /* PlayerAffterImage */
	// max = 3°³
	std::vector<PlayerAfterImage*> m_playerAfterImages;
	std::vector<AfterEffectDesc> m_afterEffectDescs;

private : /* WeaponAfterImage */
	// max = 10°³
	std::vector<WeaponAfterImage*> m_weaponAfterImages;
	std::vector<WeaponAfterEffectDesc> m_weaponAfterEffectDescs;

private :
	std::unordered_map<std::wstring, Effect*> m_effects;




};

