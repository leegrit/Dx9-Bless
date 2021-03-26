#pragma once



//enum class RenderType
//{
//	RenderOpaque = 0x0001,
//	RenderAlpha = 0x0002,
//	RenderUI = 0x0004,
//	RenderDebug = 0x0008,
//	None = 0x0010,
//};
struct RenderType
{
	static const DWORD RenderOpaque = 0x0001;
	static const DWORD RenderAlpha = 0x0002;
	static const DWORD RenderUI = 0x0004;
	static const DWORD RenderDebug = 0x0008;
	static const DWORD None = 0x0010;
	static const DWORD Texture = 0x0020;
};
//enum class LogicType
//{
//	Update = 0x0001,
//	LateUpdate = 0x0002,
//	None = 0x0004,
//};
struct ENGINE_DLL BehaviourType
{
	static const DWORD Update = 0x0001;
	static const DWORD LateUpdate = 0x0002;
	static const DWORD None = 0x0004;
};

namespace EngineTags
{
	static std::wstring Default = L"Default";
	static std::wstring Player = L"Player";
	static std::wstring Obstacle = L"Obstacle";
	static std::wstring Enemy = L"Enemy";
}

enum class ERenderType
{
	RenderMesh,
	RenderD3DXMesh,
	//RenderOpaque,
	//RenderAlpha,
	RenderTexture,
	//AlphaTexture,
	RenderUI,
	None,
};

enum class EUpdateResult
{
	Continue,
	Stop,
};

enum class EColliderType
{
	Static,
	Dynamic,
	Multipurpose, // 자동 충돌연산x
};
enum class ECollisionLayer
{
	Default,

};
enum class EColliderShape
{
	Sphere,
	Box,
	AABB,
	OBB,
};

enum class EButtonEvent
{
	ButtonDown,
	ButtonUp,
	ButtonPress,
	ButtonCollisionEnter,
	ButtonCollisionStay,
	ButtonCollisionExit,
};

enum class ELightType
{
	DIRECTIONAL,
	POINT,
};

enum class EBillboardType
{
	All,
	X,
	Y,
	Z
};

enum class ED3DXMeshType
{
	Box,
	Torus,
	Cylinder,
	Sphere
};
enum class ELoopType
{
	Default,
	Loop,
	Infinity
};


// For Editor
enum class EStaticType
{
	Nothing,
	Navigation,
};

// For NavMesh
namespace NavMeshEnums
{
	enum class EPoint
	{
		POINT_A,
		POINT_B,
		POINT_C,
		POINT_END,
	};
	enum class ELine
	{
		LINE_AB,
		LINE_BC,
		LINE_CA,
		LINE_END,
	};
	enum class ENeighbor
	{
		NEIGHBOR_AB,
		NEIGHBOR_BC,
		NEIGHBOR_CA,
		NEIGHBOR_END,
	};
	enum class ECompare
	{
		COMPARE_MOVE,
		COMPARE_STOp
	};
	enum class ECellOption
	{
		NORMAL,
		TRIGGER,
		EVENT,
	};
}