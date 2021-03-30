#pragma once
#include "GameObjectData.h"

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
		bool PickGameObject(float xMousePos, float yMousePos, _Out_ int * resultIndex);


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

		/* For DynamicMesh */
		int GetAnimationCount();
		void GetAnimationName(_Out_ class AnimNameData* outString, int index);
		void SetAnimation(int index);
		
		//////////////////////////////////////////////////////////////////////////
		// GETTER
		//////////////////////////////////////////////////////////////////////////
	public :
		inline IO::Mouse* GetMouse() const { return m_pMouse; }
		inline IO::Keyboard* GetKeyboard() const { return m_pKeyboard; }
		inline Timer* GetTimer() const { return m_pTimer; }
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
	};

}
static LRESULT CALLBACK EditWndProc(HWND, UINT, WPARAM, LPARAM);

