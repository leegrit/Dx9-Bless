#include "StandardEngineFramework.h"
#include "Gui.h"

using namespace HyEngine;

IMPLEMENT_SINGLETON(Gui)

HyEngine::Gui::Gui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();


	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(DEVICE);

	ApplyStyle();
}

HyEngine::Gui::~Gui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT HyEngine::Gui::MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam);
}

void HyEngine::Gui::Resize()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
}

void HyEngine::Gui::Update()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void HyEngine::Gui::Render()
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());


}

void HyEngine::Gui::ShowDemoGUI()
{
	static bool temp = true;
	ImGui::ShowDemoWindow(&temp);
}

void HyEngine::Gui::ShowFPS()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ 100 , 15 });
	ImGui::SetNextWindowSize(ImVec2(400, 100));
	ImGui::Begin
	(
		"FPS",
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		string frame = "FPS : " + to_string(ENGINE->GetFPS());
		ImGui::Text(frame.c_str());
	}
	ImGui::End();
}

void HyEngine::Gui::ShowGameMode()
{
	string modeName;

	switch (ENGINE->GetGameMode())
	{
	case EGameMode::EDIT_MODE :
		modeName = "EDIT_MODE";
		break;
	case EGameMode::GAME_MODE :
		modeName = "GAME_MODE";
		break;
	default :
		assert(false);
		break;
	}
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ WinMaxWidth - WinMaxWidth * 0.5f, 15 });
	ImGui::SetNextWindowSize(ImVec2(400, 100));
	ImGui::Begin
	(
		"MODE",
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		ImGui::Text(modeName.c_str());
	}
	ImGui::End();
}

void HyEngine::Gui::ShowTextInput(char * result, int size, float xPos, float yPos)
{
	if (ENGINE->GetGameMode() == EGameMode::GAME_MODE) return;
	ImGui::SetNextWindowPos({ xPos, yPos });
	ImGui::SetNextWindowSize(ImVec2(300, 200));
	ImGui::Begin
	(
		"TextInputWindow",
		&m_bOpen,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_MenuBar
	);
	{
		ImGui::InputText("Text Input", result, size);
	}
	ImGui::End();
}

void HyEngine::Gui::BeginEditGUI()
{
	m_guiCount = 0;
}

void HyEngine::Gui::EndEditGUI()
{

}

void HyEngine::Gui::InputText(std::string label, _Out_ char * result, int size)
{
	static bool bInputTextOpen = true;
	ImVec2 offset = { m_offset.x * m_guiCount, m_offset.y * m_guiCount };
	ImVec2 pos = { m_editGUIPos.x + offset.x, m_editGUIPos.y + offset.y };

	m_guiCount++;
	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(m_size);
	ImGui::Begin
	(
		"InputText",
		&bInputTextOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		ImGui::InputText(label.c_str(), result, size);
	}
	ImGui::End();
}

void HyEngine::Gui::InputInt(std::string label,_Out_ int * result)
{
	static bool bInputIntOpen = true;
	ImVec2 offset = { m_offset.x * m_guiCount, m_offset.y * m_guiCount };
	ImVec2 pos = { m_editGUIPos.x + offset.x, m_editGUIPos.y + offset.y };

	m_guiCount++;
	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(m_size);
	ImGui::Begin
	(
		"InputInt",
		&bInputIntOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		ImGui::InputInt(label.c_str(), result);
	}
	ImGui::End();
}

void HyEngine::Gui::InputFloat(std::string label, _Out_ float * result)
{
	static bool bInputFloatOpen = true;
	ImVec2 offset = { m_offset.x * m_guiCount, m_offset.y * m_guiCount };
	ImVec2 pos = { m_editGUIPos.x + offset.x, m_editGUIPos.y + offset.y };

	m_guiCount++;
	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(m_size);
	ImGui::Begin
	(
		"InputFloat",
		&bInputFloatOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		ImGui::InputFloat(label.c_str(), result);
	}
	ImGui::End();
}

void HyEngine::Gui::ShowEditRenderOption()
{
	static bool bShowEditRenderOption = true;

	ImGui::SetNextWindowPos({100, 300});
	ImGui::Begin
	(
		"RenderOption",
		&bShowEditRenderOption//,
		//ImGuiWindowFlags_NoBackground |
		//ImGuiWindowFlags_NoTitleBar |
		//ImGuiWindowFlags_NoResize |
		//ImGuiWindowFlags_NoMove
	);
	{
		bool bRenderCollider = ENGINE->CheckRenderOption(RenderOptions::RenderCollider);
		ImGui::Checkbox("RenderCollider", &bRenderCollider);
		ENGINE->SetRenderOption(RenderOptions::RenderCollider, bRenderCollider);

		bool bRenderNavMesh = ENGINE->CheckRenderOption(RenderOptions::RenderNavMesh);
		ImGui::Checkbox("RenderNavMesh", &bRenderNavMesh);
		ENGINE->SetRenderOption(RenderOptions::RenderNavMesh, bRenderNavMesh);

		bool bRenderLight = ENGINE->CheckRenderOption(RenderOptions::RenderLight);
		ImGui::Checkbox("RenderLight", &bRenderLight);
		ENGINE->SetRenderOption(RenderOptions::RenderLight, bRenderLight);

		bool bRenderShadow = ENGINE->CheckRenderOption(RenderOptions::RenderShadow);
		ImGui::Checkbox("RenderShadow", &bRenderShadow);
		ENGINE->SetRenderOption(RenderOptions::RenderShadow, bRenderShadow);

		bool bRenderUI = ENGINE->CheckRenderOption(RenderOptions::RenderUI);
		ImGui::Checkbox("RenderUI", &bRenderUI);
		ENGINE->SetRenderOption(RenderOptions::RenderUI, bRenderUI);

	}
	ImGui::End();
}

void HyEngine::Gui::ApplyStyle()
{
	ImGui::GetIO().ConfigWindowsResizeFromEdges = true;
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();


	float fontSize = 15.0f;
	float roundness = 2.0f;
	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	//ImVec4 text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
	ImVec4 text = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 backgroundVeryDark = ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
	ImVec4 backgroundDark = ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
	ImVec4 backgroundMedium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
	ImVec4 backgroundLight = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
	ImVec4 highlightBlue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
	ImVec4 highlightBlueHovered = ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
	ImVec4 highlightBlueActive = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
	ImVec4 barBackground = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
	ImVec4 bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
	ImVec4 barHovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
	ImVec4 barActive = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

	// Spatial
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = ImVec2(5, 5);
	style.ItemSpacing = ImVec2(6, 5);
	style.Alpha = 1.0f;
	style.WindowRounding = roundness;
	style.FrameRounding = roundness;
	style.PopupRounding = roundness;
	style.GrabRounding = roundness;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = roundness;

	// Colors
	style.Colors[ImGuiCol_Text] = text;
	style.Colors[ImGuiCol_WindowBg] = backgroundDark;
	style.Colors[ImGuiCol_Border] = black;
	style.Colors[ImGuiCol_FrameBg] = bar;
	style.Colors[ImGuiCol_FrameBgHovered] = highlightBlue;
	style.Colors[ImGuiCol_FrameBgActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_TitleBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_TitleBgActive] = bar;
	style.Colors[ImGuiCol_MenuBarBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_ScrollbarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarGrab] = bar;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = barHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = barActive;
	style.Colors[ImGuiCol_CheckMark] = white;
	style.Colors[ImGuiCol_SliderGrab] = bar;
	style.Colors[ImGuiCol_SliderGrabActive] = barActive;
	style.Colors[ImGuiCol_Button] = barActive;
	style.Colors[ImGuiCol_ButtonHovered] = highlightBlue;
	style.Colors[ImGuiCol_ButtonActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Header] = highlightBlue; // selected items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderHovered] = highlightBlueHovered; // hovered items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Separator] = backgroundLight;
	style.Colors[ImGuiCol_ResizeGrip] = backgroundMedium;
	style.Colors[ImGuiCol_ResizeGripHovered] = highlightBlue;
	style.Colors[ImGuiCol_ResizeGripActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = highlightBlue; // Also used for progress bar
	style.Colors[ImGuiCol_PlotHistogramHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = highlightBlue;
	style.Colors[ImGuiCol_PopupBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_DragDropTarget] = backgroundLight;
}
