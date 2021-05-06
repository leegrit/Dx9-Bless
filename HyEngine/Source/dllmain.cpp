#include "StandardEngineFramework.h"
#include "EditEngine.h"
#include "EditScene.h"
#include "GameObjectData.h"
#include "MeshData.h"
#include "CellData.h"
#include "EditObject.h"
#include "AnimNameData.h"
#include "TerrainData.h"
#include "LightData.h"
#include "EffectData.h"
#include "UIData.h"

using namespace HyEngine;

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
	EditEngine::Destroy();
}

extern "C" void WINAPI AddGameObject(int index)
{
	EDIT_ENGINE->AddGameObject(index);
}
extern "C" void WINAPI AddPawn(int index)
{
	EDIT_ENGINE->AddPawn(index);
}
extern "C" void WINAPI AddNavMesh(int index)
{
	EDIT_ENGINE->AddNavMesh(index);
}

extern "C" void WINAPI RemoveGameObject(int index)
{
	EDIT_ENGINE->RemoveGameObject(index);
}


extern "C" __declspec(dllexport) void WINAPI InsertGameData(GameObjectData* data)
{
	EDIT_ENGINE->InsertGameData(data);
}
extern "C" __declspec(dllexport) void WINAPI InsertMeshData(MeshData* data)
{
	EDIT_ENGINE->InsertMeshData(data);
}
extern "C" __declspec(dllexport) void WINAPI InsertCellData(CellData* data, int cellEditMode)
{
	EDIT_ENGINE->InsertCellData(data, cellEditMode);
}

extern "C" void WINAPI SelectEditObject(int index)
{
	EDIT_ENGINE->SelectObject(index);
}

extern "C" void WINAPI ActiveEditObject()
{
	EDIT_ENGINE->ActiveObject();
}

extern "C" void WINAPI InactiveEditObject()
{
	EDIT_ENGINE->InactiveObject();
}
extern "C" void WINAPI AdjustEditCameraPos(float xPos, float yPos, float zPos)
{
	EDIT_ENGINE->AdjustEditCameraPos(xPos, yPos, zPos);
}
extern "C" void WINAPI AdjustEditCameraRot(float xRot, float yRot, float zRot)
{
	EDIT_ENGINE->AdjustEditCameraRot(xRot, yRot, zRot);
}

extern "C" void WINAPI SetSolidMode()
{
	EDIT_ENGINE->SetSolidMode();
}
extern "C" void WINAPI SetWireFrameMode()
{
	EDIT_ENGINE->SetWireFrameMode();
}


extern "C" bool WINAPI PickNavMesh(float xMousePos, float yMousePos,int cellOption,  VectorData* pickedPos)
{
	return EDIT_ENGINE->PickNavMesh(xMousePos, yMousePos, cellOption, pickedPos);
}

extern "C" void WINAPI GetEditCameraPos(_Out_ VectorData* position)
{
	EDIT_ENGINE->GetEditCameraPos(position);
}
extern "C" void WINAPI GetEditCameraRot(_Out_ VectorData* rotation)
{
	EDIT_ENGINE->GetEditCameraRot(rotation);
}

extern "C" void WINAPI SetEditCameraPos(float xPos, float yPos, float zPos)
{
	EDIT_ENGINE->SetEditCameraPos(xPos, yPos, zPos);
}

extern "C" void WINAPI SetEditCameraRot(float xRot, float yRot, float zRot)
{
	EDIT_ENGINE->SetEditCameraRot(xRot, yRot, zRot);
}
extern "C" void WINAPI TranslateToMesh()
{
	EDIT_ENGINE->TranslateToMesh();
}
extern "C" bool WINAPI PickGameObject(float xMousePos, float yMousePos, _Out_ int * resultIndex, _Out_ VectorData* pickedPos)
{
	bool isPicked = EDIT_ENGINE->PickGameObject(xMousePos, yMousePos, resultIndex, pickedPos);
	return isPicked;
}
extern "C" void WINAPI AddCell(CellData* cellData)
{
	EDIT_ENGINE->AddCell(cellData);
}
extern "C" void WINAPI RemoveNavPrim(int navPrimIndex)
{
	EDIT_ENGINE->RemoveNavPrim(navPrimIndex);
}

extern "C" int WINAPI GetAnimationCount()
{
	return EDIT_ENGINE->GetAnimationCount();
}
extern "C" void WINAPI GetAnimationName(_Out_ AnimNameData* outString, int index)
{
	EDIT_ENGINE->GetAnimationName(outString, index);
}
extern "C" void WINAPI SetAnimation(int index)
{
	EDIT_ENGINE->SetAnimation(index);
}

//////////////////////////////////////////////////////////////////////////
// FOR TERRAIN
//////////////////////////////////////////////////////////////////////////
extern "C" void WINAPI CreateTerrain(unsigned int editID)
{
	EDIT_ENGINE->CreateTerrain(editID);
}
extern "C" void WINAPI InsertTerrainData(TerrainData* data)
{
	EDIT_ENGINE->InsertTerrainData(data);
}


//////////////////////////////////////////////////////////////////////////
// FOR LIGHT
//////////////////////////////////////////////////////////////////////////
extern "C" void WINAPI CreateLight(int editID)
{
	EDIT_ENGINE->CreateLight(editID);
}
extern "C" void WINAPI InsertLightData(LightData* data)
{
	EDIT_ENGINE->InsertLightData(data);
}

//////////////////////////////////////////////////////////////////////////
// FOR EFFECT
//////////////////////////////////////////////////////////////////////////
extern "C" void WINAPI CreateMeshEffect(int editID)
{
	EDIT_ENGINE->CreateMeshEffect(editID);
}
extern "C" void WINAPI CreateTextureEffect(int editID)
{
	EDIT_ENGINE->CreateTextureEffect(editID);
}
extern "C" void WINAPI InsertEffectData(EffectData* data)
{
	EDIT_ENGINE->InsertEffectData(data);
}

//////////////////////////////////////////////////////////////////////////
// FOR UI
//////////////////////////////////////////////////////////////////////////
extern "C" void WINAPI CreateUIPanel(int editID)
{
	EDIT_ENGINE->CreateUIPanel(editID);
}
extern "C" void WINAPI InsertUIData(UIData* data)
{
	EDIT_ENGINE->InsertUIData(data);
}
//////////////////////////////////////////////////////////////////////////
// FOR FONT
//////////////////////////////////////////////////////////////////////////
extern "C" void WINAPI CreateEditFont(int editID)
{
	EDIT_ENGINE->CreateEditFont(editID);
}