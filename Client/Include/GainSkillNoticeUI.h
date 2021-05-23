#pragma once
#include "GameObject.h"


class GainSkillNoticeUI : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit GainSkillNoticeUI(Scene* pScene);
	virtual ~GainSkillNoticeUI();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Render() override;
	virtual void Update() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public:
	void OnGainSkill(void*);

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	void Initialize();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	UIPanel* m_pBackground = nullptr;
	UIPanel* m_pIcon = nullptr;
	bool m_bGainSkill = false;
	std::wstring m_renderFont;
	float m_elapsed = 0;
	const float m_delay = 3;
	const float m_fadeInTime = 0.5f;
	const float m_fadeOutTime = 0.5f;
	D3DXCOLOR m_color;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static GainSkillNoticeUI * Create(Scene* pScene);
};

