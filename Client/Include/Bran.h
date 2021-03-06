#pragma once
#include "NonePlayer.h"

class Bran : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Bran(Scene* pScene);
	virtual ~Bran();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath);
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;
	virtual std::wstring GetOnlyCharacterName() override;
	virtual D3DXVECTOR3 GetZoomInOffset() override;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static Bran* Create(Scene* pScene, std::wstring dataPath);


	// Inherited via NonePlayer

};

