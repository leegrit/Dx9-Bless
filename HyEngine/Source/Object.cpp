#include "StandardEngineFramework.h"
#include "Object.h"

using namespace HyEngine;

Object::Object(std::wstring name)
	: m_bWantsDestroy(false),
	m_name(name)
{	
	m_id = UIDGen::Get()->GetUID();

}


Object::~Object()
{
}
