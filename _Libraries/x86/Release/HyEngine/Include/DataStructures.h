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

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	D3DXMESHCONTAINER_DERIVED() = default;
	D3DXMESHCONTAINER_DERIVED(const D3DXMESHCONTAINER_DERIVED& rhs)
	{
		if (rhs.Name != nullptr)
			strcpy_s(Name, strlen(rhs.Name), rhs.Name);
		else
			Name = nullptr;

		MeshData = rhs.MeshData;

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

	std::vector<std::wstring>		pTextureNames;
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
			strcpy_s(Name, strlen(rhs.Name), rhs.Name);
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
