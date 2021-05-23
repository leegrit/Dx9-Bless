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
			D3DXVECTOR3(m_notifyMessages[i].xPos, 100 - ((m_notifyMessages.size() - 1) - i) * 30, 0), D3DXVECTOR3(1, 1, 1),
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
		message.message = L"�������� �����Ͽ����ϴ�.";
		message.xPos = 445;
		break;
	case ENotifyType::InvalidCoolTime:
		message.message = L"���� ���ð� �߿��� ����� �� �����ϴ�.";
		message.xPos = 387;
		break;
	case ENotifyType::InvalidTarget:
		message.message = L"�ùٸ� ����� �����Ͻʽÿ�.";
		message.xPos = 434;
		break;
	case ENotifyType::GetItemNotify :
		message.message = L"�������� ȹ���Ͽ����ϴ�.";
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
