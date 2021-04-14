#pragma once

namespace HyEngine
{
	class ENGINE_DLL Gui
	{
		DECLARE_SINGLETON(Gui);
	private :
		Gui();
		~Gui();

	public :
		LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
		void Resize();

		void Update();
		void Render();

		//////////////////////////////////////////////////////////////////////////
		// SHOW GUI
		//////////////////////////////////////////////////////////////////////////
	public :
		void ShowDemoGUI();
		void ShowFPS();
		void ShowGameMode();
		void ShowEditGuide();
		void ShowTextInput(_Out_ char* result, int size, float xPos, float yPos);


		//////////////////////////////////////////////////////////////////////////
		// FOR IMGUI
		//////////////////////////////////////////////////////////////////////////
	public :


	private :
		void ApplyStyle();

	private :
		bool m_bOpen = true;
	};
}
