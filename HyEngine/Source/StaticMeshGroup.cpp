#include "StandardEngineFramework.h"
#include "StaticMeshGroup.h"
#include "StaticMesh.h"


HyEngine::StaticMeshGroup::StaticMeshGroup(std::wstring meshFilePath)
	:m_meshFilePath(meshFilePath)
{

}

HyEngine::StaticMeshGroup::~StaticMeshGroup()
{

}

void HyEngine::StaticMeshGroup::InitializeBuffer()
{
	/* �켱 ������ؾ��Ѵ�. */
	assert(m_pMeshes.size() != 0);

	m_meshCount = m_pMeshes.size();

	// ������ ���� �޽������� �ϳ��� �־�ȴ�.
	m_pMeshes[0]->GetMesh()->GetVertexBuffer(&m_pOriginVertexBuffer);
	m_pMeshes[0]->GetMesh()->GetIndexBuffer(&m_pOriginIndexBuffer);

	D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
	m_pMeshes[0]->GetMesh()->GetDeclaration(meshDeclaration);
	DWORD vertexStride = m_pMeshes[0]->GetMesh()->GetNumBytesPerVertex();

	DWORD numDeclarations = 0;
	for (int i = 0; (i < MAX_FVF_DECL_SIZE) && (meshDeclaration[i].Stream != 0xFF); i++)
	{
		numDeclarations++;
	}
	/* ������� Instancing ���� */



	DEVICE->CreateVertexDeclaration(meshDeclaration, &m_pOriginVertexDeclaration);

}

void HyEngine::StaticMeshGroup::Insert(StaticMesh * mesh)
{
	/* ���� ������ ����� �����ϴ�. */
	assert(mesh->GetMeshPath() == m_meshFilePath);

	m_pMeshes.push_back(mesh);
}

void HyEngine::StaticMeshGroup::Insert(std::vector<StaticMesh*> meshes)
{
	// �̱���
	assert(false);
}

void HyEngine::StaticMeshGroup::RenderAll()
{
}
