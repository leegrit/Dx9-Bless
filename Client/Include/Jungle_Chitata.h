#pragma once
#include "NonePlayer.h"

class Jungle_Chitata : public NonePlayer
{ 
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Jungle_Chitata(Scene * pScene);
	virtual ~Jungle_Chitata();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize(std::wstring dataPath);
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;
	virtual std::wstring GetOnlyCharacterName() override;
	virtual D3DXVECTOR3 GetZoomInOffset() override;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static Jungle_Chitata * Create(Scene* pScene, std::wstring dataPath)
	{
		Jungle_Chitata* obj = new Jungle_Chitata(pScene);
		obj->Initialize(dataPath);
		return obj;
	}
};

