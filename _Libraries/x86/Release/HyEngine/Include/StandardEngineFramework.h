#pragma once

#ifdef _DEBUG
//#define TEST_MODE
#define COLLIDER_RENDER
//#define FULL_SCREEN
#endif

#ifdef EXPORTS_ENGINE
#define _EDITOR
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

/* jsoncpp */
#include "json-forwards.h"
#include "Json.h"

#include "imgui.h"

/* ImGui */
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
//#pragma comment(lib, "ImGui.lib")

// #include <Jsoncpp/Include/json.h>
// #pragma comment(lib, "Jsoncpp/Lib/jsoncpp.lib")


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

//SeverityType::info
#define SEND_LOG(Message)  ServiceLocator::getFileLogger()->print<SeverityType::info>(Message)
#define SEND_LOG_WARNING(Message) ServiceLocator::getFileLogger()->print<SeverityType::warning>(Message)
#define SEND_LOG_ERROR(Message) ServiceLocator::getFileLogger()->print<SeverityType::error>(Message)
#ifdef _DEBUG
#define SEND_LOG_DEBUG(Message) ServiceLocator::getFileLogger()->print<SeverityType::debug>(Message)
#else
#define SEND_LOG_DEBUG(Message) 
#endif


/* Editor 환경인지 Client인지 확인용도 */
// EditEngine이 Null이라면 Client
#define IS_EDITOR EditEngine::Get()

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

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif