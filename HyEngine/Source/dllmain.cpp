#include "StandardEngineFramework.h"
#include "EditEngine.h"
#include "EditScene.h"
#include "GameObjectData.h"
#include "MeshData.h"
using namespace Editor;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//static EditEngine* pEditEngine = nullptr;

extern "C" void WINAPI Initialize()
{
	EditEngine::Create();
	//assert(pEditEngine);
}

extern "C" void WINAPI GetBackBuffer(_Out_ IDirect3DSurface9** ppSurface)
{
	EDIT_ENGINE->GetBackBuffer(ppSurface);
	//assert(ppSurface);
}

extern "C" void WINAPI Update()
{
	EDIT_ENGINE->Update();
}
extern "C" void WINAPI Render()
{
	EDIT_ENGINE->Render();
}

extern "C" void WINAPI Destroy()
{
	//EditEngine::Release(&pEditEngine);
	EditEngine::Destroy();
}

extern "C" void WINAPI AddGameObject(int index)
{
//test
	Scene* scene = EDIT_SCENE;
	assert(scene);
	EditScene * editScene = dynamic_cast<EditScene*>(scene);
	assert(editScene);
	editScene->AddMeshObject(index);
}


extern "C" __declspec(dllexport) void WINAPI InsertGameData(GameObjectData* data)
{
	EDIT_ENGINE->InsertGameData(data);
}
extern "C" __declspec(dllexport) void WINAPI InsertMeshData(MeshData* data)
{
	EDIT_ENGINE->InsertMeshData(data);
}

extern "C" void WINAPI SelectEditObject(int index)
{
	EDIT_ENGINE->SelectObject(index);
}