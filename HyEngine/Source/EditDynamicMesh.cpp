#include "StandardEngineFramework.h"
#include "EditDynamicMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "MeshData.h"
#include "AnimNameData.h"
#include "ObjectContainer.h"
#include "EditScene.h"
#include "Light.h"
#include "PathManager.h"


HyEngine::EditDynamicMesh::EditDynamicMesh(Scene * scene, GameObject * parent, int editID)
	: EditObject(ERenderType::RenderOpaque, scene, parent, editID),
	m_pLoader(nullptr),
	m_pAniCtrl(nullptr)
{

}

HyEngine::EditDynamicMesh::EditDynamicMesh(const EditDynamicMesh & rhs)
	: EditObject(ERenderType::RenderOpaque, rhs.GetScene(), rhs.GetParent(), rhs.GetEditID()),
	m_pLoader(rhs.m_pLoader),
	m_pRootFrame(rhs.m_pRootFrame),
	m_MeshContainerList(rhs.m_MeshContainerList)
{
	m_pAniCtrl = new AnimationController(*rhs.m_pAniCtrl);
}

HyEngine::EditDynamicMesh::~EditDynamicMesh()
{
	SAFE_DELETE(m_pAniCtrl);

	m_pLoader->DestroyFrame(m_pRootFrame);
	SAFE_DELETE(m_pLoader);

	m_MeshContainerList.clear();
}

void HyEngine::EditDynamicMesh::Initialize()
{
	
}

void HyEngine::EditDynamicMesh::Update()
{
	EditObject::Update();
	//TEST
	if (m_pAniCtrl == nullptr)
		return;
	PlayAnimationSet(EDIT_TIMER->getDeltaTime());
}

void HyEngine::EditDynamicMesh::Render()
{
	EditObject::Render();

	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();

	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
			pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);

		void* pSrcVtx = nullptr;
		void* pDestVtx = nullptr;

		pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// 소프트웨어 스키닝을 수행하는 함수.
		// 스키닝 뿐 아니라 애니메이션 변경 시,
		// 뼈대들과 정점 정보들의 변경을 동시에 수행해주기도 한다.
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
			pMeshContainer->pRenderingMatrix, // 뼈의 최종 변환 상태
			NULL, // 원상태로 돌려놓기 위한 상태 행렬의 주소값(본래는 뼈대마다 싹 다 역행렬을 구해줘서 넣어야하지만 안넣어줘도 상관없음 
			pSrcVtx, // 변하지 않는 원본 메쉬의 정점 정보
			pDestVtx // 변환된 정보를 담기위한 정점 정보
		);



		/* Get Shader */
		ID3DXEffect* pShader = nullptr;
		EDIT_ENGINE->TryGetShader(L"GBuffer", &pShader);
		assert(pShader);

		/* Get Selected Cam */
		Camera* pSelectedCamera = nullptr;
		pSelectedCamera = GetScene()->GetSelectedCamera();
		assert(pSelectedCamera);


	
		// 실제 출력부분
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
			pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
			pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

			pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

			D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
			pShader->SetTexture(albedoHandle, pMeshContainer->ppTexture[i]);

			/* Find normal map */
			std::wstring normalMapName = pMeshContainer->pTextureNames[i];
			CString::Replace(&normalMapName, L"_D_", L"_N_");
			std::wstring dirPath = Path::GetDirectoryName(PATH->ResourcesPathW() + m_lastMeshPath);
			IDirect3DTexture9* normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);
			
			/* Find Emissive map */
			std::wstring emissiveMapName = pMeshContainer->pTextureNames[i];
			CString::Replace(&emissiveMapName, L"_D_", L"_E_");
			IDirect3DTexture9* emissiveMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + emissiveMapName);

			/* Find Specular map */
			std::wstring specularMapName = pMeshContainer->pTextureNames[i];
			CString::Replace(&specularMapName, L"_D_", L"_SP_");
			IDirect3DTexture9* specularMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + specularMapName);


			bool hasNormalMap = false;
			
			/* If normalmap exists, set texture. */
			if (normalMap != nullptr)
			{
				hasNormalMap = true;

				D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
				pShader->SetTexture(normalHandle, normalMap);
			}
			else
			{
				D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
				pShader->SetTexture(normalHandle, NULL);
			}

			/* If emissiveMap exists set texture */
			if (emissiveMap != nullptr)
			{
				D3DXHANDLE emissiveHandle = pShader->GetParameterByName(0, "EmissiveTex");
				pShader->SetTexture(emissiveHandle, emissiveMap);
			}
			else
			{
				D3DXHANDLE emissiveHandle = pShader->GetParameterByName(0, "EmissiveTex");
				pShader->SetTexture(emissiveHandle, NULL);
			}

			/* If specularMap exists, set texture */
			if (specularMap != nullptr)
			{
				D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
				pShader->SetTexture(specularHandle, specularMap);
			}
			else
			{
				D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
				pShader->SetTexture(specularHandle, NULL);
			}

			pShader->SetBool("HasNormalMap", hasNormalMap);
			pShader->SetBool("HasEmissiveMap", false);
			pShader->SetTechnique("GBuffer");
			pShader->Begin(0, 0);
			{
				pShader->BeginPass(0);
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
				pShader->EndPass();
			}
			pShader->End();
		}

		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::EditDynamicMesh::DrawPrimitive()
{
	EditObject::DrawPrimitive();

	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();

	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
			pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);

		void* pSrcVtx = nullptr;
		void* pDestVtx = nullptr;

		pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// 소프트웨어 스키닝을 수행하는 함수.
		// 스키닝 뿐 아니라 애니메이션 변경 시,
		// 뼈대들과 정점 정보들의 변경을 동시에 수행해주기도 한다.
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
			pMeshContainer->pRenderingMatrix, // 뼈의 최종 변환 상태
			NULL, // 원상태로 돌려놓기 위한 상태 행렬의 주소값(본래는 뼈대마다 싹 다 역행렬을 구해줘서 넣어야하지만 안넣어줘도 상관없음 
			pSrcVtx, // 변하지 않는 원본 메쉬의 정점 정보
			pDestVtx // 변환된 정보를 담기위한 정점 정보
		);

		// 실제 출력부분
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::EditDynamicMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	// mesh 정보가 변경되었을 때 
	// 여기서 초기화해준다.
	assert(m_pMeshData);
	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	if (meshPath == m_lastMeshPath) return;
	m_lastMeshPath = meshPath;
	std::wstring dirPath = Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
	std::wstring fileName = Path::GetFileName(PATH->ResourcesPathW() + meshPath);

	if (std::wcscmp(meshPathExt.c_str(), L"x") != 0 && std::wcscmp(meshPathExt.c_str(), L"X") != 0)
		return;

	InitializeMeshes(dirPath, fileName);
	SetAnimationSet(0);
}

void HyEngine::EditDynamicMesh::InitializeMeshes(std::wstring filePath, std::wstring fileName)
{
	TCHAR fullPath[MAX_PATH] = L"";

	lstrcpy(fullPath, filePath.c_str());
	lstrcat(fullPath, fileName.c_str());

	m_pLoader = new MeshHierarchy(filePath);
	assert(m_pLoader);

	LPD3DXANIMATIONCONTROLLER pAniCtrl = nullptr;

	HRESULT hr;
	hr = D3DXLoadMeshHierarchyFromX(fullPath,
		D3DXMESH_MANAGED,
		DEVICE,
		m_pLoader,
		NULL,
		&m_pRootFrame,
		&pAniCtrl
	);
	assert(SUCCEEDED(hr));



	m_pAniCtrl = new AnimationController(pAniCtrl);
	assert(m_pAniCtrl);

	SAFE_RELEASE(pAniCtrl);



	D3DXMATRIX matTemp;
	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
	SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);

	
}

const D3DXFRAME_DERIVED * HyEngine::EditDynamicMesh::GetFrameByName(const char * frameName)
{
	// 해당 뼈의 이름을 통해 뼈의 정보 구조체를 반환한다.
	return (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, frameName);
}

bool HyEngine::EditDynamicMesh::IsAnimationSetEnd(double endTime)
{
	return m_pAniCtrl->IsAnimationSetEnd(endTime);
}

bool HyEngine::EditDynamicMesh::IsAnimationAfterTrack(double afterTime)
{
	return m_pAniCtrl->IsAnimationAfterTrack(afterTime);
}

const unsigned int & HyEngine::EditDynamicMesh::GetAnimationNum()
{
	return m_pAniCtrl->GetAnimationNum();
}

double HyEngine::EditDynamicMesh::GetCurAnimationPosition()
{
	return m_pAniCtrl->GetCurAnimationPosition();
}

const list<D3DXMESHCONTAINER_DERIVED*>& HyEngine::EditDynamicMesh::GetMeshContainerList()
{
	return m_MeshContainerList;
}

void HyEngine::EditDynamicMesh::SetAnimationSet(const unsigned int & index)
{
	m_pAniCtrl->SetAnimationSet(index);
}

void HyEngine::EditDynamicMesh::PlayAnimationSet(const float & timeDelta)
{
	if (m_pAniCtrl == nullptr)
		return;

	m_pAniCtrl->PlayAnimationSet(timeDelta);

	D3DXMATRIX matTemp;

	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
}

int HyEngine::EditDynamicMesh::GetAnimationCount()
{
	if (m_pAniCtrl == nullptr)
		return 0;
	return m_pAniCtrl->GetAnimationNum();
}

void HyEngine::EditDynamicMesh::GetAnimationName(_Out_ AnimNameData* outString, int index)
{
	if (index >= GetAnimationCount())return;
	LPD3DXANIMATIONSET pAs = NULL;
	m_pAniCtrl->GetAnimationSet()->GetAnimationSet(index, &pAs);
	
	LPCSTR a = pAs->GetName();
	std::wstring name = CString::CharToWstring(pAs->GetName());
	std::string convertedName = CString::ToString(name);
	strcpy_s(outString->name, 256, pAs->GetName());


}



void HyEngine::EditDynamicMesh::UpdateFrameMatrix(D3DXFRAME_DERIVED * frame, const D3DXMATRIX * parentMatrix)
{
	// 부모가 없는 경우 종료한다.
	if (frame == nullptr) return;

	frame->CombinedTransformMatrix = frame->TransformationMatrix * (*parentMatrix);

	if (frame->pFrameSibling != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameSibling, parentMatrix);

	if (frame->pFrameFirstChild != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameFirstChild, &frame->CombinedTransformMatrix);
}

void HyEngine::EditDynamicMesh::SetupFrameMatrixPointer(D3DXFRAME_DERIVED * frame)
{
	if (frame->pMeshContainer != nullptr)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)frame->pMeshContainer;

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		{
			// 뼈의 이름을 가져온다.
			const char* boneName = pMeshContainer->pSkinInfo->GetBoneName(i);
				
			// D3DXFrameFind를 통해 뼈대 이름으로 뼈대를 가져올 수 있다.
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
