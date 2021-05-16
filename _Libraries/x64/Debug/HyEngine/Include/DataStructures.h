#pragma once
#include "StandardEngineFramework.h"
#include "Camera.h"
using namespace HyEngine;
namespace HyEngine
{
	class Scene;
}
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
	bool bFullScreen;
	bool bShowProfiler;

	// �����ʿ���
	std::vector<Scene*> scenes = {};
	Scene* loadingScene = nullptr;
	Camera * camera = nullptr;
	int defaultSceneIndex;
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{

	LPDIRECT3DTEXTURE9* ppTexture;
	LPDIRECT3DTEXTURE9* ppNormal;
	LPDIRECT3DTEXTURE9* ppSpecularMask;

	std::vector<std::wstring>		pTextureNames;
	// ���� �޽�
	LPD3DXMESH			pOriMesh;

	DWORD numAttributeGroups;
	D3DXATTRIBUTERANGE * pAttributeTable;

	ID3DXBuffer* pBoneCombinationBuf;

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
	D3DXMATRIX CombinedTransformMatrix;
};
