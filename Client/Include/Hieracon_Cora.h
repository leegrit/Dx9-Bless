#pragma once
#include "NonePlayer.h"

class Hieracon_Cora : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit Hieracon_Cora(Scene* pScene);
	virtual ~Hieracon_Cora();

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
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
	class FontTexture * m_pNameTexture = nullptr;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static Hieracon_Cora * Create(Scene* pScene, std::wstring dataPath)
	{
		Hieracon_Cora* obj = new Hieracon_Cora(pScene);
		obj->Initialize(dataPath);
		return obj;
	}
};

