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

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	D3DXMESHCONTAINER_DERIVED() = default;
	D3DXMESHCONTAINER_DERIVED(const D3DXMESHCONTAINER_DERIVED& rhs)
	{
		if (rhs.Name != nullptr)
			strcpy_s(Name, strlen(rhs.Name) + 1, rhs.Name);
		else
			Name = nullptr;
		
		MeshData.Type = rhs.MeshData.Type;
		D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
		rhs.MeshData.pMesh->GetDeclaration(meshDeclaration);
		rhs.MeshData.pMesh->CloneMesh(rhs.MeshData.pMesh->GetOptions(), meshDeclaration,
			DEVICE, &MeshData.pMesh);

		pMaterials = rhs.pMaterials;
		pEffects = rhs.pEffects;
		NumMaterials = rhs.NumMaterials;
		pAdjacency = rhs.pAdjacency;
		pSkinInfo = rhs.pSkinInfo;

		if (rhs.pNextMeshContainer != nullptr)
			pNextMeshContainer = new D3DXMESHCONTAINER_DERIVED(*(D3DXMESHCONTAINER_DERIVED*)rhs.pNextMeshContainer);
		else
			pNextMeshContainer = nullptr;

		ppTexture = rhs.ppTexture;
		ppNormal = rhs.ppNormal;

		pTextureNames = rhs.pTextureNames;

		pOriMesh = rhs.pOriMesh;

		numBones = rhs.numBones;
		pFrameOffsetMatrix = new D3DXMATRIX();
		if(rhs.pFrameOffsetMatrix != nullptr)
			*pFrameOffsetMatrix = *rhs.pFrameOffsetMatrix;

		ppFrameCombinedMatrix = new D3DXMATRIX*[numBones];

		for (ULONG i = 0; i < numBones; i++)
			pFrameOffsetMatrix[i] = *pSkinInfo->GetBoneOffsetMatrix(i);

		pRenderingMatrix = new D3DXMATRIX();
		*pRenderingMatrix = *rhs.pRenderingMatrix;
	}
	LPDIRECT3DTEXTURE9* ppTexture;
	LPDIRECT3DTEXTURE9* ppNormal;
	LPDIRECT3DTEXTURE9* ppSpecularMask;

	std::vector<std::wstring>		pTextureNames;
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


struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXFRAME_DERIVED() = default;
	D3DXFRAME_DERIVED(const D3DXFRAME_DERIVED& rhs)
	{
		if (rhs.pFrameSibling != nullptr)
			pFrameSibling = new D3DXFRAME(*rhs.pFrameSibling);
		else
			pFrameSibling = nullptr;

		if (rhs.pFrameFirstChild != nullptr)
			pFrameFirstChild = new D3DXFRAME(*rhs.pFrameFirstChild);
		else
			pFrameFirstChild = nullptr;

		if (rhs.Name != nullptr)
			strcpy_s(Name, strlen(rhs.Name) + 1, rhs.Name);
		else
			Name = nullptr;

		TransformationMatrix = rhs.TransformationMatrix;

		if (rhs.pMeshContainer != nullptr)
			pMeshContainer = new D3DXMESHCONTAINER_DERIVED(*(D3DXMESHCONTAINER_DERIVED*)rhs.pMeshContainer);
		else
			pMeshContainer = nullptr;
	}
	D3DXMATRIX CombinedTransformMatrix;
};
