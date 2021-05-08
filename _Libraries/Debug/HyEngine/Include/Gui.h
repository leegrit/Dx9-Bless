#pragma once

namespace HyEngine
{
	class Gui
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

	private :
		void ApplyStyle();
	};
}

