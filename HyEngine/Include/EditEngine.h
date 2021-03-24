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
		class Scene* m_pEditScene = nullptr;
		HWND m_hWnd = NULL;
		UINT m_width;
		UINT m_height;
		bool m_bLoading;

		GameObject* m_pSelectedObject = nullptr;
	};

}
static LRESULT CALLBACK EditWndProc(HWND, UINT, WPARAM, LPARAM);

