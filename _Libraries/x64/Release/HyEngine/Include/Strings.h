#pragma once
#include "StandardEngineFramework.h"


namespace EngineTags
{
	static std::wstring Default = L"Default";
	static std::wstring Player = L"Player";
	static std::wstring Obstacle = L"Obstacle";
	static std::wstring Enemy = L"Enemy";
}

namespace RenderEvent
{
	static std::string RenderBegin = "RenderEvent.RenderBegin";
	static std::string RenderEnd = "RenderEvent.RenderEnd";
}

namespace EngineEvent
{
	static std::string ModeChanged = "EngineEvent.ModeChanged";
	static std::string ObjectDestroyed = "EngineEvent.ObjectDestroyed";
}


namespace DefaultPath
{
	// 임시 
	// 나중에 파일 읽어서 세팅할 수 있도록 수정 예정
	const std::wstring SolutionName = L"Dx9_Bless";
	const std::wstring MeshPath = L"./Resources/Mesh/";
	const std::wstring TexturePath = L"./Resources/Texture/";

	const std::wstring CubePath = MeshPath + L"Cube.obj";
	const std::wstring CheckerPath = TexturePath + L"Checker.png";
}

namespace JsonKey
{
	const std::string Hierarchy = "Hierarchy";
	const std::string GameObjectData = "GameObjectData";
	const std::string MeshData = "MeshData";
	const std::string MapData = "MapData";
	const std::string NavMeshData = "NavMeshData";
	const std::string TerrainData = "TerrainData";
	const std::string LightData = "LightData";
	const std::string EffectData = "EffectData";

	const std::string Index = "Index";
	const std::string Name = "Name";
	const std::string Tag = "Tag";
	const std::string Layer = "Layer";
	const std::string StaticType = "StaticType";
	const std::string Transform = "Transform";
	const std::string Position = "Position";
	const std::string Rotation = "Rotation";
	const std::string Scale = "Scale";
	const std::string X = "X";
	const std::string Y = "Y";
	const std::string Z = "Z";
	const std::string MeshFilePath = "MeshFilePath";
	const std::string DiffuseTexturePath = "DiffuseTexturePath";
	const std::string Group = "Group";
	const std::string CellCount = "CellCount";
	const std::string MapCount = "MapCount";

	const std::string Cell = "Cell_";
	const std::string CellIndex = "CellIndex";
	const std::string PositionX = "PositionX";
	const std::string PositionY = "PositionY";
	const std::string PositionZ = "PositionZ";
	const std::string Option = "Option";

	/* For Terrain Data */
	const std::string VertexCountX = "VertexCountX";
	const std::string VertexCountZ = "VertexCountZ";
	const std::string TextureCountX = "TextureCountX";
	const std::string TextureCountZ = "TextureCountZ";
	const std::string VertexInterval = "VertexInterval";
	const std::string DiffuseFilePath = "DiffuseFilePath";
	const std::string NormalFilePath = "NormalFilePath";

	/* For Light Data */
	const std::string LightType = "LightType";
	const std::string Direction = "Direction";
	const std::string Ambient = "Ambient";
	const std::string R = "R";
	const std::string G = "G";
	const std::string B = "B";
	const std::string A = "A";
	const std::string AmbientIntensity = "AmbientIntensity";
	const std::string Diffuse = "Diffuse";
	const std::string DiffuseIntensity = "DiffuseIntensity";
	const std::string Specular = "Specular";
	const std::string SpecularIntensity = "SpecularIntensity";
	const std::string SpecularPower = "SpecularPower";
	const std::string Range = "Range";
	const std::string Cone = "Cone";
	const std::string Constant = "Constant";
	const std::string Linear = "Linear";
	const std::string Quadratic = "Quadratic";
}