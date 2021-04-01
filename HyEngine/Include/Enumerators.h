#pragma once



//enum class RenderType
//{
//	RenderOpaque = 0x0001,
//	RenderAlpha = 0x0002,
//	RenderUI = 0x0004,
//	RenderDebug = 0x0008,
//	None = 0x0010,
//};

//enum class LogicType
//{
//	Update = 0x0001,
//	LateUpdate = 0x0002,
//	None = 0x0004,
//};




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
enum class EDataType
{
	GameObjectData,
	MeshData,
	CellData,
	TerrainData,
	End
};

enum class ECellEditMode
{
	Similar, // 근처 버텍스도 같이 이동
	Selected, // 선택한 버텍스만 이동
};