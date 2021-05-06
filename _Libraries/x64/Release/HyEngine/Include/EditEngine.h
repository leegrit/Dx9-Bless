#pragma once
#include "GameObjectData.h"

struct EditFontInfo
{
	TCHAR textBuff[256];
	D3DXMATRIX matTrans;
	D3DCOLOR textColor;
};
namespace HyEngine
{
	class EditEngine
	{
		DECLARE_SINGLETON(EditEngine)

		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	private :
		EditEngine();
		~EditEngine();
	public :
		void Render();
		void Update();
	private: /* For.Logger */
		void InitLoggingService();
	
		/* For Shader */
	private :
		void LoadShaders();
	public:
		bool InsertShader(std::wstring key, std::wstring path);
		bool TryGetShader(std::wstring key, _Out_ ID3DXEffect** ppShader);


	private : /* For Font */
		void RenderFont();
	public:
		void DrawText(const TCHAR* text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color);
		void DrawText(const TCHAR* text, D3DXMATRIX mat, D3DCOLOR color);
		void DrawTextFormat(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DCOLOR color, const TCHAR* text, int args, ...);
		void DrawTextInWorld(const TCHAR * text, D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXCOLOR color);

		//////////////////////////////////////////////////////////////////////////
		// EXPORTS
		//////////////////////////////////////////////////////////////////////////
	public :

		/* For Render */
		void GetBackBuffer(_Out_ IDirect3DSurface9 ** ppSurface);
		Scene* GetScene();

		/* For Object */
		void SelectObject(int index);
		GameObject* GetSelectedObject();
		void ActiveObject();
		void InactiveObject();
		void AddGameObject(int index);
		void AddPawn(int index);
		void AddNavMesh(int index);
		void RemoveGameObject(int index);
		bool PickGameObject(float xMousePos, float yMousePos, _Out_ int * resultIndex, _Out_ VectorData* pickedPos);


		/* For Data */
		void InsertGameData(class  GameObjectData* data);
		void InsertMeshData(class MeshData* data);
		void InsertCellData(class CellData* data, int cellEditMode);
		
		/* For Camera */
		// 이 함수는 해당 값을 대입하는게 아니라 그만큼 수정하는 함수
		void AdjustEditCameraPos(float xPos, float yPos, float zPos);
		void AdjustEditCameraRot(float xRot, float yRot, float zRot);
		void GetEditCameraPos(_Out_ VectorData* position);
		void GetEditCameraRot(_Out_ VectorData* rotation);
		void SetEditCameraPos(float xPos, float yPos, float zPos);
		void SetEditCameraRot(float xRot, float yRot, float zRot);
		// 현재 선택된 mesh를 바라볼 수 있도록 이동하는 함수
		// x mesh만 가능하다.
		void TranslateToMesh();

		/* For RenderState */
		void SetSolidMode();
		void SetWireFrameMode();

		/* For NavMesh */
		bool PickNavMesh(float xMousePos, float yMousePos, int cellOption, _Out_ VectorData* pickedPos);
		void AddCell(CellData* cellData);
		void RemoveNavPrim(int navPrimIndex);

		/* For DynamicMesh */
		int GetAnimationCount();
		void GetAnimationName(_Out_ class AnimNameData* outString, int index);
		void SetAnimation(int index);

		/* For Terrain */
		void CreateTerrain(unsigned int editID);
		void InsertTerrainData(class TerrainData* data);

		/* For Light */
		void CreateLight(int editID);
		void InsertLightData(class LightData* data);

		/* For Effect */
		void CreateMeshEffect(int editID);
		void CreateTextureEffect(int editID);
		void InsertEffectData(class EffectData * data);

		/* For UIPanel */
		void CreateUIPanel(int editID);
		void InsertUIData(class UIData * data);

		/* For Font */
		void CreateEditFont(int editID);


		//////////////////////////////////////////////////////////////////////////
		// GETTER
		//////////////////////////////////////////////////////////////////////////
	public :
		inline IO::Mouse* GetMouse() const { return m_pMouse; }
		inline IO::Keyboard* GetKeyboard() const { return m_pKeyboard; }
		inline Timer* GetTimer() const { return m_pTimer; }
		inline Renderer* GetRenderer() const;
	private :

		bool Initialize();
		bool Load();
		HRESULT EnsureHWND();
		void DestroyResources();


		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		class Renderer * m_pRenderer = nullptr;
		class Timer* m_pTimer = nullptr;
		class IO::Keyboard *m_pKeyboard;
		class IO::Mouse *m_pMouse;
		class EditScene* m_pEditScene = nullptr;
		HWND m_hWnd = NULL;
		UINT m_width;
		UINT m_height;
		bool m_bLoading;
		bool m_bGameMode = false;
		GameObject* m_pSelectedObject = nullptr;

		/* For Font */
		std::vector<EditFontInfo> m_fontInfos;

		/* For Shader */
		std::unordered_map<std::wstring, ID3DXEffect*> m_shaderMap;
	};

}
static LRESULT CALLBACK EditWndProc(HWND, UINT, WPARAM, LPARAM);

