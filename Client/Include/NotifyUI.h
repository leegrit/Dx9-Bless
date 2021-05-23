#pragma once
#include "GameObject.h"

struct NotifyMessage
{
	std::wstring message;
	float elapsed;
	float xPos;
};

using namespace HyEngine;
class NotifyUI : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit NotifyUI(Scene* pScene, std::wstring name);
	virtual ~NotifyUI();


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
	void PushNotify(ENotifyType notifyType);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private:
	std::vector<NotifyMessage> m_notifyMessages;
	const int m_notifyMessageMax = 3;
	const float m_delay = 2;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static NotifyUI* Create(Scene* pScene, std::wstring name);
};

