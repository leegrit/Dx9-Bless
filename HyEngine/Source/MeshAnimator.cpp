#include "StandardEngineFramework.h"
#include "MeshAnimator.h"
#include "VertexTypes.h"
HyEngine::MeshAnimator::MeshAnimator(GameObject * owner, ID3DXMesh * mesh)
	:Animator(owner)
{
	assert(mesh);
	m_pMesh = mesh;
}

HyEngine::MeshAnimator::~MeshAnimator()
{
	m_pAniVB->Release();
	m_pAniIB->Release();

}

void HyEngine::MeshAnimator::Initialize()
{
	Animator::Initialize();
	assert(m_pMesh);
	m_face = m_pMesh->GetNumFaces();
	m_index = m_face * 3;
	m_vertices = m_pMesh->GetNumVertices();
	m_perVertex = m_pMesh->GetNumBytesPerVertex();
	m_fvf = m_pMesh->GetFVF();
	m_pMesh->GetVertexBuffer(&m_pVB);
	m_pMesh->GetIndexBuffer(&m_pIB);

	m_pVB->Lock(0, 0, (void**)&m_pVertices, 0);
	m_pVB->Unlock();
	m_pVB->Release();

	m_pIB->Lock(0, 0, (void**)&m_pIndices, 0);
	m_pIB->Unlock();
	m_pIB->Release();


	m_aniVertex = m_vertices;
	m_aniIndex = m_index;
	m_aniFace = m_face;

	DEVICE->CreateVertexBuffer(m_aniVertex * sizeof(ModelVertex), 0, m_fvf,
		D3DPOOL_DEFAULT, &m_pAniVB, NULL);

	m_pAniVB->Lock(0, 0, (void**)&m_pVerticesAni, 0);
	for (int i = 0; i < m_aniVertex; i++)
	{
		m_pVerticesAni->x = m_pVertices[i].x;
		m_pVerticesAni->y = m_pVertices[i].y;
		m_pVerticesAni->z = m_pVertices[i].z;

	}
	m_pAniVB->Unlock();

	m_pAniIB->Lock(0, 0, (void**)&m_pIndicesAni, 0);
	for (int i = 0; i < m_aniIndex; i++)
	{
		m_pIndicesAni[i] = m_pIndices[i];
	}

	m_pAniIB->Unlock();
}


void HyEngine::MeshAnimator::Update()
{
	Animator::Update();
}

void HyEngine::MeshAnimator::LateUpdate()
{
	Animator::LateUpdate();
}

void HyEngine::MeshAnimator::OnEnable()
{
	Animator::OnEnable();
}

void HyEngine::MeshAnimator::OnDisable()
{
	Animator::OnDisable();
}

void HyEngine::MeshAnimator::FrameMove()
{
	//// юс╫ц
	//m_scale += 0.005f;

	//if (m_scale >= 1.0f)
	//{
	//	m_scale = 0.0f;

	//	m_start++;
	//	m_next++;

	//	if (m_start > m_cnt - 1)
	//		m_start = 0;
	//	if (m_next > m_cnt - 1)
	//		m_next = 0;
	//}

	//m_pAniVB->Lock(0, 0, (void**)&m_pVerticesAni, 0);
	//for (int i = 0; i < m_aniVertex; i++)
	//{
	//	D3DXVECTOR3 v1;
	//	v1.x = m_pVertices[i].x;
	//	v1.y = m_pVertices[i].y;
	//	v1.z = m_pVertices[i].z;

	//	D3DXVECTOR3 v2;
	//	v2.x = 
	//}


}
