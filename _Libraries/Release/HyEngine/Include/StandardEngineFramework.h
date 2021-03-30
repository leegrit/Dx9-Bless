#pragma once

#ifdef _DEBUG
//#define TEST_MODE
#define COLLIDER_RENDER
//#define FULL_SCREEN
#endif

#pragma warning(disable : 4251)
#pragma warning(disable : 4503)

#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string.h>
#include <assert.h>
#include <random>
#include <process.h>
#include <codecvt>
#include <locale>

/* DirectX9 */
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <DirectXMath.h>

#undef min
#undef max






#include "Settings.h"

/* Global Vars */
#include "Defines.h"
#include "Strings.h"
#include "Macros.h"
#include "Enumerators.h"

#include "GlobalVars.h"


// Utilities
//#include "ObjLoader.h"
#include "cpplinq.h"
#include "Singleton.h"
#include "EventDispatcher.h"
#include "Log.h"
#include "ServiceLocator.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "MathUtils.h"
#include "LinearMath.h"
#include "UIDGen.h"
#include "DxMath.h"
#include "DxHelper.h"
#include "fsm.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
#include "CString.h"
#include "Functor.h"
#include "Path.h"


// Data


// Core
#include "Layer.h"
#include "Timer.h"
#include "DirectXDevice.h"
#include "DataStructures.h"
#include "Scene.h"
#include "LoadingScene.h"
#include "Transform.h"
#include "Application.h"
#include "Engine.h"
#include "Collider.h"
#include "SphereCollider.h"

// Geometry
#include "Mesh.h"

// ---------------------------------------
// EDITOR
// --------------------------------------
#include "EditEngine.h"
#include "EnumForEditor.h"
#include "StringForEditor.h"



#define ENGINE Engine::Get()
#define KEYBOARD Engine::Get()->GetKeyboard()
#define MOUSE Engine::Get()->GetMouse()
#define TIMER Engine::Get()->GetTimer()
#define SCENE Engine::Get()->GetActiveScene()
#define CAMERA Engine::Get()->GetActiveScene()->GetSelectedCamera()
#define PLAYER Engine::Get()->GetActiveScene()->GetPlayer()

#define EDIT_ENGINE EditEngine::Get()
#define EDIT_KEYBOARD EditEngine::Get()->GetKeyboard()
#define EDIT_MOUSE EditEngine::Get()->GetMouse()
#define EDIT_SCENE EditEngine::Get()->GetScene()
#define EDIT_TIMER EditEngine::Get()->GetTimer()

// UI 
#include "UIElement.h"
#include "UIButton.h"
#include "ImageButton.h"
#include "ProgressBar.h"
#include "ProgressVerticalBar.h"
#include "UIPanel.h"

