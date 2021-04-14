#pragma once
#include "Scene.h"

namespace HyEngine
{
	class Pawn;
	class Equipment;
}

using namespace HyEngine;
class SampleScene : public Scene
{
	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void LoadAsync(std::function<void(int, int)> onProgress) override;
	virtual void RenderGUI() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :
	void OnModeChanged(void*);

private :
	Camera * m_pEditCam = nullptr;
	Camera * m_pGameCam = nullptr;

	// test
	Pawn* m_pPawn;

	Equipment * m_pEquip;

public:
	/* 임시 무기 위치 찾기 위해 사용 */
	static char temp[256];
};

