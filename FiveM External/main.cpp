#include "main.hpp"
#include "include.h"
#include "esp.hpp"
#include "aimbot.hpp"
#include "memory.h"
#include "offsets.h"
#include "exploit.h"
#include "xor.hpp"
#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "skStr.h"
#include <stdio.h>
#include <urlmon.h>
#include "color.hpp"
#include "colors.hpp"
#include "user_interface.h"
#include "imgui/imgui_impl_win32.h"
#include "trigger.hpp"
#include "elements.h"
#include <thread>
#include <chrono>
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;

auto name = skCrypt("zeskontop");
auto ownerid = skCrypt("utaqBe5OEv");
auto secret = skCrypt("6022db9e27001d5bb02970952f9dbd001c114a188bee10a2e6fed800187574bf");
auto version = skCrypt("1.0");

auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());



bool visual = true;
bool aimbot = true;
enum heads {
	rage, triggerbot, antiaim, visuals, settings, friendlist
};

enum sub_heads {
	general, accuracy, exploits, _general, advanced
};


void panel();



bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {

	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}


void FovAimbot() {
	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	auto draw = ImGui::GetBackgroundDrawList();
	draw->AddCircle(ImVec2(screen_x / 2, screen_y / 2), aimbot_fov_value, IM_COL32(233, 232, 232, 255), fov_segments, 2.0f);
}



void GPlayerList() {
	uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
	uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);
	for (int i = 0; i < 256; i++) {
		if (PedList) {
			uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
			if (Ped) {
				if (localplayer != 0) {
					if (Ped != localplayer) {

						player_contry[i] = Ped;

					}
				}
			}
		}
	}
}

void PlayerList() {
	GPlayerList();
	for (int i = 0; i < 256; i++) {
		if (player_contry[i] != 0) {
			string layer = std::to_string(i);
			if (player_friend[i] == 0) {
				if (ImGui::Button((skCrypt("Add Friend ID: ").decrypt() + layer).c_str(), {199, 22})) {
					player_friend[i] = player_contry[i];
				}
			}
			else {
				if (ImGui::Button((skCrypt("Rem Friend ID: ").decrypt() + layer).c_str(), {199, 22})) {
					player_friend[i] = 0;
				}
			}
		}
	}
}


void loginpanel();

int valueI;
bool the_bool;

bool god;
bool nspeed;
bool nrec;
bool nreload;
bool npread;
bool VehSp;
bool VehBrk;
bool VehGod;
int tabb = 0;

const char* menu_bind[] = { ("F4"), ("F8"), ("Delete"), ("Insert") };
const char* aimbot_bind[] = { ("Right Button") ,("Left Button") , ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
const char* trigger_bind[] = { ("Right Button") ,("Left Button"), ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
static int selected = 0;
static int sub_selected = 0;

static bool bullying = false;
static bool bullythosemfs = false;
static bool stopbullythemyoushitters = false;
static bool stop = false;
static bool niggas = false;
static bool hihihi = false;
static bool bro = false;
static int sliderinc = 0;
//static int combo = 0;
const char* hitbox_items[] = { "Head", "Neck", "Pelvis", "Right Hand", "Left Hand", "Right Foot", "Left Foot" };
static float color[4] = { 1.f, 1.f, 1.f, 1.f };


static heads tab{ rage };
static sub_heads subtab{ general };

const char* tab_name = tab == rage ? "Ragebot" : tab == antiaim ? "Anti-aim" : tab == visuals ? "Visuals" : tab == settings ? "Settings" : tab == triggerbot ? "Skins" : tab == friendlist ? "Configs" : 0;
const char* tab_icon = tab == rage ? "B" : tab == antiaim ? "C" : tab == visuals ? "D" : tab == settings ? "E" : tab == triggerbot ? "F" : tab == friendlist ? "G" : 0;
void Render() {

	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();



	if (bind_menu == 0) { bind_menuVK = VK_F4; }
	else if (bind_menu == 1) { bind_menuVK = VK_F8; }
	else if (bind_menu == 2) { bind_menuVK = VK_DELETE; }
	else if (bind_menu == 3) { bind_menuVK = VK_INSERT; }

	__try {
		if (aimbot_fov) { FovAimbot(); }

		if (esp_on) { DrawEsp(); }

		if (aimbot_on) { bindaimbot(); Aimbot(); }

		if (trigger_on) {
			bindtrigger();
			if (trigger_type == 0 || trigger_type == 1) {
				RageTriggerbot();
			}
			else if (trigger_type == 2) {
				LegitTriggerbot();
			}
		}

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_norecoil) { Weapons::NoRecoil(true); nrec = true; }
		else { if (nrec) { Weapons::NoRecoil(false); }nrec = false; }


		if (ex_noreaload) { Weapons::NoReaload(true); nreload = true; }
		else { if (nreload) { Weapons::NoReaload(false); }nreload = false; }

		if (ex_nospread) { Weapons::NoSpread(true); npread = true; }
		else { if (npread) { Weapons::NoSpread(false); }npread = false; }

		if (ex_godmode) { Player::Godmode(true); god = true; }
		else { if (god) { Player::Godmode(false); }god = false; }

		if (ex_semigodmode) {
			if (Player::GetHealth() <= 200) {
				Player::SetHealth(Player::GetMaxHealth());
			}
		}

		if (ex_vehicleaceleration) { Vehicle::VehicleAceleration(true, ex_vehicleaceleration_value); VehSp = true; }
		else { if (VehSp) { Vehicle::VehicleAceleration(false, ex_vehicleaceleration_value); }VehSp = false; }

		if (ex_vehiclebreak) { Vehicle::VehicleBrakeForce(true, ex_vehiclebreak_value); VehBrk = true; }
		else { if (VehBrk) { Vehicle::VehicleBrakeForce(false, ex_vehiclebreak_value); }VehBrk = false; }


		if (ex_vehiclegodmode) { Vehicle::GodModeVehicle(true); VehGod = true; }
		else { if (VehGod) { Vehicle::GodModeVehicle(false); }VehGod = false; }

	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}


	if (menu_visible) {

		ImGui::SetNextWindowBgAlpha(0.95f);
		ImGui::SetNextWindowSize(ImVec2(765, 425));

		ImGui::Begin(skCrypt("ActiveBypass"), nullptr, ImGuiWindowFlags_NoDecoration);

		auto draw = ImGui::GetWindowDrawList();

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		draw->AddText(fonts::semibold, 17.0f, ImVec2(pos.x + 25, pos.y + 23), ImColor(255, 255, 255), skCrypt(" FiveM").decrypt());

		ImGui::SetCursorPos({ 300, 23 });
		ImGui::BeginGroup(); {
			if (elements::tab(skCrypt("Aimbot"), tab == rage)) tab = rage;
			ImGui::SameLine();
			if (elements::tab(skCrypt("Visuals"), tab == visuals)) tab = visuals;
			ImGui::SameLine();
			if (elements::tab(skCrypt("TriggerBot"), tab == triggerbot)) tab = triggerbot;
			ImGui::SameLine();
			if (elements::tab(skCrypt("Exploits"), tab == antiaim)) tab = antiaim;
			ImGui::SameLine();
			if (elements::tab(skCrypt("Friend-List"), tab == friendlist)) tab = friendlist;
			ImGui::SameLine();
			if (elements::tab(skCrypt("Settings"), tab == settings)) tab = settings;
		}
		ImGui::EndGroup();

		switch (tab) {
		case rage:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Aimbot"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("##container"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Checkbox(skCrypt("Aimbot"), &aimbot_on);
				ImGui::Checkbox(skCrypt("Show Fov"), &aimbot_fov);
				ImGui::Checkbox(skCrypt("Target NPCs"), &TargetNpcs);
			}
			ImGui::EndChild();

			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 285, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Settings"));

			ImGui::SetCursorPos({ 285, 85 });
			ImGui::BeginChild(skCrypt("##container1"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Combo(skCrypt("Aimbot Bone"), &aimbot_bone, hitbox_items, IM_ARRAYSIZE(hitbox_items));
				ImGui::SliderFloat(skCrypt("Aimbot Smoothing"), &aimbot_smooth, 0.f, 50.f, "% .2f");
				ImGui::SliderFloat(skCrypt("Aimbot Distance"), &aimbot_max_distance, 20.f, 500.f, "% .2f");
				ImGui::SliderFloat(skCrypt("Aimbot FOV"), &aimbot_fov_value, 20.f, 400.f, "% .2f");
				ImGui::SliderInt(skCrypt("Fov Segments"), &fov_segments, 1, 50);
			}
			ImGui::EndChild();
			break;
		case triggerbot:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("TriggerBot"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("##container"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Checkbox(skCrypt("TriggerBot"), &trigger_on);
				ImGui::Checkbox(skCrypt("TriggerBot FOV"), &trigger_fov);
			}
			ImGui::EndChild();

			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 285, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Settings"));

			ImGui::SetCursorPos({ 285, 85 });
			ImGui::BeginChild(skCrypt("##container1"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::SliderFloat(skCrypt("TriggerBot FOV Value"), &trigger_fov_value, 0.f, 50.f, "% .2f");
				ImGui::SliderFloat(skCrypt("TriggerBot Distance"), &aimbot_max_distance, 20.f, 500.f, "% .2f");
			}
			ImGui::EndChild();
			break;
		case visuals:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Visuals"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("##container"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Checkbox(XorStr("Box").c_str(), &esp_box);

				ImGui::Checkbox(XorStr("Box Corner").c_str(), &esp_corner);

				ImGui::Checkbox(XorStr("Skeleton").c_str(), &esp_skeletons);

				ImGui::Checkbox(XorStr("Distance").c_str(), &esp_showdistance);

				ImGui::Checkbox(XorStr("Health Text").c_str(), &esp_hptext);

				ImGui::Checkbox(XorStr("Lines").c_str(), &esp_lines);

				ImGui::Checkbox(XorStr("Draw NPCS").c_str(), &esp_drawnpcs);

				ImGui::Checkbox(XorStr("Filled Box").c_str(), &filled_box);

				ImGui::Checkbox(XorStr("Hp Bar").c_str(), &esp_hpbar);

				ImGui::Checkbox(XorStr("Head").c_str(), &esp_head);

				ImGui::Checkbox(XorStr("Show ID").c_str(), &esp_showid);

				ImGui::SliderFloat(XorStr("Esp Distance").c_str(), &esp_max_distance, 20, 500, "% .2f");
			}
			ImGui::EndChild();

			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 285, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Settings"));

			ImGui::SetCursorPos({ 285, 85 });
			ImGui::BeginChild(skCrypt("##container1"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::ColorEdit4(XorStr("Box Color").c_str(), Temp::Box, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPBox.Value.x = Temp::Box[0]; Colors::ESPBox.Value.y = Temp::Box[1]; Colors::ESPBox.Value.z = Temp::Box[2]; Colors::ESPBox.Value.w = Temp::Box[3];

				ImGui::ColorEdit4(XorStr("Box Corner Color").c_str(), Temp::Corner, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPCorner.Value.x = Temp::Corner[0]; Colors::ESPCorner.Value.y = Temp::Corner[1]; Colors::ESPCorner.Value.z = Temp::Corner[2]; Colors::ESPCorner.Value.w = Temp::Corner[3];

				ImGui::ColorEdit4(XorStr("Skeleton Color").c_str(), Temp::Skeleton, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPSkeleton.Value.x = Temp::Skeleton[0]; Colors::ESPSkeleton.Value.y = Temp::Skeleton[1]; Colors::ESPSkeleton.Value.z = Temp::Skeleton[2]; Colors::ESPSkeleton.Value.w = Temp::Skeleton[3];

				ImGui::ColorEdit4(XorStr("Text Distance Color").c_str(), Temp::Distance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPDistance.Value.x = Temp::Distance[0]; Colors::ESPDistance.Value.y = Temp::Distance[1]; Colors::ESPDistance.Value.z = Temp::Distance[2]; Colors::ESPDistance.Value.w = Temp::Distance[3];

				ImGui::ColorEdit4(XorStr("Text Health Color").c_str(), Temp::HpText, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPHpText.Value.x = Temp::HpText[0]; Colors::ESPHpText.Value.y = Temp::HpText[1]; Colors::ESPHpText.Value.z = Temp::HpText[2]; Colors::ESPHpText.Value.w = Temp::HpText[3];

				ImGui::ColorEdit4(XorStr("Lines Color").c_str(), Temp::Lines, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				Colors::ESPLines.Value.x = Temp::Lines[0]; Colors::ESPLines.Value.y = Temp::Lines[1]; Colors::ESPLines.Value.z = Temp::Lines[2]; Colors::ESPLines.Value.w = Temp::Lines[3];


			}
			ImGui::EndChild();
			break;
		case antiaim:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Exploits"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("##container"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Checkbox(skCrypt("God Mode"), &ex_godmode);
				ImGui::Checkbox(skCrypt("Semi GodMode"), &ex_semigodmode);
				ImGui::Checkbox(skCrypt("Run Speed"), &ex_runspeed_on);
				ImGui::Checkbox(skCrypt("Vehicle Acceleration"), &ex_vehicleaceleration);
				ImGui::Checkbox(skCrypt("Vehicle GodMode"), &ex_vehiclegodmode);
				ImGui::Checkbox(skCrypt("No Recoil"), &ex_norecoil);
				ImGui::Checkbox(skCrypt("No Reload"), &ex_noreaload);
				ImGui::Checkbox(skCrypt("No Spread"), &ex_nospread);

			}
			ImGui::EndChild();

			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 285, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Settings"));

			ImGui::SetCursorPos({ 285, 85 });
			ImGui::BeginChild(skCrypt("##container1"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::SliderFloat(XorStr("Run Speed").c_str(), &ex_runspeed_value, 0.f, 1000000.f, "% .1f");
				ImGui::SliderFloat(XorStr("Vehicle Acceleration").c_str(), &ex_vehicleaceleration_value, 0.f, 20000.f, "% .2f");
				if (ImGui::Button("Fix Engine", ImVec2(192, 22))) {
					Vehicle::FixEngine(1000.f);
				}
			}
			ImGui::EndChild();
			break;
		case settings:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Settings"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("##container"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar); {
				ImGui::Combo(skCrypt("Menu Bind"), &bind_menu, menu_bind, IM_ARRAYSIZE(menu_bind));
				ImGui::Combo(skCrypt("Aimbot Bind"), &bind_aimbot, aimbot_bind, IM_ARRAYSIZE(aimbot_bind));
				ImGui::Combo(skCrypt("TriggerBot Bind"), &bind_trigger, trigger_bind, IM_ARRAYSIZE(trigger_bind));

			}
			ImGui::EndChild();
			break;
		case friendlist:
			draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), skCrypt("Friend-List"));

			ImGui::SetCursorPos({ 25, 85 });
			ImGui::BeginChild(skCrypt("Friend List"), ImVec2(219, 342));
			{
				PlayerList();
			}
			ImGui::EndChild();
			break;
		}
		
		ImGui::End();

	}

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(menu_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(menu_window);
}

void ReallockLocalPlayer() {
	while (true) {

		localplayer = read_mem<uintptr_t>(world_ptr + (0x8));

	}
}

string procname = "";
int initialize() {
	attach_window = FindWindowA("grcWindow", 0);
	DWORD off_world, off_replay, off_view;
	if (isProcRunning(skCrypt("FiveM_GTAProcess.exe").decrypt())) {
		off_world = offset::b1604::world_ptr;
		off_replay = offset::b1604::ReplayInterface_ptr;
		off_view = offset::b1604::viewport_ptr;
		procname = skCrypt("FiveM_GTAProcess.exe");
	}
	else if (isProcRunning(skCrypt("FiveM_b2060_GTAProcess.exe").decrypt())) {
		off_world = offset::b2060::world_ptr;
		off_replay = offset::b2060::ReplayInterface_ptr;
		off_view = offset::b2060::viewport_ptr;
		procname = skCrypt("FiveM_b2060_GTAProcess.exe");

	}
	else if (isProcRunning(skCrypt("FiveM_b2189_GTAProcess.exe").decrypt())) {
		off_world = offset::b2189::world_ptr;
		off_replay = offset::b2189::ReplayInterface_ptr;
		off_view = offset::b2189::viewport_ptr;
		procname = skCrypt("FiveM_b2189_GTAProcess.exe");

	}
	else if (isProcRunning(skCrypt("FiveM_b2372_GTAProcess.exe").decrypt())) {
		off_world = offset::b2372::world_ptr;
		off_replay = offset::b2372::ReplayInterface_ptr;
		off_view = offset::b2372::viewport_ptr;
		procname = skCrypt("FiveM_b2372_GTAProcess.exe");

	}
	else if (isProcRunning(skCrypt("FiveM_b2545_GTAProcess.exe").decrypt())) {
		off_world = offset::b2545::world_ptr;
		off_replay = offset::b2545::ReplayInterface_ptr;
		off_view = offset::b2545::viewport_ptr;
		procname = skCrypt("FiveM_b2545_GTAProcess.exe");

	}
	else if (isProcRunning(skCrypt("FiveM_b2612_GTAProcess.exe").decrypt())) {
		off_world = offset::b2612::world_ptr;
		off_replay = offset::b2612::ReplayInterface_ptr;
		off_view = offset::b2612::viewport_ptr;
		procname = skCrypt("FiveM_b2612_GTAProcess.exe");
	}
	else if (isProcRunning(skCrypt("FiveM_b2699_GTAProcess.exe").decrypt())) {
		off_world = offset::b2699::world_ptr;
		off_replay = offset::b2699::ReplayInterface_ptr;
		off_view = offset::b2699::viewport_ptr;
		procname = skCrypt("FiveM_b2699_GTAProcess.exe");
	}
	else if (isProcRunning(skCrypt("FiveM_b2802_GTAProcess.exe").decrypt())) {
		offset::detectv2802 = true;
		off_world = offset::b2802::world_ptr;
		off_replay = offset::b2802::ReplayInterface_ptr;
		off_view = offset::b2802::viewport_ptr;
		procname = skCrypt("FiveM_b2802_GTAProcess.exe");
	}
	else if (isProcRunning(skCrypt("FiveM_b2944_GTAProcess.exe").decrypt())) {
		offset::detectv2802 = true;
		off_world = offset::b2944::world_ptr;
		off_replay = offset::b2944::ReplayInterface_ptr;
		off_view = offset::b2944::viewport_ptr;
		procname = skCrypt("FiveM_bb2944_GTAProcess.exe");
	}
	else if (isProcRunning(skCrypt("FiveM_b3095_GTAProcess.exe").decrypt())) {
		offset::detectv2802 = true;
		off_world = offset::b3095::world_ptr;
		off_replay = offset::b3095::ReplayInterface_ptr;
		off_view = offset::b3095::viewport_ptr;
		procname = skCrypt("FiveM_b3095_GTAProcess.exe");
	
	}
	if (!attach_window) {
		MessageBoxA(0, skCrypt("FiveM application not found."), 0, 0);
		ExitProcess(0);
	}

	//fps();

	DWORD pid;
	GetWindowThreadProcessId(attach_window, &pid);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	base_address = get_module_base64(pid, std::wstring(procname.begin(), procname.end()).c_str());

	ReplayInterface_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_replay));

	world_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_world));

	viewport_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_view));

	localplayer = read_mem<uintptr_t>(world_ptr + (0x8));


	setupWindow();
	if (!menu_window) { return 1; }

	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ReallockLocalPlayer, nullptr, NULL, nullptr);
	tema();
	while (!glfwWindowShouldClose(menu_window)) {
		handleKeyPresses();
		Render();
	}

	cleanupWindow();
}

void slowPrint(const std::string& message, int milliseconds) {
	for (char c : message) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
}

std::string key;

int main() {
#define color SetConsoleTextAttribute
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	int delay = 50;

	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 800;

	SetCurrentConsoleFontEx(hOut, NULL, &fontex);

	color(hConsole, 4);

	initialize();

}
