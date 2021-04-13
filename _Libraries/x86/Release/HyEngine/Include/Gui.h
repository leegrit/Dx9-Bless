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

		/* Show GUI */
	public :
		void ShowDemoGUI();
		void ShowFPS();

	private :
		void ApplyStyle();
	};
}
