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

