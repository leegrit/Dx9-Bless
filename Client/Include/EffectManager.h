#pragma once

namespace HyEngine
{
	class Effect;
}

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
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	class GameScene* m_pScene = nullptr;

private :
	std::unordered_map<std::wstring, Effect*> m_effects;




};

