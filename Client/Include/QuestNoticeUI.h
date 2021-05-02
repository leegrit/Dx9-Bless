#pragma once
#include "GameObject.h"



using namespace HyEngine;

enum class EQuestNoticeType
{
	MainQuestAccept,
	MainQuestCompletelyClear,
	SubQuestAccept,
	SubQuestCompletelyClear
};

struct QuestNoticeDesc
{
	std::wstring questName;
	EQuestNoticeType type;
};

class QuestNoticeUI : public GameObject
{
	///////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit QuestNoticeUI(Scene* pScene, std::wstring name);
	virtual ~QuestNoticeUI() = default;

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Render() override;
	virtual void Update() override;
	
	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	 void Initialize();
	 void PushQuestNotice(std::wstring questName, EQuestNoticeType type);

	 //////////////////////////////////////////////////////////////////////////
	 // VARIABLES
	 //////////////////////////////////////////////////////////////////////////
private :
	UIPanel * m_pBackground = nullptr;
	UIPanel * m_pArrowLeft = nullptr;
	UIPanel * m_pArrowRight = nullptr;
	UIPanel * m_pMainClearIcon = nullptr;
	UIPanel * m_pSubClearIcon = nullptr;

	std::wstring m_questName;
	float m_elapsed = 0;
	const float m_delay = 2;
	const float m_fadeInTime = 0.3f;
	const float m_fadeOutTime = 0.3f;
	std::queue<QuestNoticeDesc> m_notices;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static QuestNoticeUI* Create(Scene* pScene, std::wstring name);
};

