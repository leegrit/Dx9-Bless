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
	DirectXDevice::Create();
	UIDGen::Create();
	m_pRenderer = new Renderer();
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
	SAFE_DELETE(m_pRenderer);
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





bool EditEngine::Initialize()
{
	HRESULT hr = EnsureHWND();
	assert(SUCCEEDED(hr));
	DirectXDevice::Get()->Init(m_hWnd);
	m_pTimer->start();
	return true;
}

bool EditEngine::Load()
{
	m_bLoading = true;
	m_pEditScene = new EditScene();
	m_pEditScene->LoadScene();


	m_bLoading = false;
	return true;
}

void EditEngine::Render()
{
	m_pRenderer->RenderBegin();

	m_pEditScene->RenderScene(m_pRenderer);

	m_pRenderer->RenderEnd();
}

void EditEngine::Update()
{
	EDIT_TIMER->tick();
	m_pEditScene->UpdateScene();
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
	for (auto& obj : editScene->GetMeshObjectAll())
	{
		EditObject* editObj = dynamic_cast<EditObject*>(obj);
		if (editObj->GetEditID() == index)
		{
			Object::Destroy(editObj);
			return;
		}
	}
}

bool HyEngine::EditEngine::PickGameObject(float xMousePos, float yMousePos, _Out_ int * resultIndex)
{
	for (auto& obj :  GetScene()->GetMeshObjectAll())
	{
		EditMesh* editObj = dynamic_cast<EditMesh*>(obj);
		if (editObj == nullptr)
			continue;

		// picking은 xfile만 가능
		ID3DXMesh* mesh = editObj->GetDxMesh();
		if (mesh == nullptr) continue;

		D3DXVECTOR3 origin;
		D3DXVECTOR3 direction;
		m_pEditScene->GetEditCamera()->UnProjection(&origin, &direction, D3DXVECTOR3(xMousePos, yMousePos, 0));
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
			return true;
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
	EditMesh* editMesh = dynamic_cast<EditMesh*>(m_pSelectedObject);
	if (editMesh == nullptr) return;

	float radius;
	D3DXVECTOR3 center;

	bool bFinish = editMesh->CalcBounds(&center, &radius);
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

int HyEngine::EditEngine::GetAnimationCount()
{
	EditDynamicMesh* obj = dynamic_cast<EditDynamicMesh*>(m_pSelectedObject);
	assert(obj);

	int count = obj->GetAnimationCount();

	return count;
}

void HyEngine::EditEngine::GetAnimationName(_Out_ AnimNameData* outString, int index)
{
	EditDynamicMesh* obj = dynamic_cast<EditDynamicMesh*>(m_pSelectedObject);
	assert(obj);
	 obj->GetAnimationName(outString, index);
	return;
}

void HyEngine::EditEngine::SetAnimation(int index)
{
	EditDynamicMesh* obj = dynamic_cast<EditDynamicMesh*>(m_pSelectedObject);
	assert(obj);
	CString a;


	obj->SetAnimationSet(index);
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
