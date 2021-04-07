#pragma once
#include "StandardEngineFramework.h"
#include "Camera.h"
using namespace HyEngine;

struct RendererState
{
	int numVertices;
	int numIndices;
	int numDrawCalls;
	int numTriangles;
};

struct SceneStats
{
	int numObjects;

	int numMainViewCulledObjects;



};

struct ENGINE_DLL EngineConfig
{
	bool bShowBoundingBoxes;
	bool bShowDebuger;
	bool bShowProfiler;

	// �����ʿ���
	std::vector<Scene*> scenes = {};
	Scene* loadingScene = nullptr;
	Camera * camera = nullptr;
	int defaultSceneIndex;
};


struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformMatrix;
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9* ppTexture;
	std::wstring*		pTextureNames;
	// ���� �޽�
	LPD3DXMESH			pOriMesh;

	unsigned long		numBones;
	// ���� �迭�� �Ҵ�, ����� �ּҰ� ������
	// �ִϸ��̼��� ������ ���·� �������� �� �� ������ ������� �����ִ� ���
	D3DXMATRIX*			pFrameOffsetMatrix;

	// ������ ������ �ִ� CombinedTransformationMatrix�� ��� ���ŵǱ� ������
	// �� CombinedTransformationMatrix ����� �ּҸ� �����ؼ� �Ź� ���ŵ� ����� ������ ���´�.
	D3DXMATRIX**		ppFrameCombinedMatrix;

	D3DXMATRIX*			pRenderingMatrix;

};