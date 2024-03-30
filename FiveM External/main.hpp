#include <iostream>
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "include.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <tchar.h>
#include <intrin.h>
#include "byte_array.h"
#include "Fonts.h"
#include "skStr.h"
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
RECT ProcessRect = { NULL };
HWND attach_window;
HWND fuck_hwnd;
GLFWwindow* menu_window;
int menu_width = 155;
int menu_height = 155;
bool menu_visible = true;
static void CallBackError(int error, const char* description) {}

int my_image_width;
int my_image_height;
GLuint my_image_texture;
//Replace "../../MyImage01.jpg" with your image path. Example: "C://Logo.png"
bool Result;

//namespace fonts
ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

void tema() {
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	
	ImGui::StyleColorsDark();


	// Load Fonts
	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
	bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
	logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

	tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
	tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

	subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

	// Our state
	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

	style.Colors[ImGuiCol_Border] = ImColor(255,10,10,255);
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1, 1, 1, .8); // grey
	//colors[ImGuiCol_Text] = ImVec4(.6f, .6f, .6f, 1.00f); // grey
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	colors[ImGuiCol_WindowBg] = { 0.07f, 0.07f, 0.07f, 1.0f };

	colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	colors[ImGuiCol_Border] = ImVec4(0.10f, 0.10f, 0.10f, 1.f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.10f, 0.10f, 0.10f, 1);
	colors[ImGuiCol_FrameBg] = { 0.149, 0.149, 0.149, 1 };
	colors[ImGuiCol_FrameBgHovered] = ImVec4(.6f, .6f, .6f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.25f, 0.30f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.9, 0, 0.1f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.9, 0, 0.1f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.9, 0, 0.1f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	colors[ImGuiCol_ScrollbarGrab] = { 0.5f, 0.00f, 0.7f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.5f, 0.00f, 0.7f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5f, 0.00f, 0.7f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
	//colors[ImGuiCol_CheckMark] = { 1, 1, 1, .6 };
	colors[ImGuiCol_CheckMark] = { 0.9, 0, 0.1f, 1.00f };
	colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 0.8f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.); //multicombo, combo selected item color.
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	//colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	//colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	//colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	//colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

	colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.10f, 0.5f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.1f, 0.1f, 0.1f, 1);
	colors[ImGuiCol_TabActive] = ImVec4(0.10f, 0.10f, 0.10f, 1);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 1);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.10f, 0.10f, 0.10f, 1);


}

static void HelpMarker(const char* desc) {
	ImGui::TextDisabled(skCrypt("(?)"));
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

static HWND get_process_wnd(uint32_t pid) {
	std::pair<HWND, uint32_t> params = { 0, pid };

	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}

namespace fonts {
	ImFont* medium;
	ImFont* semibold;
	ImFont* logo;
}

void setupWindow() {

	glfwSetErrorCallback(CallBackError);
	if (!glfwInit()) {
		return;
	}

	//GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	//if (!monitor) {
	//	return;
	//}

	if (attach_window) {
		GetClientRect(attach_window, &ProcessRect);
		POINT xy;
		ClientToScreen(attach_window, &xy);
		ProcessRect.left = xy.x;
		ProcessRect.top = xy.y;

		menu_width = ProcessRect.right;
		menu_height = ProcessRect.bottom;
	}

	//menu_width = glfwGetVideoMode(monitor)->width;
	//menu_height = glfwGetVideoMode(monitor)->height;

	glfwWindowHint(GLFW_FLOATING, true);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

	menu_window = glfwCreateWindow(menu_width, menu_height, skCrypt("FiveM Overlay"), NULL, NULL);
	if (menu_window == NULL) {
		return;
	}
	fuck_hwnd = glfwGetWin32Window(menu_window);
	//ShowWindow(fuck_hwnd, SW_HIDE);
	SetWindowLong(fuck_hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	glfwSetWindowAttrib(menu_window, GLFW_DECORATED, false);
	glfwSetWindowAttrib(menu_window, GLFW_MOUSE_PASSTHROUGH, true);
	glfwSetWindowMonitor(menu_window, NULL, 0, 0, menu_width, menu_height + 1, 0);

	glfwMakeContextCurrent(menu_window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		return;
	}

	my_image_texture = 0;
	//Replace "../../MyImage01.jpg" with your image path. Example: "C://Logo.png"
	Result = LoadTextureFromFile("C:\\logo.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(Result);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(menu_window, true);
	ImGui_ImplOpenGL3_Init(skCrypt("#version 130"));

	// Load Fonts
	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	fonts::medium = io.Fonts->AddFontFromMemoryTTF(InterMedium, sizeof(InterMedium), 15.0f, &font_config, ranges);
	fonts::semibold = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 17.0f, &font_config, ranges);

	fonts::logo = io.Fonts->AddFontFromMemoryTTF(catrine_logo, sizeof(catrine_logo), 17.0f, &font_config, ranges);

}

void cleanupWindow() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(menu_window);
	glfwTerminate();
}

void handleKeyPresses() {
	HWND hwnd_active = GetForegroundWindow();

	if (hwnd_active != attach_window && hwnd_active != fuck_hwnd) {
		ShowWindow(fuck_hwnd, SW_HIDE);
	}
	else {
		ShowWindow(fuck_hwnd, SW_SHOW);
		if (GetAsyncKeyState(bind_menuVK) & 1) {
			menu_visible = !menu_visible;
			glfwSetWindowAttrib(menu_window, GLFW_MOUSE_PASSTHROUGH, !menu_visible);
		}
	}
}