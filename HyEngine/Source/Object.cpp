#include "StandardEngineFramework.h"
#include "Object.h"

using namespace HyEngine;

Object::Object(std::wstring name)
	: m_bWantsDestroy(false),
	m_bActiveSelf(true),
	m_name(name)
{	
	m_id = UIDGen::Get()->GetUID();

}


Object::~Object()
{
}

void HyEngine::Object::SetActive(bool active)
{
	m_bActiveSelf = active;
}
