#include "StandardEngineFramework.h"
#include "Equipment.h"
#include "DynamicMesh.h"

HyEngine::Equipment::Equipment(Scene * scene, GameObject * pOwner, std::wstring name)
	: Mesh(ERenderType::RenderOpaque, scene, nullptr, name),
	m_pMesh( nullptr),
	m_pOwner(pOwner)
{
	//strcpy_s(m_boneName, 256, "");
}

HyEngine::Equipment::~Equipment()
{
}

void HyEngine::Equipment::Initialize(std::wstring xFilePath, std::wstring boneName)
{
	HRESULT hr = 0;

	ID3DXBuffer * adjBuffer = nullptr;
	ID3DXBuffer* mtrlBuffer = nullptr;
	DWORD numMtrls = 0;


	hr = D3DXLoadMeshFromX
	(
		(xFilePath).c_str(),
		D3DXMESH_MANAGED,
		DEVICE,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pMesh
	);
	assert(SUCCEEDED(hr));


	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		std::wstring dirPath = HyEngine::Path::GetDirectoryName(xFilePath);
		for (int i = 0; i < numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			// save the ith material
			m_mtrls.push_back(mtrls[i]);

			// check if the ith material has an associative texture
			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = nullptr;
				std::wstring fileName = CString::CharToWstring(mtrls[i].pTextureFilename);
				D3DXCreateTextureFromFile
				(
					DEVICE,
					(dirPath + fileName).c_str(),
					&tex
				);
				m_textureNames.push_back(fileName);
				// save the loaded texture
				m_textures.push_back(tex);

				/* Find NormalMap */
				std::wstring normalMapName = fileName;
				CString::Replace(&normalMapName, L"_D_", L"_N_");
				IDirect3DTexture9 * normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);
				m_normals.push_back(normalMap);

				/* Find EmissiveMap */
				std::wstring emissiveMapName = fileName;
				CString::Replace(&emissiveMapName, L"_D_", L"_E_");
				IDirect3DTexture9* emissiveMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + emissiveMapName);
				m_emissives.push_back(emissiveMap);

				/* Find SpecularMap */
				std::wstring specularMapName = fileName;
				CString::Replace(&specularMapName, L"_D_", L"_SP_");
				IDirect3DTexture9* specularMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + specularMapName);
				m_speculars.push_back(specularMap);
			}
			else
			{
				m_textureNames.push_back(L"");
				// no texture for the ith subset
				m_textures.push_back(0);
			}
		}
	}
	mtrlBuffer->Release();

	hr = m_pMesh->OptimizeInplace
	(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0
	);

	adjBuffer->Release();

	assert(SUCCEEDED(hr));


	D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
	DWORD vertexStride = m_pMesh->GetNumBytesPerVertex();
	if (SUCCEEDED(m_pMesh->GetDeclaration(meshDeclaration)))
	{
		DWORD numDeclarations = 0;
		for (int i = 0; (i < MAX_FVF_DECL_SIZE) && (meshDeclaration[i].Stream != 0xFF); i++)
		{
			numDeclarations++;
		}
		/* Tangent */
		meshDeclaration[numDeclarations].Stream = 0;
		meshDeclaration[numDeclarations].Offset = (WORD)vertexStride;
		meshDeclaration[numDeclarations].Type = D3DDECLTYPE_FLOAT3;
		meshDeclaration[numDeclarations].Method = D3DDECLMETHOD_DEFAULT;
		meshDeclaration[numDeclarations].Usage = D3DDECLUSAGE_TANGENT;
		meshDeclaration[numDeclarations].UsageIndex = 0;

		/* Binormal */
		meshDeclaration[numDeclarations + 1].Stream = 0;
		meshDeclaration[numDeclarations + 1].Offset = (WORD)(vertexStride + 3 * sizeof(float));
		meshDeclaration[numDeclarations + 1].Type = D3DDECLTYPE_FLOAT3;
		meshDeclaration[numDeclarations + 1].Method = D3DDECLMETHOD_DEFAULT;
		meshDeclaration[numDeclarations + 1].Usage = D3DDECLUSAGE_BINORMAL;
		meshDeclaration[numDeclarations + 1].UsageIndex = 0;

		/* Ending element */
		memset(&meshDeclaration[numDeclarations + 2], 0, sizeof(D3DVERTEXELEMENT9));
		meshDeclaration[numDeclarations + 2].Stream = 0xFF;
		meshDeclaration[numDeclarations + 2].Type = D3DDECLTYPE_UNUSED;

		ID3DXMesh* clonedMesh = nullptr;
		if (SUCCEEDED(m_pMesh->CloneMesh(m_pMesh->GetOptions(), meshDeclaration, DEVICE, &clonedMesh)))
		{
			m_pMesh->Release();
			m_pMesh = clonedMesh;
		}

	}
	m_pMesh->UpdateSemantics(meshDeclaration);


	/* Get adjacency */
	LPDWORD pAdjacency = new DWORD[m_pMesh->GetNumFaces() * 3];
	m_pMesh->GenerateAdjacency(0.0001f, pAdjacency);

	/* Compute tangent vector */
	D3DXComputeTangent(m_pMesh, 0, 0, 0, 1, pAdjacency);

	if (m_pParentBoneMatrix == nullptr)
	{
		DynamicMesh* mesh = dynamic_cast<DynamicMesh*>(m_pOwner);
		assert(mesh);
		const D3DXFRAME_DERIVED * pFrame = mesh->GetFrameByName(CString::ToString(boneName).c_str());
		if (pFrame == nullptr) return;

		m_pParentBoneMatrix = &pFrame->CombinedTransformMatrix;


	}
}

void HyEngine::Equipment::Update()
{
	GameObject::Update();
	DynamicMesh* mesh = dynamic_cast<DynamicMesh*>(m_pOwner);
	assert(mesh);


	m_pParentWorldMatrix = mesh->m_pTransform->GetWorldMatrix();

}

void HyEngine::Equipment::Render()
{
	GameObject::Render();

	/* Get Shader */
	if (m_pShader == nullptr)
	{
		if (IS_EDITOR)
			EDIT_ENGINE->TryGetShader(L"GBuffer", &m_pShader);
		else
			ENGINE->TryGetShader(L"GBuffer", &m_pShader);
	}
	assert(m_pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	for (int i = 0; i < m_mtrls.size(); i++)
	{
		/* Set world, view and projection */
		if (m_pParentBoneMatrix != nullptr)
		{
			D3DXMATRIX resultWorld = m_pTransform->GetWorldMatrix() * (*m_pParentBoneMatrix * m_pParentWorldMatrix);
			m_pShader->SetValue("WorldMatrix", &resultWorld, sizeof(resultWorld));
		}
		else
			m_pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
		m_pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
		m_pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

		/* Set world position */
		m_pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

		/* Set albedo */
		D3DXHANDLE albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");
		m_pShader->SetTexture(albedoHandle, m_textures[i]);

		/* Set NormalMap */
		D3DXHANDLE normalHandle = m_pShader->GetParameterByName(0, "NormalTex");
		m_pShader->SetTexture(normalHandle, m_normals[i]);

		/* Set Emissive */
		D3DXHANDLE emissiveHandle = m_pShader->GetParameterByName(0, "EmissiveTex");
		m_pShader->SetTexture(emissiveHandle, m_emissives[i]);

		/* Set Specular */
		D3DXHANDLE specularHandle = m_pShader->GetParameterByName(0, "SpecularTex");
		m_pShader->SetTexture(specularHandle, m_speculars[i]);

		bool hasNormalMap = false;
		if (m_normals[i] != nullptr)
			hasNormalMap = true;
		m_pShader->SetValue("HasNormalMap", &hasNormalMap, sizeof(hasNormalMap));

		m_pShader->SetTechnique("GBuffer");
		m_pShader->Begin(0, 0);
		{
			m_pShader->BeginPass(0);
			m_pMesh->DrawSubset(i);
			m_pShader->EndPass();
		}
		m_pShader->End();
	}
}

void HyEngine::Equipment::DrawPrimitive(ID3DXEffect* pShader)
{
	GameObject::DrawPrimitive(pShader);
	if (m_pParentBoneMatrix != nullptr)
	{
		D3DXMATRIX resultWorld = m_pTransform->GetWorldMatrix() * (*m_pParentBoneMatrix * m_pParentWorldMatrix);
		pShader->SetValue("WorldMatrix", &resultWorld, sizeof(resultWorld));
	}
	else
		pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));

	for (int i = 0; i < m_mtrls.size(); i++)
	{
		m_pMesh->DrawSubset(i);
	}
}

void HyEngine::Equipment::UpdatedData(EDataType dataType)
{

}

bool HyEngine::Equipment::ComputeBoundingSphere(D3DXVECTOR3 * center, float * radius)
{
	if (m_pMesh == nullptr)
	{
		*center = D3DXVECTOR3(0, 0, 0);
		*radius = 0;
		return false;
	}
	BYTE* ptr = nullptr;

	// get the face count
	DWORD numVertices = m_pMesh->GetNumVertices();

	// get the fvf flags
	DWORD fvfSize = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// lock the vertex buffer
	m_pMesh->LockVertexBuffer(0, (void**)&ptr);

	HRESULT hr;
	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)ptr,
		numVertices,
		fvfSize,
		center, radius);
	assert(SUCCEEDED(hr));

	m_pMesh->UnlockVertexBuffer();


	return true;
}



Equipment * HyEngine::Equipment::Create(Scene * scene, GameObject* owner, std::wstring xFilePath, std::wstring boneName, std::wstring name)
{
	Equipment * equip = new Equipment(scene, owner, name);
	equip->Initialize(xFilePath, boneName);
	return equip;
}
