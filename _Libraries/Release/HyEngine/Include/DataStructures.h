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

	// 수정필요함
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
	// 원본 메쉬
	LPD3DXMESH			pOriMesh;

	unsigned long		numBones;
	// 동적 배열로 할당, 행렬의 주소값 보관용
	// 애니메이션을 포함한 형태로 렌더링을 할 때 최초의 뼈대들이 갖고있는 행렬
	D3DXMATRIX*			pFrameOffsetMatrix;

	// 뺘들이 가지고 있는 CombinedTransformationMatrix가 계속 갱신되기 때문에
	// 그 CombinedTransformationMatrix 행렬의 주소를 보관해서 매번 갱신된 행렬의 정보를 얻어온다.
	D3DXMATRIX**		ppFrameCombinedMatrix;

	D3DXMATRIX*			pRenderingMatrix;

};