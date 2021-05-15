#include "StandardEngineFramework.h"
#include "EditEngine.h"
#include "EditScene.h"
#include "EditObject.h"
#include "Renderer.h"
#include "EditData.h"
#include "GameObjectData.h"
#include "MeshData.h"
#include "NavMesh.h"
#include "CellData.h"
#include "EditMesh.h"
#include "EditDynamicMesh.h"
#include "AnimNameData.h"
#include "PathManager.h"
#include "TerrainData.h"
#include "Terrain.h"
#include "ObjectContainer.h"
#include "LightObject.h"
#include "LightData.h"
#include "EffectData.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "UIData.h"

using namespace HyEngine;

const static TCHAR szAppName[] = TEXT("D3DImageSample");


IMPLEMENT_SINGLETON(EditEngine)

EditEngine::EditEngine()
	:m_hWnd(NULL),
	m_pEditScene(nullptr),
	m_width(1024),
	m_height(1024),
	m_bLoading(false),
	m_pTimer(nullptr)
{
	InitLoggingService();
	DirectXDevice::Create();
	UIDGen::Create();
	PathManager::Create();

	//m_pRenderer = new Renderer();
	m_pTimer = new Timer();
	m_pMouse = new IO::Mouse();
	m_pKeyboard = new IO::Keyboard();

	Initialize();
	Load();
}
void EditEngine::DestroyResources()
{
	DirectXDevice::Destroy();
	UIDGen::Destroy();
	PathManager::Destroy();
	Renderer::Release(m_pRenderer);
	SAFE_DELETE(m_pTimer);

}
EditEngine::~EditEngine()
{
	DestroyResources();
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		UnregisterClass(szAppName, NULL);
	}
}





inline Renderer * HyEngine::EditEngine::GetRenderer() const
{
	return m_pRenderer;
}

bool EditEngine::Initialize()
{
	HRESULT hr = EnsureHWND();
	assert(SUCCEEDED(hr));
	DirectXDevice::Get()->Init(m_hWnd);
	m_pRenderer = Renderer::Create();
	m_pTimer->start();
	return true;
}

bool EditEngine::Load()
{
	m_bLoading = true;
	m_pEditScene = new EditScene();
	m_pEditScene->LoadScene();

	LoadShaders();


	m_bLoading = false;
	return true;
}

void EditEngine::Render()
{
	/* Occlusion Query */
	/*
	m_pRenderer->OcclusionBegin();
	m_pRenderer->OcclusionCull(m_pEditScene);
	m_pRenderer->OcclusionEnd();
	*/
	m_pRenderer->RenderBegin();
	m_pEditScene->RenderScene(m_pRenderer);
	RenderFont();
	m_pRenderer->RenderEnd();
}

void EditEngine::Update()
{
	m_fontInfos.clear();
	EDIT_TIMER->tick();
	m_pEditScene->UpdateScene();
	m_pEditScene->ViewFrustumCull();
	//if (m_bGameMode)
	//{
	//	m_pEditScene->UpdateScene();
	//}
	//else // editMode
	//{
	//	assert(m_pEditScene);
	//	EditScene* editScene = dynamic_cast<EditScene*>(m_pEditScene);
	//	assert(editScene);
	//	m_pEditScene->CheckWantDestroy();
	//	editScene->GetSelectedCamera()->CameraUpdate();
	//}
}

void HyEngine::EditEngine::InitLoggingService()
{
	// create file Logger
	std::shared_ptr<Logger<FileLogPolicy >> engineLogger =
		std::make_shared<Logger<FileLogPolicy >>(L"editor.log");

	// set name of current thread
	engineLogger->setThreadName("mainThread");

	// register the logging service
	ServiceLocator::provideFileLoggingService(engineLogger);


#ifdef _DEBUG
	// print starting message
	ServiceLocator::getFileLogger()->print<SeverityType::info>("The file logger was created successfully.");
#endif
}

void HyEngine::EditEngine::LoadShaders()
{
	InsertShader(L"GBuffer", PATH->ShadersPathW() + L"GBuffer.fx");
	InsertShader(L"PointLight", PATH->ShadersPathW() + L"PointLight.fx");
	InsertShader(L"SpotLight", PATH->ShadersPathW() + L"SpotLight.fx");
	InsertShader(L"Ambient", PATH->ShadersPathW() + L"Ambient.fx");
	InsertShader(L"DirectionalLight", PATH->ShadersPathW() + L"DirectionalLight.fx");
	InsertShader(L"DiffuseShader", PATH->ShadersPathW() + L"DiffuseShader.fx");
	InsertShader(L"MeshEffect", PATH->ShadersPathW() + L"MeshEffect.fx");
	InsertShader(L"TextureEffect", PATH->ShadersPathW() + L"TextureEffect.fx");
	InsertShader(L"ShadowMap", PATH->ShadersPathW() + L"ShadowMap.fx");
	InsertShader(L"SoftShadowMapping", PATH->ShadersPathW() + L"SoftShadowMapping.fx");
	InsertShader(L"Blur", PATH->ShadersPathW() + L"Blur.fx");
	InsertShader(L"Collider", PATH->ShadersPathW() + L"Collider.fx");
	InsertShader(L"Skybox", PATH->ShadersPathW() + L"Skybox.fx");
	InsertShader(L"UIPanel", PATH->ShadersPathW() + L"UIPanel.fx");
	InsertShader(L"SkinnedMesh", PATH->ShadersPathW() + L"SkinnedMesh.fx");
	InsertShader(L"StaticMesh", PATH->ShadersPathW() + L"StaticMesh.fx");
	InsertShader(L"OcclusionQuery", PATH->ShadersPathW() + L"OcclusionQuery.fx");
	InsertShader(L"LinearFilter", PATH->ShadersPathW() + L"LinearFilter.fx");
	InsertShader(L"Terrain", PATH->ShadersPathW() + L"Terrain.fx");
	InsertShader(L"DeferredBlend", PATH->ShadersPathW() + L"DeferredBlend.fx");
	InsertShader(L"ShieldEffect", PATH->ShadersPathW() + L"ShieldEffect.fx");
	InsertShader(L"PRBuffer", PATH->ShadersPathW() + L"PRBuffer.fx");
	InsertShader(L"RimLight", PATH->ShadersPathW() + L"RimLight.fx");
	InsertShader(L"Brightness", PATH->ShadersPathW() + L"Brightness.fx");
	InsertShader(L"Bloom", PATH->ShadersPathW() + L"Bloom.fx");
	InsertShader(L"PostRender", PATH->ShadersPathW() + L"PostRender.fx");
	InsertShader(L"DebugMRT", PATH->ShadersPathW() + L"DebugMRT.fx");
}

bool HyEngine::EditEngine::InsertShader(std::wstring key, std::wstring path)
{
	auto& iter = m_shaderMap.find(key);

	/* already exist */
	if (iter != m_shaderMap.end())
		return false;

	ID3DXEffect* shader = nullptr;
	D3DXCreateEffectFromFile(DEVICE, path.c_str(), nullptr, nullptr, 0, nullptr, &shader, nullptr);
	assert(shader);

	m_shaderMap.insert(make_pair(key, shader));
}

bool HyEngine::EditEngine::TryGetShader(std::wstring key, _Out_ ID3DXEffect ** ppShader)
{
	*ppShader = nullptr;

	auto& iter = m_shaderMap.find(key);

	if (iter == m_shaderMap.end())
		return false;

	*ppShader = iter->second;
	return true;
}

void HyEngine::EditEngine::RenderFont()
{
	DIRECT_SPRITE->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	/*DWORD old;
	DEVICE->GetRenderState(D3DRS_ZENABLE, &old);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);*/
	for (auto& fontInfo : m_fontInfos)
	{
		DIRECT_SPRITE->SetTransform(&fontInfo.matTrans);
		DIRECT_FONT->DrawTextW(DIRECT_SPRITE, fontInfo.textBuff, lstrlen(fontInfo.textBuff), nullptr,fontInfo.format, fontInfo.textColor);
	}
	//DEVICE->SetRenderState(D3DRS_ZENABLE, old);

	DIRECT_SPRITE->End();
}

void HyEngine::EditEngine::DrawText(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, DWORD format)
{
	EditFontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;
	info.format = format;

	m_fontInfos.push_back(info);
}

void HyEngine::EditEngine::DrawText(const TCHAR * text, D3DXMATRIX mat, D3DCOLOR color)
{
	EditFontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	info.matTrans = mat;
	info.textColor = color;
	info.format = DT_LEFT;

	m_fontInfos.push_back(info);
}

void HyEngine::EditEngine::DrawTextFormat(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, const TCHAR * text, int args, ...)
{
	EditFontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text, args);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;
	info.format = DT_LEFT;

	m_fontInfos.push_back(info);
}

void HyEngine::EditEngine::DrawTextInWorld(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXCOLOR color)
{
	D3DXVECTOR3 resultPos;
	D3DXMATRIX resultMat;
	D3DXMATRIX worldMat;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	D3DXMATRIX viewMat = SCENE->GetSelectedCamera()->GetViewMatrix();
	D3DXMATRIX projMat = SCENE->GetSelectedCamera()->GetProjectionMatrix();


	//position.x -= m_size.x * 0.5f;
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, 1);
	worldMat = scaleMat * posMat;
	D3DVIEWPORT9 viewPort;
	DEVICE->GetViewport(&viewPort);

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	D3DXVec3Project(&resultPos, &D3DXVECTOR3(0, 0, 0), &viewPort, &projMat, &viewMat, &worldMat);


	ENGINE->DrawText(text, resultPos, D3DXVECTOR3(1, 1, 1), color);
}


void EditEngine::GetBackBuffer(IDirect3DSurface9 ** ppSurface)
{
	*ppSurface = nullptr;

	DEVICE->GetRenderTarget(0, ppSurface);

	assert(ppSurface);
}

Scene * EditEngine::GetScene()
{
	assert(m_pEditScene);
	return m_pEditScene;
}

void EditEngine::SelectObject(int index)
{
	EditScene* scene = static_cast<EditScene*>(m_pEditScene);
	GameObject* selectedObj =  scene->GetGameObject(index);
	m_pSelectedObject = selectedObj;
}

void HyEngine::EditEngine::InsertGameData(GameObjectData* data)
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->InsertGameData(data);
}

void HyEngine::EditEngine::InsertMeshData(MeshData * data)
{
	if (m_pSelectedObject == nullptr)
		return;

	m_pSelectedObject->InsertMeshData(data);
}

void HyEngine::EditEngine::InsertCellData(CellData * data, int cellEditMode)
{
	if (m_pSelectedObject == nullptr)
		return;
	NavMesh* navMesh = dynamic_cast<NavMesh*>(m_pSelectedObject);
	navMesh->SetCellEditMode((ECellEditMode)cellEditMode);
	navMesh->InsertCellData(data);
}

void HyEngine::EditEngine::ActiveObject()
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->SetActive(true);
}

void HyEngine::EditEngine::InactiveObject()
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->SetActive(false);
}

void HyEngine::EditEngine::AddGameObject(int index)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddMeshObject(index);
}

void HyEngine::EditEngine::AddPawn(int index)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddPawn(index);
}

void HyEngine::EditEngine::AddNavMesh(int index)
{
	Scene* scene = EDIT_SCENE;
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddNavMesh(index);
}

void HyEngine::EditEngine::RemoveGameObject(int index)
{
	Scene* scene = EDIT_SCENE;
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	for (auto& obj : editScene->GetObjectContainer()->GetGameObjectAll())
	{
		//EditObject* editObj = dynamic_cast<EditObject*>(obj);
		if (obj->GetEditID() == index)
		{
			Object::Destroy(obj);
			return;
		}
	}
}

bool HyEngine::EditEngine::PickGameObject(float xMousePos, float yMousePos, _Out_ int * resultIndex, _Out_ VectorData* pickedPos)
{
	std::vector<GameObject*>& meshObjs = GetScene()->GetObjectContainer()->GetOpaqueObjectAll();
	/* For Terrain */
	std::vector<GameObject*>& textureObjs = GetScene()->GetObjectContainer()->GetAlphaObjectAll();
	
	/* Merge */
	std::vector<GameObject*> sortedVec;
	sortedVec.insert(sortedVec.end(), meshObjs.begin(), meshObjs.end());
	sortedVec.insert(sortedVec.end(), textureObjs.begin(), textureObjs.end());


	std::sort(sortedVec.begin(), sortedVec.end(), [&](GameObject* left, GameObject* right) ->bool
	{
		D3DXVECTOR3 camPos = m_pEditScene->GetEditCamera()->m_pTransform->m_position;
		D3DXVECTOR3 leftPos = left->m_pTransform->m_position;
		D3DXVECTOR3 rightPos = right->m_pTransform->m_position;
		float leftDist = D3DXVec3Length(&(camPos - leftPos));
		float rightDist = D3DXVec3Length(&(camPos - rightPos));


		if (leftDist < rightDist)
			return true;
		else
			return false;
	});
	for (auto& obj : sortedVec)
	{
		StaticMesh* editObj = dynamic_cast<StaticMesh*>(obj);
		if (editObj != nullptr)
		{

			// picking은 xfile만 가능
			ID3DXMesh* mesh = editObj->GetMesh();
			if (mesh == nullptr) continue;

			D3DXVECTOR3 origin;
			D3DXVECTOR3 direction;
			m_pEditScene->GetEditCamera()->UnProjection(&origin, &direction, D3DXVECTOR3(xMousePos, yMousePos, 0));

			D3DXMATRIX worldInverse;
			D3DXVECTOR3 worldOrigin = origin;
			D3DXVECTOR3 worldDirection = direction;
			D3DXMatrixInverse(&worldInverse, nullptr, &editObj->m_pTransform->GetWorldMatrix());
			D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
			D3DXVec3TransformNormal(&direction, &direction, &worldInverse);

			BOOL isHit = false;
			DWORD faceIndex;
			FLOAT u;
			FLOAT v;
			FLOAT dist;
			LPD3DXBUFFER allHits;
			DWORD countOfHits;
			D3DXVECTOR3 resultPos;
			D3DXIntersect(mesh, &origin, &direction, &isHit, &faceIndex, &u, &v, &dist, &allHits, &countOfHits);

			if (isHit)
			{
				*resultIndex = editObj->GetEditID();

				D3DXVECTOR3 resultPos = worldOrigin + worldDirection * dist;
				pickedPos->x = resultPos.x;
				pickedPos->y = resultPos.y;
				pickedPos->z = resultPos.z;
				return true;
			}
		}
	
		Terrain* terrain = dynamic_cast<Terrain*>(obj);
		if (terrain != nullptr)
		{
			D3DXVECTOR3 origin;
			D3DXVECTOR3 direction;
			m_pEditScene->GetEditCamera()->UnProjection(&origin, &direction, D3DXVECTOR3(xMousePos, yMousePos, 0));

			D3DXMATRIX worldInverse;
			D3DXMatrixInverse(&worldInverse, nullptr, &terrain->m_pTransform->GetWorldMatrix());
			D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
			D3DXVec3TransformNormal(&direction, &direction, &worldInverse);
			
			D3DXVECTOR3 resultPos;
			bool isHit = false;
			isHit = terrain->TryPickOnTerrain(origin, direction, &resultPos);
			if (isHit)
			{
				pickedPos->x = resultPos.x;
				pickedPos->y = resultPos.y;
				pickedPos->z = resultPos.z;
				*resultIndex = terrain->GetEditID();
				return true;
			}
		}

	}
	return false;
}

void HyEngine::EditEngine::AdjustEditCameraPos(float xPos, float yPos, float zPos)
{
	D3DXVECTOR3 curPos = m_pEditScene->GetEditCamera()->GetPosition();
	Transform* curTr = m_pEditScene->GetEditCamera()->GetTransform();

	D3DXVECTOR3 forward = curTr->Forward() * zPos;
	D3DXVECTOR3 up = curTr->Up() * yPos;
	D3DXVECTOR3 right = curTr->Right() * xPos;
	curPos += forward;
	curPos += up;
	curPos += right;
	//curPos = D3DXVECTOR3(curPos.x + xPos, curPos.y + yPos, curPos.z + zPos);

	m_pEditScene->GetEditCamera()->SetPosition(curPos.x, curPos.y, curPos.z);
}

void HyEngine::EditEngine::AdjustEditCameraRot(float xRot, float yRot, float zRot)
{
	D3DXVECTOR3 curRot = m_pEditScene->GetEditCamera()->GetRotationEuler();
	curRot = D3DXVECTOR3(curRot.x + xRot, curRot.y + yRot, curRot.z + zRot);
	m_pEditScene->GetEditCamera()->SetRotationEuler(curRot.x, curRot.y, curRot.z);

}

void HyEngine::EditEngine::GetEditCameraPos(VectorData * position)
{
	D3DXVECTOR3 pos = m_pEditScene->GetEditCamera()->m_pTransform->m_position;

	position->x = pos.x;
	position->y = pos.y;
	position->z = pos.z;
}

void HyEngine::EditEngine::GetEditCameraRot(VectorData * rotation)
{
	D3DXVECTOR3 rot = m_pEditScene->GetEditCamera()->m_pTransform->m_rotationEuler;
	rotation->x = rot.x;
	rotation->y = rot.y;
	rotation->z = rot.z;
}

void HyEngine::EditEngine::SetEditCameraPos(float xPos, float yPos, float zPos)
{
	m_pEditScene->GetEditCamera()->m_pTransform->SetPosition(xPos, yPos, zPos);
}

void HyEngine::EditEngine::SetEditCameraRot(float xRot, float yRot, float zRot)
{
	m_pEditScene->GetEditCamera()->m_pTransform->m_rotationEuler = D3DXVECTOR3(xRot, yRot, zRot);
}

void HyEngine::EditEngine::TranslateToMesh()
{
	Mesh* editMesh = dynamic_cast<Mesh*>(m_pSelectedObject);
	if (editMesh == nullptr) return;

	float radius;
	D3DXVECTOR3 center;

	bool bFinish = editMesh->ComputeBoundingSphere(&center, &radius);
	if (bFinish == false)
		return;

	D3DXVECTOR3 result = center;

	Transform* editCameraTr = m_pEditScene->GetEditCamera()->m_pTransform;

	result = result + (-editCameraTr->Forward().operator D3DXVECTOR3()) * radius;

	// 메쉬를 안정적으로 바라볼 수 있도록 일정 거리만큼 추가적으로 이동시킨다.
	result = result + (-editCameraTr->Forward().operator D3DXVECTOR3()) * 20;

	m_pEditScene->GetEditCamera()->m_pTransform->SetPosition(result);
	

}

void HyEngine::EditEngine::SetSolidMode()
{
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void HyEngine::EditEngine::SetWireFrameMode()
{
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

bool HyEngine::EditEngine::PickNavMesh(float xMousePos, float yMousePos, int cellOption, VectorData * pickedPos)
{
	Scene* scene = EDIT_SCENE;
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	return editScene->PickNavMesh(xMousePos, yMousePos, (ECellOption)cellOption, pickedPos);
}

void HyEngine::EditEngine::AddCell(CellData * cellData)
{
	NavMesh* editObj = dynamic_cast<NavMesh*>(m_pSelectedObject);
	assert(editObj);

	D3DXVECTOR3 position;
	position.x = cellData->position.x;
	position.y = cellData->position.y;
	position.z = cellData->position.z;

	editObj->AddCell(position, (ECellOption)cellData->option, cellData->group);

}

void HyEngine::EditEngine::RemoveNavPrim(int navPrimIndex)
{
	NavMesh* navMesh = dynamic_cast<NavMesh*>(m_pSelectedObject);
	assert(navMesh);

	navMesh->RemoveNavPrim(navPrimIndex);
}

int HyEngine::EditEngine::GetAnimationCount()
{
	DynamicMesh* obj = dynamic_cast<DynamicMesh*>(m_pSelectedObject);
	assert(obj);

	int count = obj->GetAnimationCount();

	return count;
}

void HyEngine::EditEngine::GetAnimationName(_Out_ AnimNameData* outString, int index)
{
	DynamicMesh* obj = dynamic_cast<DynamicMesh*>(m_pSelectedObject);
	assert(obj);
	 obj->GetAnimationName(outString, index);
	return;
}

void HyEngine::EditEngine::SetAnimation(int index)
{
	DynamicMesh* obj = dynamic_cast<DynamicMesh*>(m_pSelectedObject);
	assert(obj);
	CString a;


	obj->SetAnimationSet(index);
}

void HyEngine::EditEngine::CreateTerrain(unsigned int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddTerrain(editID);
}

void HyEngine::EditEngine::InsertTerrainData(TerrainData * data)
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->InsertTerrainData(data);
}

void HyEngine::EditEngine::CreateLight(int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddLight(editID);
}

void HyEngine::EditEngine::InsertLightData(LightData * data)
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->InsertLightData(data);
}

void HyEngine::EditEngine::CreateMeshEffect(int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddMeshEffect(editID);
}

void HyEngine::EditEngine::CreateTextureEffect(int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddTextureEffect(editID);
}

void HyEngine::EditEngine::InsertEffectData(EffectData * data)
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->InsertEffectData(data);
}

void HyEngine::EditEngine::CreateUIPanel(int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddUIPanel(editID);
}

void HyEngine::EditEngine::InsertUIData(UIData * data)
{
	if (m_pSelectedObject == nullptr)
		return;
	m_pSelectedObject->InsertUIData(data);
}

void HyEngine::EditEngine::CreateEditFont(int editID)
{
	Scene* scene = GetScene();
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddFont(editID);
}


//void HyEngine::EditEngine::PickNavMesh(float xMousePos, float yMousePos)
//{
//	m_pEditScene->PickNavMesh(xMousePos, yMousePos);
//}

GameObject * HyEngine::EditEngine::GetSelectedObject()
{
	return m_pSelectedObject;
}

HRESULT EditEngine::EnsureHWND()
{
	HRESULT hr = S_OK;

	if (!m_hWnd)
	{
		WNDCLASS wndClass;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = EditWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = NULL;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = szAppName;

		if (!RegisterClass(&wndClass))
		{
			assert(false);
		}

		m_hWnd = CreateWindow(szAppName,
			szAppName,
			WS_OVERLAPPEDWINDOW,
			0,                   // Initial X
			0,                   // Initial Y
			0,                   // Width
			0,                   // Height
			NULL,
			NULL,
			NULL,
			NULL);
	}
	return hr;
}


LRESULT CALLBACK EditWndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	EditEngine * engine =EditEngine::Get();
	if(engine != nullptr)
		EDIT_MOUSE->InputProc(umessage, wparam, lparam);
	switch (umessage)
	{
	//case WM_DESTROY:	// Check if the window is being destroyed.
	//	PostQuitMessage(0);
	//	return 0;

	//case WM_QUIT:		// Check if the window is being closed.
	//	PostQuitMessage(0);
	//	return 0;
	//default: // All other messages pass to the message handler in the system class.
	//	return g_pAppHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	return DefWindowProc(hwnd, umessage, wparam, lparam);
}
