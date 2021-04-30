#pragma once
#include "StandardEngineFramework.h"

struct ENGINE_DLL BehaviourType
{
	static const DWORD Update = 1;
	static const DWORD LateUpdate = 2;
	static const DWORD None = 4;
};

struct RenderType
{
	static const DWORD RenderOpaque = 1;
	static const DWORD RenderAlpha = 2;
	static const DWORD RenderUI = 4;
	static const DWORD RenderDebug = 8;
	static const DWORD None = 16;
	static const DWORD Texture = 32;
};

namespace RenderOptions
{
	static const DWORD RenderCollider = 4;
	static const DWORD RenderNavMesh = 8;
	static const DWORD RenderUI = 16;
	static const DWORD RenderShadow = 32;
	static const DWORD RenderLight = 64;
}