#pragma once
#include "NonePlayer.h"
class Leoni : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Leoni(Scene* pScene);
	virtual ~Leoni();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath);
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static Leoni * Create(Scene* pScene, std::wstring dataPath)
	{
		Leoni* obj = new Leoni(pScene);
		obj->Initialize(dataPath);
		return obj;
	}
};

