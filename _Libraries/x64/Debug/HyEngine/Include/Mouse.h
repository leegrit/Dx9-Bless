#pragma once


#define MAX_INPUT_MOUSE 8

namespace HyEngine
{
	namespace IO
	{
		class ENGINE_DLL Mouse
		{
		public:
			Mouse();
			~Mouse();

			void SetHandle(HWND handle)
			{
				this->handle = handle;
			}

			void Update();

			LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);

			D3DXVECTOR3 GetPosition() { return position; }
			void SetPosition(D3DXVECTOR3 pos);

			bool Down(DWORD button)
			{
				if (!bMouseCaptured) return false;
				return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
			}

			bool Up(DWORD button)
			{
				if (!bMouseCaptured) return false;
				return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
			}

			bool Press(DWORD button)
			{
				if (!bMouseCaptured) return false;
				return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS;
			}

			D3DXVECTOR3 GetMoveValue()
			{
				return wheelMoveValue;
			}

			inline bool IsCaptured() const { return bMouseCaptured; }
			inline void CaptureMouse(bool bDoCapture)
			{
				bMouseCaptured = bDoCapture;
			}

		private:


			HWND handle;
			D3DXVECTOR3 position; //마우스 위치

			byte buttonStatus[MAX_INPUT_MOUSE];
			byte buttonOldStatus[MAX_INPUT_MOUSE];
			byte buttonMap[MAX_INPUT_MOUSE];

			D3DXVECTOR3 wheelStatus;
			D3DXVECTOR3 wheelOldStatus;
			D3DXVECTOR3 wheelMoveValue;

			DWORD timeDblClk;
			DWORD startDblClk[MAX_INPUT_MOUSE];
			int buttonCount[MAX_INPUT_MOUSE];


			bool bMouseCaptured = true;
			enum
			{
				MOUSE_ROTATION_NONE = 0,
				MOUSE_ROTATION_LEFT,
				MOUSE_ROTATION_RIGHT
			};

			enum
			{
				BUTTON_INPUT_STATUS_NONE = 0,
				BUTTON_INPUT_STATUS_DOWN,
				BUTTON_INPUT_STATUS_UP,
				BUTTON_INPUT_STATUS_PRESS,
				BUTTON_INPUT_STATUS_DBLCLK
			};
		};
	}
}