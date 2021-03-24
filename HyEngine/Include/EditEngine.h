#pragma once
#include "GameObjectData.h"

namespace Editor
{
	class EditEngine
	{
		DECLARE_SINGLETON(EditEngine)
	private :
		EditEngine();
		~EditEngine();
	public :
		//static EditEngine* Create();
		static void Release(EditEngine** engine);
		
		void Render();
		void Update();

		void GetBackBuffer(_Out_ IDirect3DSurface9 ** ppSurface);
		Scene* GetScene();

		void SelectObject(int index);
		void InsertGameData(class  GameObjectData* data);
		void InsertMeshData(class MeshData* data);
		void ActiveObject();
		void InactiveObject();
		// 이 함수는 해당 값을 대입하는게 아니라 그만큼 수정하는 함수
		void AdjustEditCameraPos(float xPos, float yPos, float zPos);
		void AdjustEditCameraRot(float xRot, float yRot, float zRot);
		void SetSolidMode();
		void SetWireFrameMode();

		inline IO::Mouse* GetMouse() const { return m_pMouse; }
		inline IO::Keyboard* GetKeyboard() const { return m_pKeyboard; }
		inline Timer* GetTimer() const { return m_pTimer; }
	private :

		bool Initialize();
		bool Load();
		HRESULT EnsureHWND();
		void DestroyResources();

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

