#include "StandardEngineFramework.h"
#include "D3DXMeshObject.h"

using namespace HyEngine;


HyEngine::D3DXMeshObject::D3DXMeshObject(Scene * scene, GameObject * parent, ED3DXMeshType meshType, const std::wstring & name) 
	: GameObject(ERenderType::RenderD3DXMesh, scene, parent, name)
{
	switch (meshType)
	{
	case ED3DXMeshType::Box:
		D3DXCreateBox
		(
			DEVICE,
			2.0f, // width
			2.0f, // height
			2.0f, // depth
			&m_pMesh,
			0
		);
		break;
	case ED3DXMeshType::Torus:
		D3DXCreateTorus(
			DEVICE,
			1.0f, // inner radius
			3.0f, // outer radius
			10,   // sides
			10,   // rings
			&m_pMesh,
			0);

		break;
	case ED3DXMeshType::Cylinder:
		D3DXCreateCylinder
		(
			DEVICE,
			1.0f, // radius at negative z end
			1.0f, // radius at positive z end
			3.0f, // length of cylinder
			10, // slices
			10, // stacks
			&m_pMesh,
			0
		);
		break;
	case ED3DXMeshType::Sphere:
		D3DXCreateSphere(
			DEVICE,
			1.0f, // radius
			10,   // slices
			10,   // stacks
			&m_pMesh,
			0);
		break;
	default:
		break;
	}
}

HyEngine::D3DXMeshObject::~D3DXMeshObject()
{
}

void HyEngine::D3DXMeshObject::Initialize()
{
	
}

void HyEngine::D3DXMeshObject::Render()
{
	GameObject::Render();

}

void HyEngine::D3DXMeshObject::Draw()
{
	m_pMesh->DrawSubset(0);
}
