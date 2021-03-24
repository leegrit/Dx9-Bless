#include "StandardEngineFramework.h"
#include "GameObject.h"
#include "Component.h"

using namespace HyEngine;

GameObject::GameObject(ERenderType renderType, Scene* scene, GameObject * parent,  const std::wstring& name)
	: Object(name),
	m_renderType(renderType),
	m_bActiveSelf(true),
	m_bViewFrustumCulled(false),
	m_pScene(scene),
	m_pParent(parent),
	m_tag(EngineTags::Default),
	m_layer(Layer::Default),
	m_renderQueue(3000)
{
	//assert(false);
	m_pTransform = new Transform(this);
	switch (renderType)
	{
	case ERenderType::RenderMesh :
		m_pScene->AddMeshObject(this);
		break;
	case ERenderType::RenderTexture:
		m_pScene->AddTextureObject(this);
		break;
	case ERenderType::RenderUI :
		m_pScene->AddUIObject(this);
		break;
	case ERenderType::None:
		m_pScene->AddInvisibleObject(this);
		break;
	}
	if (m_pParent)
		m_pParent->AddChild(this);
}


//GameObject::GameObject(ERenderType renderType, Scene* scene, GameObject* parent, const std::wstring& tag,
//	const Vector3& originPos,
//	const Quaternion& originRot,
//	const Vector3& originScale)
//	: Object(tag),
//	m_renderType(renderType),
//	m_bActiveSelf(true),
//	m_pScene(scene),
//	m_pParent(parent),
//	m_tag(tag)
//{
//	m_pTransform = new Transform(this, originPos, originRot, originScale);
//	/*switch (renderType)
//	{
//	case ERenderType::RenderOpaque:
//		m_pScene->AddOpaqueObject(this);
//		break;
//	case ERenderType::RenderAlpha:
//		m_pScene->AddAlphaObject(this);
//		break;
//	case ERenderType::Texture:
//		m_pScene->AddTextureObject(this);
//		break;
//	case ERenderType::AlphaTexture:
//		m_pScene->AddAlphaTextureObject(this);
//		break;
//	case ERenderType::UI:
//		m_pScene->AddUIObject(this);
//		break;
//	case ERenderType::None:
//		m_pScene->AddInvisibleObject(this);
//		break;
//	}*/
//	switch (renderType)
//	{
//	case ERenderType::RenderMesh:
//		m_pScene->AddMeshObject(this);
//		break;
//	case ERenderType::RenderTexture:
//		m_pScene->AddTextureObject(this);
//		break;
//	case ERenderType::RenderUI:
//		m_pScene->AddUIObject(this);
//		break;
//	}
//	if (m_pParent)
//		m_pParent->AddChild(this);
//}


GameObject::~GameObject()
{
	if (m_pParent)
		m_pParent->RemoveChild(this);
	
	delete m_pTransform;

	for (auto& com : m_components)
	{
		Object::DestroyImmediate(com);
	}
	m_components.clear();

	for (auto& child : m_pChilds)
	{
		child->SetActive(false);
		child->m_pParent = nullptr;
		Object::Destroy(child);
	}
	m_pChilds.clear();
}



void GameObject::Update()
{
	for (auto& com : m_components)
	{
		if (com->GetBehaviourType() & BehaviourType::Update)
		{
			if(com->GetActive() == true)
				com->Update();
		}
	}
}

void GameObject::LateUpdate()
{
	for (auto& com : m_components)
	{
		if (com->GetBehaviourType() & BehaviourType::LateUpdate)
		{
			if(com->GetActive() == true)
				com->LateUpdate();
		}
	}
	for (UINT i = 0; i < m_components.size(); i++)
	{
		if (m_components[i]->m_bWantsDestroy)
		{
			Object::DestroyImmediate(m_components[i]);
			m_components.erase(m_components.begin() + i);
		}
	}

}

void GameObject::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
}

bool GameObject::CompareTag(std::wstring tag)
 {
	 return m_tag == tag;
 }

std::wstring HyEngine::GameObject::GetTag() const
{
	return m_tag;
}

 void HyEngine::GameObject::SetActive(bool active)
{
	 for (auto& com : m_components)
	 {
		 com->SetActive(active);
	 }
	 for (auto& child : m_pChilds)
	 {
		 child->SetActive(active);
	 }
	if (m_bActiveSelf != active)
	{
		if (active == true)
			OnEnable();
		else
			OnDisable();
	}
	
	m_bActiveSelf = active;
}

void HyEngine::GameObject::SetTag(std::wstring tag)
{
	m_tag = tag;
}

GameObject * HyEngine::GameObject::GetParent()
{
	return m_pParent;
}

Scene * HyEngine::GameObject::GetScene()
{
	return m_pScene;
}
