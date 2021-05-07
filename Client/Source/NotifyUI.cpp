#include "stdafx.h"
#include "NotifyUI.h"

NotifyUI::NotifyUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

NotifyUI::~NotifyUI()
{
}

void NotifyUI::Initialize()
{
}

void NotifyUI::Update()
{
	if (m_notifyMessages.size() == 0)return;

	for (int i = 0; i < m_notifyMessages.size(); i++)
	{
		m_notifyMessages[i].elapsed += TIMER->getDeltaTime();
		if (m_notifyMessages[i].elapsed >= m_delay)
		{
			m_notifyMessages.erase(m_notifyMessages.begin() + i);
			i--;
			continue;
		}
		float alpha = (m_delay - m_notifyMessages[i].elapsed) / m_delay;
		ENGINE->DrawText(m_notifyMessages[i].message.c_str(),
			D3DXVECTOR3(m_notifyMessages[i].xPos, 230 - ((m_notifyMessages.size() - 1) - i) * 30, 0), D3DXVECTOR3(1, 1, 1),
			D3DXCOLOR(1, 1, 1, alpha));
	}
}

void NotifyUI::Render()
{
	assert(false);
}

void NotifyUI::PushNotify(ENotifyType notifyType)
{
	if (m_notifyMessages.size() >= m_notifyMessageMax)
	{
		m_notifyMessages.erase(m_notifyMessages.begin());
	}

	NotifyMessage message;
	message.elapsed = 0;
	switch (notifyType)
	{
	case ENotifyType::BuyItemNotify:
		message.message = L"아이템을 구매하였습니다.";
		message.xPos = 445;
		break;
	case ENotifyType::InvalidCoolTime:
		message.message = L"재사용 대기시간 중에는 사용할 수 없습니다.";
		message.xPos = 387;
		break;
	case ENotifyType::InvalidTarget:
		message.message = L"올바른 대상을 선택하십시오.";
		message.xPos = 434;
		break;
	case ENotifyType::GetItemNotify :
		message.message = L"아이템을 획득하였습니다.";
		message.xPos = 445;
		break;
	default:
		assert(false);
		break;
	}
	m_notifyMessages.push_back(message);
}

NotifyUI * NotifyUI::Create(Scene * pScene, std::wstring name)
{
	NotifyUI * obj = new NotifyUI(pScene, name);
	obj->Initialize();
	return obj;
}
