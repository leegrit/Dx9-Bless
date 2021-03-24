#include "StandardEngineFramework.h"
#include "EditEngine.h"
#include "EditScene.h"
#include "EditObject.h"
#include "Renderer.h"
#include "EditData.h"
#include "GameObjectData.h"
#include "MeshData.h"

using namespace Editor;

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


void EditEngine::Release(EditEngine ** engine)
{
	SAFE_DELETE(*engine);
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
	m_pEditScene->UpdateScene();
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
	GameObject* selectedObj =  scene->GetMeshObject(index);
	m_pSelectedObject = selectedObj;
}

void Editor::EditEngine::InsertGameData(GameObjectData* data)
{
	if (m_pSelectedObject == nullptr)
		return;
	EditObject* obj = dynamic_cast<EditObject*>(m_pSelectedObject);
	assert(obj);
	obj->InsertGameData(data);
}

void Editor::EditEngine::InsertMeshData(MeshData * data)
{
	if (m_pSelectedObject == nullptr)
		return;
	EditObject* obj = dynamic_cast<EditObject*>(m_pSelectedObject);
	assert(obj);
	obj->InsertMeshData(data);
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
