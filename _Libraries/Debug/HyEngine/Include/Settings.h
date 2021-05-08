#pragma once

#include <string.h>
#include <vector>

namespace HyEngine
{
	namespace Settings
	{
		//------------------------------------------------------------
		// RENDERING
		//------------------------------------------------------------
		struct Bloom
		{
			bool bEnabled;
			float brightnessThreshold;
			int blurStrength = 1;
		};
		struct SSAO
		{
			bool bEnabled;
			float ambientFactor;
			float radius;
			float intensity;
		};
		struct Rendering
		{
			// TODO : something
		};


		//------------------------------------------------------------
		// ENGINE
		//------------------------------------------------------------

		struct Logger
		{
			bool bConsol;
			bool bFile;
		};

		struct Window
		{
			int width;
			int height;
			int fullScreen;
			int vsync;
		};


		struct Engine
		{
			Logger logger;
			Window window;
			int levelToLoad;
			std::vector<std::string> sceneNames;

		};

		//------------------------------------------------------------
		// SCENE
		//------------------------------------------------------------
		struct Optimization
		{
			bool bViewFrustumCull_MainView = true;
			bool bViewFrustumCull_LocalLights = true;
			bool bSortRenderLists = true;
		};
		struct SceneRender
		{
			SSAO ssao;
			bool bSkylightEnabled;
			Bloom bloom;

			Optimization optimization;
		};
	}
}