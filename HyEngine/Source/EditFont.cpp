#include "StandardEngineFramework.h"
#include "EditFont.h"

HyEngine::EditFont::EditFont(Scene * pScene, int editID)
	: GameObject(ERenderType::None, pScene, nullptr, L"EditFont")
{
	SetEditID(editID);
}

HyEngine::EditFont::~EditFont()
{
}

void HyEngine::EditFont::Initialize()
{

}

void HyEngine::EditFont::Update()
{
	EDIT_ENGINE->DrawText(GetName().c_str(), m_pTransform->m_position.operator D3DXVECTOR3(), m_pTransform->m_scale.operator D3DXVECTOR3(), D3DXCOLOR(0, 1, 0, 1), DT_CENTER);
}

EditFont * HyEngine::EditFont::Create(Scene * pScene, int editID)
{
	EditFont * obj = new EditFont(pScene, editID);
	obj->Initialize();
	return obj;
}
