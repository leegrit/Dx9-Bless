#include "StandardEngineFramework.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"
#include "UpdateDispatcher.h"
#include "SceneTransition.h"
#include "LoadingScene.h"
#include "EventDispatcher.h"
#include "ScriptableData.h"
#include "PathManager.h"

using namespace HyEngine;

Settings::Engine Engine::sEngineSettigns ;

IMPLEMENT_SINGLETON(Engine)

// todo keyboard, mouse, timer
Engine::Engine()
	: 
	m_bLoading(false),
	m_bIsPaused(false)
{
	SEND_LOG("Engine Created");
	DirectXDevice::Create();
	UIDGen::Create();
	PathManager::Create();

	
	//m_pRenderer = new Renderer();
	m_pMouse = new IO::Mouse();
	m_pKeyboard = new IO::Keyboard();
	m_pTimer = new Timer();
	
}
Engine::~Engine()
{
	delete m_pTimer;
	delete m_pKeyboard;
	delete m_pMouse;
	//delete m_pRenderer;
	Renderer::Release(m_pRenderer);
	DirectXDevice::Destroy();
	UIDGen::Destroy();
	PathManager::Destroy();
}

bool Engine::Initialize(HWND hWnd, EngineConfig engineConfig)
{
	SEND_LOG("Engine Initialize Start");
	DirectXDevice::Get()->Init(hWnd);
	m_pRenderer = Renderer::Create();
	m_pTimer->start();

	assert(engineConfig.scenes.size() != 0);

	this->engineConfig = engineConfig;
	m_scenes = engineConfig.scenes;
	SEND_LOG("Engine Initialize End");
	return false;
}

void Engine::Exit()
{
	m_pActiveScene->UnloadScene();
	m_pLoadingScene->UnloadScene();

	SAFE_DELETE(m_pSceneTransition);
	SAFE_DELETE(m_pLoadingScene);
	for (auto& scene : m_scenes)
	{
		SAFE_DELETE(scene);
	}
	for (auto& data : m_scriptableDatas)
	{
		delete data.second;
	}
	m_scriptableDatas.clear();
}

bool Engine::Load()
{
	m_bLoading = true;

	LoadShaders();


	if (engineConfig.loadingScene == nullptr)
		m_pLoadingScene = new LoadingScene();
	else
		m_pLoadingScene = (LoadingScene*)engineConfig.loadingScene;
	m_currentLevel = engineConfig.defaultSceneIndex;
	SAFE_DELETE(m_pSceneTransition);
	m_pSceneTransition = new SceneTransition();
	// 처음엔 current scene이 없기때문에 null을 넣는다.
	m_pSceneTransition->Transit(nullptr, m_scenes[m_currentLevel],
	[&](){
		// on completed 
	
		m_pActiveScene = m_scenes[m_currentLevel];
		m_scenes[m_currentLevel]->LoadScene();
		
		m_pActiveScene->LateLoadScene();
		TIMER->reset();
	});
	//LoadScenes();

	m_bLoading = false;
	return false;
}

void Engine::SimulateFrame()
{
	// 여기서 폰트 정보를 초기화해준다.
	m_fontInfos.clear();

	//m_pCamera->Update();
	m_pKeyboard->Update();
	m_pMouse->Update();
	/*__try
	{*/
		UpdateDispatcher::Update();
	/*}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG
		
		<< "UpdateDispatcher Exception" << std::endl;
#endif
	}*/
	if (m_pActiveScene)
	{
		m_pActiveScene->UpdateScene();
		// 여기서 오브젝트의 변경된 사항을 갖고 컬링한다.
		// 나중에 이 정보를 활용해서 렌더쪽에서 컬 처리 후 그린다.
		m_pActiveScene->ViewFrustumCull();
	}
	while (m_eventQueue.size())
	{
		m_eventQueue.back()();
		m_eventQueue.pop();
	}
}

void Engine::RenderFrame()
{
	m_pRenderer->RenderBegin();
	//DEVICE->SetTransform(D3DTS_PROJECTION, &m_pCamera->GetProjectionMatrix());
	//DEVICE->SetTransform(D3DTS_VIEW, &m_pCamera->GetViewMatrix());


	if (m_pActiveScene)
		m_pActiveScene->RenderScene(m_pRenderer);

	RenderFont();
	m_pRenderer->RenderEnd();
}

Scene * Engine::GetActiveScene()
{
	return m_pActiveScene;
}

void HyEngine::Engine::SwitchScene(int sceneNumber)
{
	m_fontInfos.clear();
	// 이 함수가 업데이트 도중에 호출되기 때문에
	// 잠시 이벤트 큐에 담아뒀다가 업데이트가 종료되면 
	// 그때 안전하게 수행된다.
	m_eventQueue.push([=]() 
	{
		assert(m_pSceneTransition != nullptr);

		// 처음엔 current scene이 없기때문에 null을 넣는다.
		m_pSceneTransition->Transit(m_scenes[m_currentLevel], m_scenes[sceneNumber],
			[=]() {
			// on completed 
			m_pActiveScene = m_scenes[sceneNumber];
			m_scenes[sceneNumber]->LoadScene();
		
			m_currentLevel = sceneNumber;
			m_pActiveScene->LateLoadScene();
			TIMER->reset();
		});
	});
}

void HyEngine::Engine::ShowLoadingScene(SceneTransition * sceneTransiion)
{
	// 여기서 activeScene을 잠시 loadingScene으로 한다.
	m_pLoadingScene->LoadScene();
	m_pActiveScene = m_pLoadingScene;
	m_pLoadingScene->LateLoadScene();
}

void HyEngine::Engine::HideLoadingScene()
{
	// Transition에서 다른 씬으로 교체하는 콜백을 호출하기 때문에
	m_pActiveScene = nullptr;
	m_pLoadingScene->Unload();
}

void HyEngine::Engine::AddScriptableData(std::wstring key, ScriptableData* data)
{
	m_scriptableDatas.insert(std::make_pair(key, data));
}

ScriptableData * HyEngine::Engine::GetScriptableData(std::wstring key)
{

	auto data =	m_scriptableDatas.find(key);
	if (data == m_scriptableDatas.end())
		return nullptr;
	return data->second;
}

void HyEngine::Engine::DrawText(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color)
{
	FontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;

	m_fontInfos.push_back(info);
}

void HyEngine::Engine::DrawTextFormat(D3DXVECTOR3 position,D3DXVECTOR3 scale, D3DCOLOR color, const TCHAR * text, int args, ...)
{
	FontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text, args);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;

	m_fontInfos.push_back(info);

}

bool HyEngine::Engine::InsertShader(std::wstring key, std::wstring path)
{
	auto& iter =  m_shaderMap.find(key);
	
	/* already exist */
	if (iter != m_shaderMap.end())
		return false;

	ID3DXEffect* shader = nullptr;
	D3DXCreateEffectFromFile(DEVICE, path.c_str(), nullptr, nullptr, 0, nullptr, &shader, nullptr);
	assert(shader);

	m_shaderMap.insert(make_pair(key, shader));
}

bool HyEngine::Engine::TryGetShader(std::wstring key,_Out_ ID3DXEffect ** ppShader)
{
	*ppShader = nullptr;

	auto& iter = m_shaderMap.find(key);

	if (iter == m_shaderMap.end())
		return false;

	*ppShader = iter->second;
	return true;
}


bool Engine::LoadShaders()
{
	InsertShader(L"GBuffer", PATH->ShadersPathW() + L"GBuffer.fx");
	InsertShader(L"PointLight", PATH->ShadersPathW() + L"PointLight.fx");
	InsertShader(L"SpotLight", PATH->ShadersPathW() + L"SpotLight.fx");
	InsertShader(L"Ambient", PATH->ShadersPathW() + L"Ambient.fx");
	InsertShader(L"DirectionalLight", PATH->ShadersPathW() + L"DirectionalLight.fx");
	InsertShader(L"DiffuseShader", PATH->ShadersPathW() + L"DiffuseShader.fx");
	return true;
}

void Engine::LoadScenes()
{
	// don't use
	assert(false);

	/*m_currentLevel = engineConfig.defaultSceneIndex;
	m_pActiveScene = engineConfig.scenes[m_currentLevel];
	m_pActiveScene->LoadScene();*/
}


void Engine::RenderDebug()
{

}

void HyEngine::Engine::RenderFont()
{
	DIRECT_SPRITE->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	for (auto& fontInfo : m_fontInfos)
	{
		DIRECT_SPRITE->SetTransform(&fontInfo.matTrans);
		DIRECT_FONT->DrawTextW(DIRECT_SPRITE, fontInfo.textBuff, lstrlen(fontInfo.textBuff), nullptr, 0, fontInfo.textColor);
	}
	

	DIRECT_SPRITE->End();
}
