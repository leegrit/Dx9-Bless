#pragma once
#include "NonePlayer.h"

class Jungle_Liurens : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Jungle_Liurens(Scene* pScene);
	virtual ~Jungle_Liurens();

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
	static Jungle_Liurens * Create(Scene* pScene, std::wstring dataPath)
	{
		Jungle_Liurens* obj = new Jungle_Liurens(pScene);
		obj->Initialize(dataPath);
		return obj;
	}

};

