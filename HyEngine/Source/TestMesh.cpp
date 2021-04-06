#include "StandardEngineFramework.h"
#include "TestMesh.h"
#include "Collider.h"
#include "SphereCollider.h"

HyEngine::TestMesh::TestMesh(Scene * scene, GameObject * parent)
	: GameObject(ERenderType::RenderOpaque, scene, parent, L"TestMesh")
{
	//assert(false);
	m_pMesh = MeshLoader::GetMesh("../../../Resources/Mesh/Cube.obj");
	//assert(m_pMesh);
	m_pBaseTex = (IDirect3DTexture9*)(TextureLoader::GetTexture(L"../../../Resources/Texture/Checker.png"));
}

HyEngine::TestMesh::~TestMesh()
{
	
	m_pMesh.reset();
	SAFE_RELEASE(m_pBaseTex);
}

void HyEngine::TestMesh::Initialize()
{
	m_pCollider = SphereCollider::Create(EColliderType::Dynamic, this, 1, Layer::Player, [](Collider*) {});
	m_pTransform->SetScale(10, 10, 10);
}

void HyEngine::TestMesh::Render()
{
	//if (m_bInit == false) return;
	GameObject::Render();
	/*if (m_pMesh)
	{
		m_pMesh = MeshLoader::GetMesh(CString::ToString(L"../Resources/Mesh/Cube.obj"));


		assert(m_pMesh);
	}*/

	DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
	DEVICE->SetIndices(m_pMesh->GetIndexBuffer());

	assert(m_pBaseTex);
	DEVICE->SetTexture(0, m_pBaseTex);

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
}
