#pragma once
#include "UIElement.h"

namespace HyEngine
{
	class TextureQuad;
	class ProgressBar;
}

using namespace HyEngine;
class QuestGuideUI : public UIElement
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit QuestGuideUI(Scene* pScene, std::wstring name);
	virtual ~QuestGuideUI();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	 virtual void Initialize(EQuestImportance questImportance);
	 virtual void Render() override;


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void ShowGuideUI(std::wstring questName, std::wstring questContent, float yOffset, float progress = -1);
	void HideGuideUI();


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Render */
	UIPanel* m_pHeadline = nullptr;
	UIPanel* m_pIcon = nullptr;
	UIPanel* m_pFillBack = nullptr;
	ProgressBar * m_pFill = nullptr;
	
private : /* For Quest */
	std::wstring m_questName;
	std::wstring m_questContent;
	const float m_yOrigin = 182;
	const float m_yFontTitleOri = 193;
	const float m_yFontContentOri = 220;
	const float m_yFillOrigin = 117;
	float m_yOffset;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static QuestGuideUI * Create
	(
		Scene* pScene,
		EQuestImportance questImportance,
		std::wstring name
	);
};

