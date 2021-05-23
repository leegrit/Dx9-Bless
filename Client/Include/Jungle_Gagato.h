#pragma once
#include "NonePlayer.h"
 
class Jungle_Gagato : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Jungle_Gagato(Scene* pScene);
	virtual ~Jungle_Gagato();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize(std::wstring dataPath);
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;
	virtual bool DoInteract() override;
	virtual std::wstring GetOnlyCharacterName() override;
	virtual D3DXVECTOR3 GetZoomInOffset() override;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static Jungle_Gagato * Create(Scene* pScene, std::wstring dataPath)
	{
		Jungle_Gagato* obj = new Jungle_Gagato(pScene);
		obj->Initialize(dataPath);
		return obj;
	}

};

