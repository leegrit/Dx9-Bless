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
		void BeginEditGUI();
		void EndEditGUI();
		void InputText(std::string label, _Out_ char* result, int size);
		void InputInt(std::string label, _Out_ int* result);
		void InputFloat(std::string label, _Out_ float* result);

		void ShowEditRenderOption();
	private :
		void ApplyStyle();

	private :
		bool m_bOpen = true;

		/* EditGUI */
		ImVec2 m_editGUIPos = ImVec2(WinMaxWidth - 500, 200);
		ImVec2 m_offset = ImVec2(0, 50);
		ImVec2 m_size = ImVec2(300, 200);
		int m_guiCount = 0;
	};
}
