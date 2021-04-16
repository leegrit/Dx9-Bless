#include "StandardEngineFramework.h"
#include "DynamicMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "MeshData.h"
#include "AnimNameData.h"
#include "Deserializer.h"
#include "PathManager.h"
#include "HierarchyData.h"
#include "MeshHierarchyLoader.h"

HyEngine::DynamicMesh::DynamicMesh(Scene * scene, GameObject * parent,std::wstring name)
	: Mesh(ERenderType::RenderOpaque, scene, parent, name),
	m_pLoader(nullptr),
	m_pAniCtrl(nullptr)
{

}

HyEngine::DynamicMesh::DynamicMesh(Scene * scene, GameObject * parent, int editID)
	: Mesh(ERenderType::RenderOpaque, scene, parent, L"DynamicMesh"),
	m_pLoader(nullptr),
	m_pAniCtrl(nullptr)
{
	SetEditID(editID);
	EventDispatcher::AddEventListener(RenderEvent::RenderBegin, to_string(GetInstanceID()), std::bind(&DynamicMesh::OnRenderBegin, this, placeholders::_1));
	EventDispatcher::AddEventListener(RenderEvent::RenderEnd, to_string(GetInstanceID()), std::bind(&DynamicMesh::OnRenderEnd, this, placeholders::_1));

}

HyEngine::DynamicMesh::~DynamicMesh()
{
	EventDispatcher::RemoveEventListener(RenderEvent::RenderBegin, to_string(GetInstanceID()));
	EventDispatcher::RemoveEventListener(RenderEvent::RenderEnd, to_string(GetInstanceID()));
	m_MeshContainerList.clear();
}

void HyEngine::DynamicMesh::Initialize(std::wstring dataPath)
{

	EventDispatcher::AddEventListener(RenderEvent::RenderBegin, to_string(GetInstanceID()), std::bind(&DynamicMesh::OnRenderBegin,this, placeholders::_1));
	EventDispatcher::AddEventListener(RenderEvent::RenderEnd, to_string(GetInstanceID()), std::bind( &DynamicMesh::OnRenderEnd,this, placeholders::_1));

	std::shared_ptr<HierarchyData> data = Deserializer::Deserialize(dataPath);
	InsertGameData(data->gameObjectData);
	InsertMeshData(data->meshData);
}

void HyEngine::DynamicMesh::Initialize()
{
}

void HyEngine::DynamicMesh::Update()
{
	GameObject::Update();
	if (m_pAniCtrl == nullptr)
		return;
	if (IS_EDITOR)
	{
		PlayAnimationSet(EDIT_TIMER->getDeltaTime());
	}
	else
	{
		PlayAnimationSet(TIMER->getDeltaTime());

	}
}

void HyEngine::DynamicMesh::Render()
{
	GameObject::Render();

	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();

	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		//for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		//	pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);

		//void* pSrcVtx = nullptr;
		//void* pDestVtx = nullptr;

		//pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		//pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// ����Ʈ���� ��Ű���� �����ϴ� �Լ�.
		// ��Ű�� �� �ƴ϶� �ִϸ��̼� ���� ��,
		// ������ ���� �������� ������ ���ÿ� �������ֱ⵵ �Ѵ�.
		//pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
		//	pMeshContainer->pRenderingMatrix, // ���� ���� ��ȯ ����
		//	NULL, // �����·� �������� ���� ���� ����� �ּҰ�(������ ���븶�� �� �� ������� �����༭ �־�������� �ȳ־��൵ ������� 
		//	pSrcVtx, // ������ �ʴ� ���� �޽��� ���� ����
		//	pDestVtx // ��ȯ�� ������ ������� ���� ����
		//);

		/* Get Shader */
		if (m_pShader == nullptr)
		{
			if (ENGINE)
				ENGINE->TryGetShader(L"GBuffer", &m_pShader);
			else
				EDIT_ENGINE->TryGetShader(L"GBuffer", &m_pShader);
		}
		assert(m_pShader);

		/* Get Selected Cam */
		Camera* pSelectedCamera = nullptr;
		pSelectedCamera = GetScene()->GetSelectedCamera();
		assert(pSelectedCamera);

		// ���� ��ºκ�
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			m_pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
			m_pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
			m_pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

			m_pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

			D3DXHANDLE albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");
			m_pShader->SetTexture(albedoHandle, pMeshContainer->ppTexture[i]);

			D3DXHANDLE normalHandle = m_pShader->GetParameterByName(0, "NormalTex");
			m_pShader->SetTexture(normalHandle, pMeshContainer->ppNormal[i]);

			D3DXHANDLE emissiveHandle = m_pShader->GetParameterByName(0, "EmissiveTex");
			m_pShader->SetTexture(emissiveHandle, NULL);

			D3DXHANDLE specularHandle = m_pShader->GetParameterByName(0, "SpecularTex");
			m_pShader->SetTexture(specularHandle, NULL);

			D3DXHANDLE specularMaskHandle = m_pShader->GetParameterByName(0, "SpecularMaskTex");
			m_pShader->SetTexture(specularMaskHandle, pMeshContainer->ppSpecularMask[i]);

			bool hasNormalMap = false;
			if (pMeshContainer->ppNormal[i] != nullptr)
			{
				hasNormalMap = true;
			}

			m_pShader->SetBool("HasNormalMap", hasNormalMap);
			m_pShader->SetBool("HasEmissiveMap", false);
			m_pShader->SetTechnique("GBuffer");
			m_pShader->Begin(0, 0);
			{
				m_pShader->BeginPass(0);
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
				m_pShader->EndPass();
			}
			m_pShader->End();
		}

		//pMeshContainer->pOriMesh->UnlockVertexBuffer();
	//	pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::DynamicMesh::DrawPrimitive(ID3DXEffect* pShader)
{
	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();

	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		// ���� ��ºκ�
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

	}
}

void HyEngine::DynamicMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	// mesh ������ ����Ǿ��� �� 
	// ���⼭ �ʱ�ȭ���ش�.
	assert(m_pMeshData);
	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	if (m_lastMeshPath == meshPath) return;
	m_lastMeshPath = meshPath;
	std::wstring dirPath = Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
	std::wstring fileName = Path::GetFileName(PATH->ResourcesPathW() + meshPath);

	if (std::wcscmp(meshPathExt.c_str(), L"x") != 0 && std::wcscmp(meshPathExt.c_str(), L"X") != 0)
		return;

	InitializeMeshes(dirPath, fileName);
	if (IS_EDITOR)
	{
		InitializeAnimationNames();
	}
	SetAnimationSet(0);
}

bool HyEngine::DynamicMesh::ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius)
{
	for (auto& meshContainer : m_MeshContainerList)
	{
		if (meshContainer->pOriMesh == nullptr)
			continue;

		BYTE * ptr = nullptr;

		/* Get the face count */
		DWORD numVertices = meshContainer->pOriMesh->GetNumVertices();

		/* Get the fvf Size */
		DWORD fvfSize = D3DXGetFVFVertexSize(meshContainer->pOriMesh->GetFVF());

		/* Lock the vertex buffer */
		meshContainer->pOriMesh->LockVertexBuffer(0, (void**)&ptr);

		HRESULT hr;
		hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)ptr,
			numVertices,
			fvfSize,
			center, radius);
		assert(SUCCEEDED(hr));

		meshContainer->pOriMesh->UnlockVertexBuffer();
// 
// 		float scaleFactor = std::max(m_pTransform->m_scale.x(), m_pTransform->m_scale.y());
// 		scaleFactor = std::max(scaleFactor, m_pTransform->m_scale.z());
// 		// scale���� �޵����Ѵ�.
// 		*radius *= scaleFactor;

		return true;
	}

	/* Fail */
	*center = D3DXVECTOR3(0, 0, 0);
	*radius = 0;
	return false;
}

void HyEngine::DynamicMesh::InitializeMeshes(std::wstring filePath, std::wstring fileName)
{
	TCHAR fullPath[MAX_PATH] = L"";

	lstrcpy(fullPath, filePath.c_str());
	lstrcat(fullPath, fileName.c_str());

	std::wstring temp = fullPath;

	bool isSucceeded = MeshHierarchyLoader::TryGetMeshHierarchy(temp, &m_pAniCtrl, &m_pRootFrame);
	assert(isSucceeded == true);

	D3DXMATRIX matTemp;
	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));

	SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);
}

const D3DXFRAME_DERIVED * HyEngine::DynamicMesh::GetFrameByName(const char * frameName)
{
	// �ش� ���� �̸��� ���� ���� ���� ����ü�� ��ȯ�Ѵ�.
	return (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, frameName);
}

bool HyEngine::DynamicMesh::IsAnimationSetEnd(double endTime)
{
	return m_pAniCtrl->IsAnimationSetEnd(endTime);
}

bool HyEngine::DynamicMesh::IsAnimationAfterTrack(double afterTime)
{
	return m_pAniCtrl->IsAnimationAfterTrack(afterTime);
}

const unsigned int & HyEngine::DynamicMesh::GetAnimationNum()
{
	return m_pAniCtrl->GetAnimationNum();
}

double HyEngine::DynamicMesh::GetCurAnimationPosition()
{
	return m_pAniCtrl->GetCurAnimationPosition();
}

const list<D3DXMESHCONTAINER_DERIVED*>& HyEngine::DynamicMesh::GetMeshContainerList()
{
	return m_MeshContainerList;
}

void HyEngine::DynamicMesh::SetAnimationSet(const unsigned int & index)
{
	m_pAniCtrl->SetAnimationSet(index);
}

void HyEngine::DynamicMesh::PlayAnimationSet(const float & timeDelta)
{
	if (m_pAniCtrl == nullptr)
		return;

// 	m_pAniCtrl->PlayAnimationSet(timeDelta);
// 
// 	D3DXMATRIX matTemp;
// 
// 	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
}

void HyEngine::DynamicMesh::OnRenderBegin(void*)
{
	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();
	
	if (IS_EDITOR)
		m_pAniCtrl->PlayAnimationSet(EDIT_TIMER->getDeltaTime());
	else
		m_pAniCtrl->PlayAnimationSet(TIMER->getDeltaTime());

	D3DXMATRIX matTemp;

	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
			pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);

		void* pSrcVtx = nullptr;
		void* pDestVtx = nullptr;

		pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// ����Ʈ���� ��Ű���� �����ϴ� �Լ�.
		// ��Ű�� �� �ƴ϶� �ִϸ��̼� ���� ��,
		// ������ ���� �������� ������ ���ÿ� �������ֱ⵵ �Ѵ�.
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
			pMeshContainer->pRenderingMatrix, // ���� ���� ��ȯ ����
			NULL, // �����·� �������� ���� ���� ����� �ּҰ�(������ ���븶�� �� �� ������� �����༭ �־�������� �ȳ־��൵ ������� 
			pSrcVtx, // ������ �ʴ� ���� �޽��� ���� ����
			pDestVtx // ��ȯ�� ������ ������� ���� ����
		);


		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::DynamicMesh::OnRenderEnd(void*)
{
}

void HyEngine::DynamicMesh::InitializeAnimationNames()
{
	int count = GetAnimationCount();
	if (count <= 0) return;

	for (int index = 0; index < count; index++)
	{
		LPD3DXANIMATIONSET pAs = nullptr;
		m_pAniCtrl->GetAnimationSet()->GetAnimationSet(index, &pAs);

		m_animationNames.emplace_back(CString::CharToString(pAs->GetName()));
	}
}

int HyEngine::DynamicMesh::GetAnimationCount()
{
	if (m_pAniCtrl == nullptr)
		return 0;
	return m_pAniCtrl->GetAnimationNum();
}

void HyEngine::DynamicMesh::GetAnimationName(AnimNameData * outString, int index)
{
	if (index >= m_animationNames.size()) return;

	strcpy_s(outString->name, 256, m_animationNames[index].c_str());
}

void HyEngine::DynamicMesh::UpdateFrameMatrix(D3DXFRAME_DERIVED * frame, const D3DXMATRIX * parentMatrix)
{
	// �θ� ���� ��� �����Ѵ�.
	if (frame == nullptr) return;

	frame->CombinedTransformMatrix = frame->TransformationMatrix * (*parentMatrix);

	if (frame->pFrameSibling != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameSibling, parentMatrix);

	if (frame->pFrameFirstChild != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameFirstChild, &frame->CombinedTransformMatrix);
}

void HyEngine::DynamicMesh::SetupFrameMatrixPointer(D3DXFRAME_DERIVED * frame)
{
	if (frame->pMeshContainer != nullptr)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)frame->pMeshContainer;

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		{
			// ���� �̸��� �����´�.
			const char* boneName = pMeshContainer->pSkinInfo->GetBoneName(i);

			// D3DXFrameFind�� ���� ���� �̸����� ���븦 ������ �� �ִ�.
			D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, boneName);

			pMeshContainer->ppFrameCombinedMatrix[i] = &pFrame->CombinedTransformMatrix;
		}

		m_MeshContainerList.emplace_back(pMeshContainer);
	}

	if (frame->pFrameSibling != nullptr)
		SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)frame->pFrameSibling);

	if (frame->pFrameFirstChild != nullptr)
		SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)frame->pFrameFirstChild);
}

void HyEngine::DynamicMesh::UpdateBoneMatrix(D3DXFRAME_DERIVED * frame)
{
	if (frame->pMeshContainer != nullptr)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)frame->pMeshContainer;
		for (UINT i = 0; i < pMeshContainer->numBones; i++)
			pMeshContainer->pFrameOffsetMatrix[i] = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);
	}

	if (frame->pFrameSibling != nullptr)
		UpdateBoneMatrix((D3DXFRAME_DERIVED*)frame->pFrameSibling);
	
	if (frame->pFrameFirstChild != nullptr)
		UpdateBoneMatrix((D3DXFRAME_DERIVED*)frame->pFrameFirstChild);

}
