#pragma once
#include "GameObject.h"

using namespace HyEngine;

class WarpPoint  : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit WarpPoint(Scene* pScene, std::wstring name);
	virtual ~WarpPoint();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize();
	virtual void Update() override;
	virtual void Render() override;


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void DoWarp();
	void SetWarpScene(int sceneIndex);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	float m_radius = 20;
	int m_sceneIndex = -1;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static WarpPoint* Create(Scene* pScene,int sceneIndex , std::wstring name);
};

