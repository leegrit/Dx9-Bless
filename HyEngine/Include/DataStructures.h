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

	std::vector<Scene*> scenes = {};
	Scene* loadingScene = nullptr;
	Camera * camera = nullptr;
	int defaultSceneIndex;
};