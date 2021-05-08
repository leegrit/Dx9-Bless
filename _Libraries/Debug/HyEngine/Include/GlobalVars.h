#pragma once
#include "StandardEngineFramework.h"

struct ENGINE_DLL BehaviourType
{
	static const DWORD Update = 0x0001;
	static const DWORD LateUpdate = 0x0002;
	static const DWORD None = 0x0004;
};

struct RenderType
{
	static const DWORD RenderOpaque = 0x0001;
	static const DWORD RenderAlpha = 0x0002;
	static const DWORD RenderUI = 0x0004;
	static const DWORD RenderDebug = 0x0008;
	static const DWORD None = 0x0010;
	static const DWORD Texture = 0x0020;
};