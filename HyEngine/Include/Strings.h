#pragma once
#include "StandardEngineFramework.h"


namespace EngineTags
{
	static std::wstring Default = L"Default";
	static std::wstring Player = L"Player";
	static std::wstring Obstacle = L"Obstacle";
	static std::wstring Enemy = L"Enemy";
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

}