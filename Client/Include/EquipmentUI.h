#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Button;
}

enum class EEquipSlot
{
	Helmet,
	Upper,
	Belt,
	Glove,
	Weapon,
	Shoulder,
	Lower,
	Boots,
	MAX
};

using namespace HyEngine;
class EquipmentUI  :public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit EquipmentUI(Scene* pScene, std::wstring name);
	virtual ~EquipmentUI();

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
	void Show();
	void Hide();
	bool IsShow();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Render */
	UIPanel* m_pBackground = nullptr;
	std::vector<Button*> m_equipSlots;
	Button* m_pCloseButton = nullptr;
	UIPanel* m_pUnderLine = nullptr;
	UIPanel* m_pUnderPanel = nullptr;
	UIPanel* m_pClassIcon = nullptr;

	UIPanel* m_pEquipSelectPanel = nullptr;
	class ItemInfoUI* m_pEquipInfoUI = nullptr;
private : /* For Equip Slot */
	const int m_maxSlotVertical = 4;
	const int m_maxSlotHorizontal = 2;
	const int m_maxSlotCount = 8;
	const float m_slotOffset = 60;

private :
	bool m_bShow = false;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	/////////////////////////////////////////////////////////////////////////
public :
	static EquipmentUI* Create(Scene* pScene, std::wstring name);

};

