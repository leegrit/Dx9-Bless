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
#include "Gui.h"
#include "MeshHierarchyLoader.h"
#include "SoundManager.h"

using namespace HyEngine;

Settings::Engine Engine::sEngineSettigns ;

IMPLEMENT_SINGLETON(Engine)

// todo keyboard, mouse, timer
Engine::Engine()
	: 
	m_bLoading(false),
	m_bIsPaused(false),
	m_gameMode(EGameMode::GAME_MODE)
{
	SEND_LOG("Engine Created");
	DirectXDevice::Create();
	UIDGen::Create();
	PathManager::Create();
	SoundManager::Create();
	
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
	MeshHierarchyLoader::Clear();
	SoundManager::Destroy();
}

bool Engine::Initialize(HWND hWnd, EngineConfig engineConfig)
{
	SEND_LOG("Engine Initialize Start");
	DirectXDevice::Get()->Init(hWnd);
	m_pRenderer = Renderer::Create();
	m_pTimer->start();

	SoundManager::Get()->Initialize();

	assert(engineConfig.scenes.size() != 0);

	this->engineConfig = engineConfig;
	m_scenes = engineConfig.scenes;

	m_renderOption = RenderOptions::RenderCollider | 
					 RenderOptions::RenderLight |
					 RenderOptions::RenderNavMesh |
					 RenderOptions::RenderShadow | 
					 RenderOptions::RenderUI;

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

	if (KEYBOARD->Up(VK_TAB))
	{
		if (GetGameMode() == EGameMode::GAME_MODE)
			SetGameMode(EGameMode::EDIT_MODE);
		else
			SetGameMode(EGameMode::GAME_MODE);
		EventDispatcher::TriggerEvent(EngineEvent::ModeChanged);
	}
	if (m_pActiveScene != m_pLoadingScene)
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
	if (m_pActiveScene == nullptr) return;
	// 임시
	//if (m_pActiveScene == m_pLoadingScene) return;
	
	/* Occlusion Query */

	/*m_pRenderer->OcclusionBegin();
	m_pRenderer->OcclusionCull(m_pActiveScene);
	m_pRenderer->OcclusionEnd();*/

	m_pRenderer->RenderBegin();
	//DEVICE->SetTransform(D3DTS_PROJECTION, &m_pCamera->GetProjectionMatrix());
	//DEVICE->SetTransform(D3DTS_VIEW, &m_pCamera->GetViewMatrix());

	Gui::Get()->Update();
	if (m_pActiveScene)
	{
		m_pActiveScene->RenderScene(m_pRenderer);
		m_pActiveScene->RenderGUI();
	}
	
	Gui::Get()->Render();
	RenderFont();
	m_pRenderer->RenderEnd();
}

void HyEngine::Engine::ToggleRenderOption(DWORD renderOption)
{
	m_renderOption = m_renderOption ^ renderOption;
}

void HyEngine::Engine::SetRenderOption(DWORD renderOption, bool bActive)
{
	if (bActive)
	{
		m_renderOption = m_renderOption | renderOption;
	}
	else
	{
		DWORD temp = ~renderOption;
		m_renderOption = m_renderOption & temp;
	}
}

DWORD HyEngine::Engine::GetRenderOption() const
{
	return m_renderOption;
}

bool HyEngine::Engine::CheckRenderOption(DWORD renderOption)
{
	return m_renderOption & renderOption;
}

Scene * Engine::GetActiveScene()
{
	return m_pActiveScene;
}

void HyEngine::Engine::SetGameMode(EGameMode mode)
{
	m_gameMode = mode;
}

EGameMode HyEngine::Engine::GetGameMode() const
{
	return m_gameMode;
}

void HyEngine::Engine::SetFPS(float fps)
{
	m_fps = fps;
}

float HyEngine::Engine::GetFPS() const
{
	return m_fps;
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

void HyEngine::Engine::DrawText(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, DWORD format)
{
	FontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;
	//info.format = format;
	info.format = DT_LEFT | DT_TOP;
	RECT rect;
	SetRect(&rect, 0, 0, 1024, 768);
	info.rect = rect;
	m_fontInfos.push_back(info);
}

void HyEngine::Engine::DrawText(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, RECT rect, DWORD format)
{
	FontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;
	info.format = format;
	info.rect = rect;
	m_fontInfos.push_back(info);
}

void HyEngine::Engine::DrawText(const TCHAR * text, D3DXMATRIX mat, D3DCOLOR color)
{
	FontInfo info;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	wsprintf(info.textBuff, text);
	info.matTrans = mat;
	info.textColor = color;
	info.format = DT_LEFT | DT_TOP;
	RECT rect;
	SetRect(&rect, 0, 0, 1024, 768);
	info.rect = rect;
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
	info.format = DT_LEFT;

	m_fontInfos.push_back(info);

}

void HyEngine::Engine::DrawTextInWorld(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXCOLOR color)
{

	D3DXVECTOR3 resultPos;
	D3DXMATRIX resultMat;
	D3DXMATRIX worldMat;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;

	D3DXMATRIX viewMat = SCENE->GetSelectedCamera()->GetViewMatrix();
	D3DXMATRIX projMat = SCENE->GetSelectedCamera()->GetProjectionMatrix();

	
	//position.x -= m_size.x * 0.5f;
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, 1);
	worldMat = scaleMat * posMat;
	D3DVIEWPORT9 viewPort;
	DEVICE->GetViewport(&viewPort);

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	D3DXVec3Project(&resultPos, &D3DXVECTOR3(0, 0, 0), &viewPort, &projMat, &viewMat, &worldMat);


	FontInfo info;

	wsprintf(info.textBuff, text);
	D3DXMatrixTranslation(&posMat, resultPos.x, resultPos.y, resultPos.z);
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	info.matTrans = scaleMat * posMat;
	info.textColor = color;
	//info.format = format;
	info.format = DT_BOTTOM | DT_CENTER;
	RECT rect;
	SetRect(&rect, -612, -40, 612, 0);
	info.rect = rect;
	m_fontInfos.push_back(info);
	//ENGINE->DrawText(text, resultPos, D3DXVECTOR3(1, 1, 1), color);
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
	InsertShader(L"MeshEffect", PATH->ShadersPathW() + L"MeshEffect.fx");
	InsertShader(L"TextureEffect", PATH->ShadersPathW() + L"TextureEffect.fx");
	InsertShader(L"ShadowMap", PATH->ShadersPathW() + L"ShadowMap.fx");
	InsertShader(L"SoftShadowMapping", PATH->ShadersPathW() + L"SoftShadowMapping.fx");
	InsertShader(L"Blur", PATH->ShadersPathW() + L"Blur.fx");
	InsertShader(L"Collider", PATH->ShadersPathW() + L"Collider.fx");
	InsertShader(L"Skybox", PATH->ShadersPathW() + L"Skybox.fx");
	InsertShader(L"UIPanel", PATH->ShadersPathW() + L"UIPanel.fx");
	InsertShader(L"SkinnedMesh", PATH->ShadersPathW() + L"SkinnedMesh.fx");
	InsertShader(L"StaticMesh", PATH->ShadersPathW() + L"StaticMesh.fx");
	InsertShader(L"OcclusionQuery", PATH->ShadersPathW() + L"OcclusionQuery.fx");
	InsertShader(L"LinearFilter", PATH->ShadersPathW() + L"LinearFilter.fx");
	InsertShader(L"Terrain", PATH->ShadersPathW() + L"Terrain.fx");
	InsertShader(L"Texture", PATH->ShadersPathW() + L"Texture.fx");
	InsertShader(L"ProgressBar", PATH->ShadersPathW() + L"ProgressBar.fx");
	InsertShader(L"FadeInOut", PATH->ShadersPathW() + L"FadeInOut.fx");
	InsertShader(L"TargetingUI", PATH->ShadersPathW() + L"TargetingUI.fx");
	InsertShader(L"LUTFilter", PATH->ShadersPathW() + L"LUTFilter.fx");
	InsertShader(L"DeferredBlend", PATH->ShadersPathW() + L"DeferredBlend.fx");
	InsertShader(L"ShieldEffect", PATH->ShadersPathW() + L"ShieldEffect.fx");
	InsertShader(L"PRBuffer", PATH->ShadersPathW() + L"PRBuffer.fx");
	InsertShader(L"RimLight", PATH->ShadersPathW() + L"RimLight.fx");
	InsertShader(L"Brightness", PATH->ShadersPathW() + L"Brightness.fx");
	InsertShader(L"Bloom", PATH->ShadersPathW() + L"Bloom.fx");
	InsertShader(L"PostRender", PATH->ShadersPathW() + L"PostRender.fx");
	InsertShader(L"DebugMRT", PATH->ShadersPathW() + L"DebugMRT.fx");
	InsertShader(L"FontTexture", PATH->ShadersPathW() + L"FontTexture.fx");
	InsertShader(L"SkillProgressUI", PATH->ShadersPathW() + L"SkillProgressUI.fx");
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

	/*DWORD old;
	DEVICE->GetRenderState(D3DRS_ZENABLE, &old);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);*/

	for (auto& fontInfo : m_fontInfos)
	{
		DIRECT_SPRITE->SetTransform(&fontInfo.matTrans);
		/*RECT rect;
		SetRect(&rect, -500, -40, 500, 0);
*/
		DIRECT_FONT->DrawTextW(DIRECT_SPRITE, fontInfo.textBuff, lstrlen(fontInfo.textBuff), &fontInfo.rect, fontInfo.format/*DT_CENTER | DT_BOTTOM*/, fontInfo.textColor);
	}
	//DEVICE->SetRenderState(D3DRS_ZENABLE, old);

	DIRECT_SPRITE->End();
}
