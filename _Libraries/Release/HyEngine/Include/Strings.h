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
	// �ӽ� 
	// ���߿� ���� �о ������ �� �ֵ��� ���� ����
	const std::wstring SolutionName = L"Dx9_Bless";
	const std::wstring MeshPath = L"./Resources/Mesh/";
	const std::wstring TexturePath = L"./Resources/Texture/";

	const std::wstring CubePath = MeshPath + L"Cube.obj";
	const std::wstring CheckerPath = TexturePath + L"Checker.png";
}

