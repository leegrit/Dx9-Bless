#pragma once
#include "NonePlayer.h"


class Guido : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Guido(Scene *pScene);
	virtual ~Guido();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static Guido* Create(Scene* pScene, std::wstring dataPath);


	
};

