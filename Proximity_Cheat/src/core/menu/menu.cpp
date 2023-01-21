#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "./chatbox/ChatBox.h"

#include "socket/msoket.h"
#include "socket/packet/Packet.h"

#include "core/features/features.hpp"
#include "core/menu/menu.hpp"
#include "core/features/visuals/skin_changer/skin_changer.hpp"
#include "core/config/config.hpp"
#include "dependencies/imgui/imgui_internal.h"
#include "snowflake/snowflake.hpp"



using namespace ens;




#define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

void setOurCustomImguiColorsAndEtc(LPDIRECT3DDEVICE9);

//float alertboxX = 10.0f;
//float alertboxY = 10.0f;
//float alertboxWidth = 300.0f;
//float alertboxHeight = 100.0f;
//float lineLength = 300.0f;
//float lineThickness = 2.0f;
//float alpha = 255.0f;
//
//// Bu fonksiyon, alertbox'� animasyonlu bir �ekilde g�sterir
//void showAlertBox() {
//	// Alertbox'�n pozisyonunu ve �zelliklerini g�ncelle
//	alertboxX += (targetX - alertboxX) * 0.1f;
//	alertboxY += (targetY - alertboxY) * 0.1f;
//	lineLength -= 3.0f * Time.deltaTime;
//	alpha -= Time.deltaTime * 255.0f;
//
//	// Alertbox'� �iz
//	ImGui.SetNextWindowPos(new Vector2(alertboxX, alertboxY));
//	ImGui.SetNextWindowSize(new Vector2(alertboxWidth, alertboxHeight));
//	ImGui.Begin("Alert Box", ref showAlertBox, ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoCollapse);
//
//	// Ufak �izgi �iz
//	ImGui.GetWindowDrawList().AddLine(new Vector2(lineLength, alertboxHeight - lineThickness), new Vector2(lineLength, alertboxHeight), ImGui.GetColorU32(new Vector4(1, 1, 1, alpha / 255.0f)), lineThickness);
//
//	// Alertbox'�n i�eri�ini olu�tur
//	ImGui.Text("This is an alert box!");
//	ImGui.End();
//}

struct windowSize {
	float width;
	float height;
};

auto getMenuPos = [](ImVec2& pos) {
	pos = ImGui::GetWindowPos();
};

auto getCursorPos = [](ImVec2& pos) {
	pos = ImGui::GetCursorPos();
};

auto getZtkColor = [](int red, int green, int blue, int alpha = 255)
{
	return ImVec4((float)red / 255.0f, (float)green / 255.0f, (float)blue / 255.0f, (float)alpha / 255.0f);
};

void GetWindowSize(windowSize& size, LPDIRECT3DDEVICE9 pDevice);

/*
auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
	// Background
	render::draw_filled_rect(x, y, w, h, bg);
	// Header title
	render::draw_filled_rect(x, y, w, 30, header_text);
	render::draw_filled_rect(x, y + 30, w, 2, header_line);
	render::draw_text_string(x + 10, y + 8, render::fonts::watermark_font, name, false, color::white(255));
};

void menu::render() {
	if (!variables::ui::menux::opened) return;

	// Menu title and all that
	do_frame(variables::ui::menux::x, variables::ui::menux::y, variables::ui::menux::w, variables::ui::menux::h,
		color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "Rogsoftware");

	#pragma region TABS

	constexpr int tab_number = 4;
	const int tab_size   = variables::ui::menux::w / tab_number;

	gui::tab(variables::ui::menux::x + (tab_size * 0), variables::ui::menux::y + gui::vars::top_margin, tab_size, gui::vars::tab_height,
		render::fonts::watermark_font, "Aim", menu::current_tab, 0);
	gui::tab(variables::ui::menux::x + (tab_size * 1), variables::ui::menux::y + gui::vars::top_margin, tab_size, gui::vars::tab_height,
		render::fonts::watermark_font, "Visuals", menu::current_tab, 1);
	gui::tab(variables::ui::menux::x + (tab_size * 2), variables::ui::menux::y + gui::vars::top_margin, tab_size, gui::vars::tab_height,
		render::fonts::watermark_font, "Misc", menu::current_tab, 2);
	gui::tab(variables::ui::menux::x + (tab_size * 3), variables::ui::menux::y + gui::vars::top_margin, tab_size, gui::vars::tab_height,
		render::fonts::watermark_font, "Config", menu::current_tab, 3);
	#pragma endregion

	#pragma region CONTAINERS

	gui::update_positions();		// Get the updated variables with current menux pos and all that

	switch (current_tab) {
		// Aim
		case 0: {
			gui::init_tab();

			gui::add_groupbox("General", 3); {
				gui::add_checkbox	("Also target friendly",				variables::aim::target_friends);
				gui::add_checkbox	("Enable noscope aimbot on snipers",	variables::aim::aimbot_noscope);
				gui::add_checkbox	("Enable non-rifle aim punch",			variables::aim::non_rifle_aimpunch);
			}

			gui::add_groupbox("Triggerbot", 3); {
				gui::add_checkbox	("Enable triggerbot",	variables::aim::triggerbot);
				gui::add_hotkey		("Triggerbot key",		variables::aim::triggerbot_key);
				gui::add_slider		("Triggerbot delay",	variables::aim::triggerbot_delay, 0.f, 30.f);
			}

			gui::add_groupbox("Aimbot", 13); {
				gui::add_checkbox		("Enable aimbot",			variables::aim::aimbot);
				gui::add_checkbox		("Autofire",				variables::aim::autofire);
				gui::add_checkbox		("Auto revolver",			variables::aim::autorevolver);
				gui::add_hotkey			("Only on key",				variables::aim::aimbot_key);
				gui::add_checkbox		("Silent",					variables::aim::silent);
				gui::add_combobox		("Autowall",				variables::aim::autowall_settings, variables::aim::autowall);
				gui::add_multicombobox	("Aimbot hitboxes",			variables::aim::hitboxes);
				gui::add_checkbox		("Bodyaim if lethal",		variables::aim::bodyaim_if_lethal);
				gui::add_checkbox		("Priorize lethal targets",	variables::aim::priorize_lethal_targets);
				gui::add_slider			("Minimum damage",			variables::aim::min_damage, 0.f, 100.f);
				gui::add_slider			("Aimbot fov",				variables::aim::aimbot_fov, 0.f, 180.f);
				gui::add_checkbox		("Draw fov",				variables::aim::draw_fov, variables::colors::aimbot_fov_c);
				gui::add_slider			("Aimbot smoothing",		variables::aim::aimbot_smoothing, 0.f, 1.f);
			}

			gui::add_column();

			gui::add_groupbox("Antiaim", 7); {
				gui::add_checkbox	("AntiAim",						variables::antiaim::antiaim);
				gui::add_slider		("Pitch (x)",					variables::antiaim::pitch, -89.f, 89.f);
				gui::add_slider		("Yaw (y)",						variables::antiaim::yaw, -180.f, 180.f);
				gui::add_checkbox	("Spinbot",						variables::antiaim::spinbot);
				gui::add_slider		("Spinbot speed",				variables::antiaim::spinbot_speed, 0.f, 100.f);
				gui::add_checkbox	("Peek antiaim (Manual)",		variables::antiaim::peek_aa);						// Probably needs name change
				gui::add_hotkey		("Peek antiaim toggle",			variables::antiaim::peek_aa_toggle_key);
			}
			break;
		}
		// Visuals
		case 1:	{
			gui::init_tab();

			gui::add_groupbox("Player ESP", 7); {
				gui::add_checkbox		("Enable team ESP (global)",	variables::player_visuals::showteamesp, variables::colors::friendly_color);
				gui::add_checkbox		("Box ESP",						variables::player_visuals::boxesp, variables::colors::enemy_color);
				gui::add_checkbox		("Skeleton ESP",				variables::player_visuals::skeletonesp, variables::colors::enemy_color_soft);
				gui::add_checkbox		("Name ESP",					variables::player_visuals::nameesp);
				gui::add_multicombobox	("Player info",					variables::player_visuals::playerinfo);
				gui::add_checkbox		("Health ESP",					variables::player_visuals::healthesp);
				gui::add_checkbox		("Line ESP",					variables::player_visuals::lineesp);
			}

			gui::add_groupbox("Chams", 13); {
				gui::add_checkbox("Only visible chams",			variables::chams::only_visible_chams);
				gui::add_checkbox("Wireframe chams",			variables::chams::wireframe_chams);
				gui::add_checkbox("Draw on top",				variables::chams::draw_chams_on_top);
				gui::add_checkbox("Player chams",				variables::chams::player_chams, variables::colors::chams_vis_friend_c, variables::colors::chams_vis_enemy_c);
				gui::add_combobox("Player chams material",		variables::chams::materials, variables::chams::player_chams_mat_id);
				gui::add_checkbox("Local player chams",			variables::chams::localplayer_chams, variables::colors::chams_localplayer);
				gui::add_combobox("Local chams material",		variables::chams::materials, variables::chams::localplayer_chams_mat_id);
				gui::add_checkbox("Viewmodel weapon chams",		variables::chams::vm_weapon_chams, variables::colors::chams_weapon_c);
				gui::add_combobox("Weapon chams material",		variables::chams::materials, variables::chams::weapon_chams_mat_id);
				gui::add_checkbox("Arms chams",					variables::chams::vm_arm_chams, variables::colors::chams_arms_c);
				gui::add_combobox("Arms chams material",		variables::chams::materials, variables::chams::arm_chams_mat_id);
				gui::add_checkbox("Sleeve chams",				variables::chams::vm_sleeve_chams, variables::colors::chams_sleeve_c);
				gui::add_combobox("Sleeve chams material",		variables::chams::materials, variables::chams::sleeve_chams_mat_id);
			}

			gui::add_column();

			gui::add_groupbox("Glow", 3); {
				gui::add_checkbox("Player glow",		variables::player_visuals::playerglow, variables::colors::friendly_glow_c, variables::colors::enemy_glow_c);
				gui::add_checkbox("Entity glow",		variables::entity_visuals::entityglow, variables::colors::entity_glow_c);
				gui::add_checkbox("Chicken pride",		variables::misc_visuals::chickenpride);
			}

			gui::add_groupbox("Other ESP", 3); {
				gui::add_checkbox("Bomb timer",				variables::entity_visuals::bombtimer);
				gui::add_checkbox("Nade projectile ESP",	variables::entity_visuals::nade_esp);
				gui::add_combobox("Entity info",			variables::entity_visuals::entity_esp_settings, variables::entity_visuals::entity_esp);
			}

			gui::add_groupbox("Misc", 9); {
				gui::add_slider			("No flash",				variables::misc_visuals::noflash_alpha, 0.f, 1.f);
				gui::add_checkbox		("Wireframe smoke",			variables::misc_visuals::wireframe_smoke);
				gui::add_checkbox		("Nade prediction",			variables::misc_visuals::nade_predict);
				gui::add_checkbox		("No sniper scope",			variables::misc_visuals::noscope);
				gui::add_checkbox		("Worldcolor",				variables::misc_visuals::worldcolor, variables::colors::worldcolor_c);
				gui::add_multicombobox	("Bullet tracers",			variables::misc_visuals::bulletracer_draw_target);
				gui::add_multicombobox	("Bullet tracer teams",		variables::misc_visuals::bulletracer_team_target);
				gui::add_checkbox		("Custom crosshair",		variables::misc_visuals::crosshair, variables::colors::crosshair_c);
				gui::add_checkbox		("Recoil crosshair",		variables::misc_visuals::recoil_crosshair, variables::colors::recoil_crosshair_c);
			}
			break;
		}
		case 2: {	// Misc
			gui::init_tab();

			gui::add_groupbox("Network", 4); {
				gui::add_checkbox	("Backtrack",			variables::misc::backtrack);
				gui::add_slider		("Backtrack ms",		variables::misc::backtrack_ticks, 0.f, 400.f);
				gui::add_checkbox	("Also friendly",		variables::misc::backtrack_team, variables::colors::bt_chams_friend_fade, variables::colors::bt_chams_friend);
				gui::add_checkbox	("Backtrack chams",		variables::chams::backtrack_chams, variables::colors::bt_chams_enemy_fade, variables::colors::bt_chams_enemy);
			}

			gui::add_groupbox("Movement", 11); {
				gui::add_checkbox	("Infinite duck (WARNING: Untrusted)",	variables::misc::infinite_duck);
				gui::add_checkbox	("Bhop",								variables::misc::bhop);
				gui::add_combobox	("Autostrafe",							variables::misc::autostrafe_options, variables::misc::autostrafe_target);
				gui::add_checkbox	("Enable edgejump",						variables::misc::edgejump);
				gui::add_hotkey		("Edgejump key",						variables::misc::ej_key);
				gui::add_checkbox	("Edgebug",								variables::misc::edgebug);
				gui::add_hotkey		("Edgebug key",							variables::misc::eb_key);
				gui::add_checkbox	("Jumpbug",								variables::misc::jumpbug);
				gui::add_hotkey		("Jumpbug key",							variables::misc::jb_key);
				gui::add_checkbox	("Slowwalk",							variables::misc::slowwalk);
				gui::add_hotkey		("Slowwalk key",						variables::misc::slowwalk_key);
			}

			gui::add_groupbox("Speedgraph", 3); {
				gui::add_multicombobox	("Speedgraph options",	variables::misc::speedgraph_target);
				gui::add_slider			("Speedgraph height",	variables::misc::speedgraph_h, 0.f, 100.f);
				gui::add_slider			("Speedgraph pos",		variables::misc::speedgraph_pos, 0.f, 100.f);
			}
			
			gui::add_column();

			gui::add_groupbox("Thirdperson", 3); {
				gui::add_checkbox	("Thirdperson",				variables::misc::thirdperson);
				gui::add_hotkey		("Thirdperson toggle key",	variables::misc::thirdperson_key);
				gui::add_slider		("Thirdperson distance",	variables::misc::thirdperson_dist, 50.f, 200.f);
			}

			gui::add_groupbox("Interface", 4); {
				gui::add_checkbox("Hide cheat on screenshots",	variables::misc::clean_screenshots);
				gui::add_multicombobox("Watermark",				variables::misc::watermark);
				gui::add_checkbox("Spectator list",				variables::ui::spectators::spectator_list);
				gui::add_checkbox("Reveal ranks",				variables::misc::reveal_ranks);
			}

			gui::add_groupbox("Fov", 2); {
				gui::add_slider("Custom FOV",				variables::misc_visuals::custom_fov_slider, 80.f, 130.f);
				gui::add_slider("Custom viewmodel FOV",		variables::misc_visuals::custom_vmfov_slider, 0.5f, 2.f);
			}

			gui::add_groupbox("Motion blur", 5); {
				gui::add_checkbox	("Enable motion blur",		variables::motion_blur.enabled);
				gui::add_checkbox	("Forward motion blur",		variables::motion_blur.forwardEnabled);
				gui::add_slider		("Strenght",				variables::motion_blur.strength, 0.f, 15.f);
				gui::add_slider		("Falling intensity",		variables::motion_blur.fallingIntensity, 0.f, 10.f);
				gui::add_slider		("Rotation intensity",		variables::motion_blur.rotationIntensity, 0.f, 10.f);
			}


			gui::add_bottom_groupbox(1);
			// Not as dynamic because its at the bottom and with the whole width
			gui::groupbox(gui::vars::o_container_left_pos, gui::vars::button_part_y, gui::vars::o_container_width, gui::vars::button_part_h, render::fonts::watermark_font, "Buttons", false); {
				gui::button(gui::vars::o_item_left_pos, gui::vars::button_base_item_y + (15 * 0), gui::vars::o_item_checkbox_pos - 20, render::fonts::watermark_font,		// Bigger "checkbox" as button
					"Exec autoexec", button_functions::exec_autoexec);																										// @todo: Pass size and pos
			}
			break;
		}
		case 3: {	// Config
			gui::init_tab();

			gui::add_groupbox("Config", 4); {
				gui::add_button		("Refresh configs",			config::refresh_list);
				gui::add_textbox	("Config name...",			config::new_config_name, config::create_new_config);
				gui::add_button		("Load selected config",	config::load_selected_config);
				gui::add_button		("Save selected config",	config::save_selected_config);
			}

			gui::add_groupbox("Skins", 2); {
				gui::add_button("Load skin config",					skins::read_skins);
				gui::add_button("Update game skins (Full update)",	button_functions::full_update);
			}

			gui::add_column();

			gui::add_groupbox("Config selection", config::max_configs); {
				gui::config_selection(gui::vars::container_left_pos, gui::vars::cur_base_item_y, gui::vars::container_width, render::fonts::watermark_font,
					config::config_names);
			}
			break;
		}
	}
	#pragma endregion

	#pragma region WINDOW MOVEMENTS
	spectator_framework::spec_list_movement(variables::ui::spectators::x, variables::ui::spectators::y, variables::ui::spectators::w, variables::ui::spectators::h);
	gui::menu_movement(variables::ui::menux::x, variables::ui::menux::y, variables::ui::menux::w, 30);
	#pragma endregion

}

// Toggle using IsPressed (GetAsyncKeyState)
void menu::check_toggle() {
	if (input::global_input.IsPressed(VK_XBUTTON2))
		variables::ui::menux::opened = !variables::ui::menux::opened;
}

// Makes the window positions relative based on screen size
void menu::init_windows() {
	int screen_w, screen_h;
	interfaces::engine->get_screen_size(screen_w, screen_h);

	variables::ui::menux::y = screen_h * 0.2;
	variables::ui::menux::x = screen_w * 0.2;
	variables::ui::spectators::y = screen_h * 0.5;		// For smaller screens
}
*/


/*void menux::renderImguiBasedMenu() {
	ImGui::ShowDemoWindow();
}*/

void imspaceMacro(float x, float y) {
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + x, ImGui::GetCursorPos().y + y));
}

bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	// Render
	window->DrawList->PathClear();

	int num_segments = 30;
	int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

	const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

	for (int i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
			centre.y + ImSin(a + g.Time * 8) * radius));
	}

	window->DrawList->PathStroke(color, false, thickness);
}



void GetWindowSize(windowSize& size, LPDIRECT3DDEVICE9 pDevice) {
	D3DDEVICE_CREATION_PARAMETERS cparams;
	RECT rect;

	pDevice->GetCreationParameters(&cparams);
	GetWindowRect(cparams.hFocusWindow, &rect);


	size.width = (float)rect.right - rect.left;
	size.height = (float)rect.bottom - rect.top;
}

int calculateUiScalar(int scalaDef) {
	if (false)
	{
		if (variables::Menu_Settings::ui_scalar == 200)
			return scalaDef + ((scalaDef * 200) / 100);
		else if (variables::Menu_Settings::ui_scalar == 175)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 150)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 125)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 100)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 75)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 50)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 25)
			return 0000;
		else if (variables::Menu_Settings::ui_scalar == 0)
			return 0000;
		else
			return scalaDef;
	}

	int bclakcX = (scalaDef * variables::Menu_Settings::ui_scalar) / 100;

	if (bclakcX < 0)
		bclakcX = 0;
	return bclakcX;
}

void customComboBox(int& selectedItemID, std::vector<const char*>& lList) {
	ImGuiStyle& imguiStyles = ImGui::GetStyle();
	imguiStyles.FramePadding = ImVec2(4, 4);

	const char* selectedItemName = selectedItemID == -1 ? "none" : lList.at(selectedItemID);
	if (ImGui::BeginCombo("##combo", selectedItemName)) // The second parameter is the label previewed before opening the combo.
	{

		for (int n = 0; n < lList.size(); n++)
		{

			bool is_selected = (selectedItemID == n); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(lList.at(n), is_selected))
			{
				selectedItemID = is_selected ? -1 : n;
				ImGui::SetItemDefaultFocus();

			}

		}
		ImGui::EndCombo();
	}

	imguiStyles.FramePadding = ImVec2(1.2f, 1.2f);
}

void renderAimbotPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height - 60));

	ImGui::BeginChild("#aimbot_menu_basement", cMenuSize, false);
	{
		ImGui::BeginChild("#aa_state_left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Enabled", &variables::Aimbot_Settings::enabled);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Team Check", &variables::Aimbot_Settings::teamCheck);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("No Scope", &variables::Aimbot_Settings::noScope);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Fire", &variables::Aimbot_Settings::autofire);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Silent Aim", &variables::Aimbot_Settings::silentAim);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Non Rifle Aim Punch", &variables::Aimbot_Settings::non_rifle_aimpunch);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Revolver", &variables::Aimbot_Settings::auto_revolver);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Draw Fov", &variables::Aimbot_Settings::drawFov);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Priorize Lethal Targets", &variables::Aimbot_Settings::priorize_lethal_targets);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Wall", &variables::Aimbot_Settings::auto_wall);




			ImGui::PushItemWidth(cMenuSize.x / 2 - (ImGui::CalcTextSize("Aimbot Fov").x + 30));

			imspaceMacro(10, 10);
			ImGui::SliderFloat("Aimbot Fov", &variables::Aimbot_Settings::aimbot_fov, 0, 180.f, "%.1f");

			ImGui::PopItemWidth();




			ImGui::PushItemWidth(cMenuSize.x / 2 - (ImGui::CalcTextSize("Aimbot Hitchance").x + 30));

			imspaceMacro(10, 10);
			ImGui::SliderFloat("Aimbot Hitchance", &variables::Aimbot_Settings::aimbot_hitchance, 0.f, 125.f, "%.1f");

			ImGui::PopItemWidth();





			ImGui::PushItemWidth(cMenuSize.x / 2 - (ImGui::CalcTextSize("Smoothness").x + 30));

			imspaceMacro(10, 10);
			ImGui::SliderFloat("Smoothness", &variables::Aimbot_Settings::aimbot_smoothing,0.f, 1.f);

			ImGui::PopItemWidth();





			ImGui::PushItemWidth(cMenuSize.x / 2 - (ImGui::CalcTextSize("Min Damage").x + 30));

			imspaceMacro(10, 10);
			ImGui::SliderFloat("Min Damage", &variables::Aimbot_Settings::min_damage, 0, 120.f, "%.0f");

			ImGui::PopItemWidth();

			 
			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);


		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#aa_state_right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			ImGui::PushItemWidth(cMenuSize.x / 2 - 30);
			{
				imspaceMacro(10, 10);
				ImGui::ListBoxHeader("#aimbot_hitboxes_list", 4, 10);
				{
					for (size_t i = 0; i < IM_ARRAYSIZE(variables::Aimbot_Settings::selected_hitboxes); i++)
					{
						bool* isSelected = &variables::Aimbot_Settings::selected_hitboxes[i];

						if (ImGui::Selectable(variables::Aimbot_Settings::selected_hitboxes_names[i], *isSelected))
						{
							*isSelected = !*isSelected;
						}
					}
				}
				ImGui::ListBoxFooter();
			}
			ImGui::PopItemWidth();
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderAntiAimPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));

	ImGui::BeginChild("#AntiAimMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#aa_state_left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			/*imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Enabled", &variables::Aimbot_Settings::enabled);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Team Check", &variables::Aimbot_Settings::teamCheck);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Fire", &variables::Aimbot_Settings::autofire);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Revolver", &variables::Aimbot_Settings::auto_revolver);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Auto Wall", &variables::Aimbot_Settings::auto_wall);
			imspaceMacro(10, 10);
			ImGui::PushItemWidth(cMenuSize.x / 2 - (ImGui::CalcTextSize("Min Damage").x + 30));
			ImGui::SliderFloat("Min Damage", &variables::Aimbot_Settings::min_damage, 0, 120.f, "%.0f");
			imspaceMacro(10, 10);
			ImGui::SliderFloat("Aimbot Fov", &variables::Aimbot_Settings::aimbot_fov, 0, 180.f, "%.1f");
			ImGui::PopItemWidth();*/

			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);

		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#aa_state_right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {

		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderEspPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));
	ImGuiStyle& imguiStyles2 = ImGui::GetStyle();
	ImGui::BeginChild("#EspMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#esp-state-left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			if (variables::Esp_Settings::selected_team == 0)
				imguiStyles2.Colors[ImGuiCol_Button] = ImColor(35, 90, 30);



			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Enabled Base", &variables::Esp_Settings::enabledBase);


			imspaceMacro(10, 10);
			if (ImGui::Button("Enemy", ImVec2((cMenuSize.x / 2) / 3 - 13.3, 30)))
				variables::Esp_Settings::selected_team = 0;

			ImGui::SameLine();

			imguiStyles2.Colors[ImGuiCol_Button] = ImColor(40, 40, 40);

			if (variables::Esp_Settings::selected_team == 1)
				imguiStyles2.Colors[ImGuiCol_Button] = ImColor(35, 90, 30);
			imspaceMacro(10, 0);
			if (ImGui::Button("Team", ImVec2((cMenuSize.x / 2) / 3 - 13.3, 30)))
				variables::Esp_Settings::selected_team = 1;
			ImGui::SameLine();
			imguiStyles2.Colors[ImGuiCol_Button] = ImColor(40, 40, 40);

			if (variables::Esp_Settings::selected_team == 2)
				imguiStyles2.Colors[ImGuiCol_Button] = ImColor(35, 90, 30);

			imspaceMacro(10, 0);
			if (ImGui::Button("Local", ImVec2((cMenuSize.x / 2) / 3 - 13.3, 30)))
				variables::Esp_Settings::selected_team = 2;

			imguiStyles2.Colors[ImGuiCol_Button] = ImColor(40, 40, 40);

			imspaceMacro(10, 20);
			ImGui::CheckboxTypeB("Name", &variables::Esp_Settings::enabledNameesp[variables::Esp_Settings::selected_team]);

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Health", &variables::Esp_Settings::enabledHealthesp[variables::Esp_Settings::selected_team]);

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Box", &variables::Esp_Settings::enabledBox[variables::Esp_Settings::selected_team]);

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Line", &variables::Esp_Settings::enabledLine[variables::Esp_Settings::selected_team]);

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Skeleton", &variables::Esp_Settings::enabledSkeleton[variables::Esp_Settings::selected_team]);

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Other Info", &variables::Esp_Settings::enabledGethers[variables::Esp_Settings::selected_team]);



			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);

		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#esp-state-right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			{
				imspaceMacro(10, 10);
				ImGui::Text("Enemy Box Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_box_color", variables::Esp_Settings::colors_box[0]);

				imspaceMacro(10, 10);
				ImGui::Text("Enemy Name Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_name_color", variables::Esp_Settings::colors_name[0]);

				imspaceMacro(10, 10);
				ImGui::Text("Enemy Line Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_line_color", variables::Esp_Settings::colors_line[0]);

				imspaceMacro(10, 10);
				ImGui::Text("Enemy Skeleton Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_skeleton_color", variables::Esp_Settings::colors_skeleton[0]);

				imspaceMacro(10, 10);
				ImGui::Text("Enemy Health Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_health_color", variables::Esp_Settings::colors_health[0]);

				imspaceMacro(10, 10);
				ImGui::Text("Enemy Info Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##enemy_info_color", variables::Esp_Settings::colors_info[0]);
			}

			imspaceMacro(10, 15);
			ImGui::Separator();

			{
				imspaceMacro(10, 10);
				ImGui::Text("Team Box Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_box_color", variables::Esp_Settings::colors_box[1]);

				imspaceMacro(10, 10);
				ImGui::Text("Team Name Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_name_color", variables::Esp_Settings::colors_name[1]);

				imspaceMacro(10, 10);
				ImGui::Text("Team Line Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_line_color", variables::Esp_Settings::colors_line[1]);

				imspaceMacro(10, 10);
				ImGui::Text("Team Skeleton Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_skeleton_color", variables::Esp_Settings::colors_skeleton[1]);

				imspaceMacro(10, 10);
				ImGui::Text("Team Health Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_health_color", variables::Esp_Settings::colors_health[1]);

				imspaceMacro(10, 10);
				ImGui::Text("Team Info Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##team_info_color", variables::Esp_Settings::colors_info[1]);
			}



			imspaceMacro(10, 15);
			ImGui::Separator();

			{
				imspaceMacro(10, 10);
				ImGui::Text("Local Box Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_box_color", variables::Esp_Settings::colors_box[2]);

				imspaceMacro(10, 10);
				ImGui::Text("Local Name Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_name_color", variables::Esp_Settings::colors_name[2]);

				imspaceMacro(10, 10);
				ImGui::Text("Local Line Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_line_color", variables::Esp_Settings::colors_line[2]);

				imspaceMacro(10, 10);
				ImGui::Text("Local Skeleton Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_skeleton_color", variables::Esp_Settings::colors_skeleton[2]);

				imspaceMacro(10, 10);
				ImGui::Text("Local Health Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_health_color", variables::Esp_Settings::colors_health[2]);

				imspaceMacro(10, 10);
				ImGui::Text("Local Info Color");
				imspaceMacro(10, 2);
				ImGui::ColorEdit4("##local_info_color", variables::Esp_Settings::colors_info[2]);
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderChamsPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));
	ImGuiStyle& imguiStyles2 = ImGui::GetStyle();
	ImGui::BeginChild("#ChamsMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#ChamsMenu-state-left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Chams General", &variables::chams::general_chams_enabled);
			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Draw Top", &variables::chams::draw_chams_on_top);

			imspaceMacro(10, 30);
			ImGui::CheckboxTypeB("Enemy Chams", &variables::chams::enemy_chams);
			if (variables::chams::enemy_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Enemy Only Visible", &variables::chams::enemy_only_visible);


				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Enemy Wireframe", &variables::chams::enemy_wireframe);


				imspaceMacro(10, 10);
				if (ImGui::BeginCombo("##enemy-material", variables::chams::materials[variables::chams::enemy_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < variables::chams::materials.size(); n++) 
					{
						bool is_selected = (variables::chams::enemy_chams_material == n); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
						{
							variables::chams::enemy_chams_material = n;
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
			}

			imspaceMacro(0, 15);
			ImGui::Separator();



			imspaceMacro(10, 15);
			ImGui::CheckboxTypeB("Team Chams", &variables::chams::team_chams);

			if (variables::chams::team_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Team Only Visible", &variables::chams::team_only_visible);


				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Team Wireframe", &variables::chams::team_wireframe);
				imspaceMacro(10, 10);

				if (ImGui::BeginCombo("##team-material", variables::chams::materials[variables::chams::team_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < variables::chams::materials.size(); n++)
					{
						bool is_selected = (variables::chams::team_chams_material == n); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
						{
							variables::chams::team_chams_material = n;
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
			}

			imspaceMacro(0, 15);
			ImGui::Separator();


			imspaceMacro(10, 15);
			ImGui::CheckboxTypeB("Local Chams", &variables::chams::local_chams);

			if (variables::chams::local_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Local Only Visible", &variables::chams::local_only_visible);

				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Local Wireframe", &variables::chams::local_wireframe);


				imspaceMacro(10, 10);

				if (ImGui::BeginCombo("##local-material", variables::chams::materials[variables::chams::local_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < variables::chams::materials.size(); n++)
					{
						bool is_selected = (variables::chams::local_chams_material == n); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
						{
							variables::chams::local_chams_material = n;
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
			}

			imspaceMacro(0, 15);
			ImGui::Separator();

			imspaceMacro(10, 15);
			ImGui::CheckboxTypeB("Weapon Chams", &variables::chams::weapon_chams);
			if (variables::chams::weapon_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Weapon Wireframe", &variables::chams::weapon_wireframe);

				{
					imspaceMacro(10, 10);

					if (ImGui::BeginCombo("##weapon-material", variables::chams::materials[variables::chams::weapon_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
					{
						for (int n = 0; n < variables::chams::materials.size(); n++)
						{
							bool is_selected = (variables::chams::weapon_chams_material == n); // You can store your selection however you want, outside or inside your objects
							if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
							{
								variables::chams::weapon_chams_material = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
				}

			}


			imspaceMacro(0, 15);
			ImGui::Separator();


			imspaceMacro(10, 15);
			ImGui::CheckboxTypeB("Arm Chams", &variables::chams::arm_chams);
			if (variables::chams::arm_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Arm Wireframe", &variables::chams::arm_wireframe);

				{
					imspaceMacro(10, 10);

					if (ImGui::BeginCombo("##arm-material", variables::chams::materials[variables::chams::arm_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
					{
						for (int n = 0; n < variables::chams::materials.size(); n++)
						{
							bool is_selected = (variables::chams::arm_chams_material == n); // You can store your selection however you want, outside or inside your objects
							if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
							{
								variables::chams::arm_chams_material = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
				}

			}


			imspaceMacro(0, 15);
			ImGui::Separator();


			imspaceMacro(10, 15);

			ImGui::CheckboxTypeB("Sleeve Chams", &variables::chams::sleeve_chams);

			if (variables::chams::sleeve_chams)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Sleeve Wireframe", &variables::chams::sleeve_wireframe);

				{
					imspaceMacro(10, 10);

					if (ImGui::BeginCombo("##sleeve-material", variables::chams::materials[variables::chams::sleeve_chams_material].c_str())) // The second parameter is the label previewed before opening the combo.
					{
						for (int n = 0; n < variables::chams::materials.size(); n++)
						{
							bool is_selected = (variables::chams::sleeve_chams_material == n); // You can store your selection however you want, outside or inside your objects
							if (ImGui::Selectable(variables::chams::materials[n].c_str(), is_selected))
							{
								variables::chams::sleeve_chams_material = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
				}

			}



			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);

			}
			ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#ChamsMenu-state-right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false);
		{
			if (variables::chams::general_chams_enabled)
			{
				if (variables::chams::enemy_chams)
				{

					imspaceMacro(10, 10);
					ImGui::Text("Enemy Chams Visible Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##enemy_chams_visible", variables::chams::player_colors_chams[ENEMY][VICIBLE]);

					if (!variables::chams::enemy_only_visible)
					{
						imspaceMacro(10, 10);
						ImGui::Text("Enemy Chams Hidden Color");
						imspaceMacro(10, 2);
						ImGui::ColorEdit4("##enemy_chams_invisible", variables::chams::player_colors_chams[ENEMY][INVICIBLE]);
					}
				}

				imspaceMacro(0, 15);

				if (variables::chams::team_chams)
				{
					ImGui::Separator();


					imspaceMacro(10, 15);
					ImGui::Text("Team Chams Visible Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##team_chams_visible", variables::chams::player_colors_chams[TEAM][VICIBLE]);

					if (!variables::chams::team_only_visible)
					{
						imspaceMacro(10, 10);
						ImGui::Text("Team Chams Hidden Color");
						imspaceMacro(10, 2);
						ImGui::ColorEdit4("##team_chams_invisible", variables::chams::player_colors_chams[TEAM][INVICIBLE]);
					}

				}

				imspaceMacro(0, 15);

				if (variables::chams::local_chams)
				{
					ImGui::Separator();


					imspaceMacro(10, 15);
					ImGui::Text("Local Chams Visible Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##local_chams_visible", variables::chams::player_colors_chams[LOCAL][VICIBLE]);

					if (!variables::chams::team_only_visible)
					{
						imspaceMacro(10, 10);
						ImGui::Text("Local Chams Hidden Color");
						imspaceMacro(10, 2);
						ImGui::ColorEdit4("##local_chams_invisible", variables::chams::player_colors_chams[LOCAL][INVICIBLE]);
					}

				}

				imspaceMacro(0, 15);

				if (variables::chams::weapon_chams)
				{
					ImGui::Separator();


					imspaceMacro(10, 15);
					ImGui::Text("Weapon Chams Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##weapon_chams_visible", variables::chams::colors_weapon);
				}

				imspaceMacro(0, 10);


				if (variables::chams::arm_chams)
				{
					ImGui::Separator();


					imspaceMacro(10, 15);
					ImGui::Text("Arm Chams Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##arm_chams_visible", variables::chams::colors_arm);
				}

				imspaceMacro(0, 15);

				if (variables::chams::sleeve_chams)
				{
					ImGui::Separator();


					imspaceMacro(10, 15);
					ImGui::Text("Sleeve Chams Color");
					imspaceMacro(10, 2);
					ImGui::ColorEdit4("##sleeve_chams_visible", variables::chams::colors_sleeve);
				}
			}

		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderSkinsPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));


	ImGui::BeginChild("#SkinsMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#skins-state-left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false);
		{

			imspaceMacro(10, 10);
			ImGui::CheckboxTypeB("Enabled", &variables::Skin_Changer::isEnabledBasement);

			int TsexVal = variables::Skin_Changer::skinlistSelectedWeaponID;
			imspaceMacro(10, 10);
			ImGui::PushItemWidth(cMenuSize.x / 2 - 20);
			{
				customComboBox(variables::Skin_Changer::skinlistSelectedWeaponID, variables::Skin_Changer::menuSkinsItemDefins);
			}
			ImGui::PopItemWidth();

			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);

		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#skins-state-right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false);
		{
			if (variables::Skin_Changer::skinlistSelectedWeaponID != -1)
			{
				imspaceMacro(10, 10);
				ImGui::CheckboxTypeB("Enabled", &variables::Skin_Changer::isEnabled[variables::Skin_Changer::skinlistSelectedWeaponID]);

				if (variables::Skin_Changer::skinlistSelectedWeaponID == 0)
				{
					imspaceMacro(10, 10);
					ImGui::PushItemWidth(cMenuSize.x / 2 - 20);
					{
						customComboBox(variables::Skin_Changer::selectedKnifeNameID, variables::Skin_Changer::knifeNames);
					}
					ImGui::PopItemWidth();
				}
				else if (variables::Skin_Changer::skinlistSelectedWeaponID == 1)
				{
					/*imspaceMacro(10, 10);
					ImGui::PushItemWidth(cMenuSize.x / 2 - 20);
					{
						customComboBox(variables::Skin_Changer::selectedKnifeNameID, variables::Skin_Changer::knifeNames);
					}
					ImGui::PopItemWidth();*/

					imspaceMacro(10, 10);
					ImGui::Text("Wait next update :)");
				}

				imspaceMacro(10, 10);
				ImGui::InputInt("Paint Kit", &variables::Skin_Changer::newPaintKit[variables::Skin_Changer::skinlistSelectedWeaponID]);
				imspaceMacro(10, 10);
				ImGui::InputInt("Seed", &variables::Skin_Changer::newSeed[variables::Skin_Changer::skinlistSelectedWeaponID]);
				imspaceMacro(10, 10);
				ImGui::InputInt("Stat Track", &variables::Skin_Changer::newStatTrak[variables::Skin_Changer::skinlistSelectedWeaponID]);
				imspaceMacro(10, 10);
				ImGui::InputInt("Quality", &variables::Skin_Changer::newQuality[variables::Skin_Changer::skinlistSelectedWeaponID]);
				imspaceMacro(10, 10);
				ImGui::InputFloat("Wear", &variables::Skin_Changer::newWear[variables::Skin_Changer::skinlistSelectedWeaponID]);
				//imspaceMacro(10, 10);
				//ImGui::InputText("Custom Name", (char*)&variables::Skin_Changer::newCustomName, strlen(variables::Skin_Changer::newCustomName[variables::Skin_Changer::skinlistSelectedWeaponID]));

				imspaceMacro(10, 10);
				if (ImGui::Button("SAVE & UPDATE", ImVec2(150, 35)))
				{
					interfaces::clientstate->full_update();
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderMiscPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));
	ImGuiStyle& imguiStyles2 = ImGui::GetStyle();
	ImGui::BeginChild("#MiscMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#misc-state-left", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			
			imspaceMacro(10, 10);
			//ImGui::CheckboxTypeB("Thirdperson", &variables::misc::thirdperson);
			ImGui::Text("The Alpha Feature");


			ImVec2 nPos = {};

			getMenuPos(nPos);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + 5), ImVec2(nPos.x + (cMenuSize.x / 2) - 2, nPos.y + cMenuSize.y - 10), ImColor(150, 150, 150), 2);

		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("#misc-state-right", ImVec2(cMenuSize.x / 2, cMenuSize.y), false); {
			imspaceMacro(10, 10);
			ImGui::Text("The Alpha Feature");
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void renderConfigsPage() {
	ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 - 8), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60));
	ImGuiStyle& imguiStyles2 = ImGui::GetStyle();
	ImGui::BeginChild("#SettingsMenu", cMenuSize, false);
	{
		ImGui::BeginChild("#settings_state_left", ImVec2(cMenuSize.x, cMenuSize.y), false);
		{
			for (auto item : config::configsList)
			{
				std::string configName = item.configName;
				std::string dateText = item.date;
				std::string authorName = (std::string("By ") + std::string(item.author));

				ImVec2 configNameSize = ImGui::CalcTextSize(configName.c_str());
				ImVec2 dateTextSize = ImGui::CalcTextSize(dateText.c_str());
				ImVec2 authorNameSize = ImGui::CalcTextSize(authorName.c_str());

				imspaceMacro(5, 5);

				ImGui::BeginChild(std::string(std::string("#cfg_item") + std::to_string(item.configId)).c_str(), ImVec2(cMenuSize.x - 10, 75), false);
				{
					ImGui::BeginChild(std::string(std::string("#cfg_item_text_side") + std::to_string(item.configId)).c_str(), ImVec2(configNameSize.x + 20 + authorNameSize.x + 20, 60), false);
					{
						ImGui::BeginChild(std::string(std::string("#cfg_item_text_inside") + std::to_string(item.configId)).c_str(), ImVec2(configNameSize.x + 20 + authorNameSize.x + 20 + 10, 40), false);
						{
							imspaceMacro(10, 60 / 2 - configNameSize.y / 2);
							ImGui::Text(configName.c_str());
						}
						ImGui::EndChild();

						imspaceMacro(10, 0);

						ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
						{
							ImGui::Text(authorName.c_str());

							ImGui::SameLine();

							imspaceMacro(1, 0);
							ImGui::Text(" - ");

							ImGui::SameLine();

							imspaceMacro(1, 0);
							ImGui::Text(dateText.c_str());
						}
						ImGui::PopFont();
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImVec2 rsSize = ImVec2((cMenuSize.x - 10) - (configNameSize.x + 20 + authorNameSize.x + 20), 60);

					ImGui::BeginChild(std::string(std::string("#cfg-item-right-side") + std::to_string(item.configId)).c_str(), ImVec2(rsSize), false);
					{
						ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
						{
							if (!mSocket::cfg::waiting_response)
							{
								imspaceMacro(rsSize.x - 146 - 5, 75 / 2 - (30 / 2));
								if (ImGui::Button("Save", ImVec2(60, 30)))
								{
									config::saveConfig(item);
								}

								ImGui::SameLine();
								imspaceMacro(10, 0);

								if (ImGui::Button("Load", ImVec2(60, 30)))
								{
									config::loadConfigFromServer(item);
								}
							}
						}
						ImGui::PopFont();
					}
					ImGui::EndChild();
					imspaceMacro(0, 14);

					ImGui::Separator();

				}
				ImGui::EndChild();
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}


void renderConnectingToServer(LPDIRECT3DDEVICE9 pDevice)
{
	ImGuiStyle& imguiStyles = ImGui::GetStyle();

	float FirstRadius = imguiStyles.WindowRounding;

	windowSize wsz;

	GetWindowSize(wsz, pDevice);
	
	std::string loadString = "";

	if (!mSocket::cfg::authed && mSocket::cfg::socketIsConnected)
		loadString = "Waiting authentication...";
	else if (variables::NetworkUser::fuckThisCheat)
		loadString = "Wtf are you doing?";
	else
		loadString = "Connecting to server";

	ImVec2 cTSize = ImGui::CalcTextSize(loadString.c_str());
	ImVec2 cWSize = ImVec2(0, 0);

	cWSize.x = 40 + cTSize.x + 10;
	cWSize.y = 40;

	imguiStyles.WindowRounding = 5.f;


	ImGui::SetNextWindowPos(ImVec2(wsz.width - cWSize.x - 10, 10));
	ImGui::SetNextWindowSize(cWSize);
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 255.f);
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));
			{
				ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(1, 100, 50, 25));
				{
					ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(35.0f / 255.0f, 160.0f / 255.0f, 30.0f / 255.0f, 1.0f));
					{
						ImGui::Begin("Loader :)", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);
						{
							imspaceMacro(10, 10 - (3/2));
							Spinner("#19954", 10, 3, ImColor(35, 160, 30));

							ImGui::SameLine();

							imspaceMacro(10, 0);
							ImGui::Text(loadString.c_str());
						}
						ImGui::End();
					}
					ImGui::PopStyleColor();
				}
				ImGui::PopStyleColor();
			}
			ImGui::PopStyleColor();
		}
		ImGui::PopStyleVar();
	}

	imguiStyles.WindowRounding = FirstRadius;
}
char dcbText[250] = {};
#define SNOW_LIMIT 60
std::vector<Snowflake::Snowflake> snow;

void iXmenu::renderImguiBasedMenu(LPDIRECT3DDEVICE9 pDevice, bool isActive) {
	static bool loaded = false;
	static bool firstanim = true; 
	int currenttime = (float)(clock() / 1000.f);
	static int startedtime = 0;
	static bool savetime = true;
	
	static bool initedFirstOpen = false;

	float deltaTime = ImGui::GetIO().DeltaTime;
	static float speed = 300.f;

	static float alpha = 0.0f;

	static int initSnowFlakes = false;
	int xxx, yyy;

	interfaces::engine->get_screen_size(xxx, yyy);
	if (!initSnowFlakes)
	{
		initSnowFlakes = true;
		Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 1.f/*minimum size*/, 10.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, xxx, yyy, Snowflake::vec3(0.f, 0.002f)/*gravity*/, IM_COL32(255, 255, 255, 100)/*color*/);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, interfaces::engine->is_in_game() ? (alpha > 0.f ? alpha : 0) : 255);
	{

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(xxx, yyy));
		ImGui::SetNextWindowBgAlpha(0.f);
		POINT mouse;
		ImGui::Begin("##qeqweqwad4qw98e4qw651", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
		{
			RECT rc;
			HWND mhwnd = FindWindowA(nullptr, "Counter-Strike: Global Offensive - Direct3D 9");
			GetWindowRect(mhwnd, &rc);

			if (ImGui::GetWindowPos().x != 0 || ImGui::GetWindowPos().y != 0)
			{
				//MoveWindow(mhwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight(), TRUE); // you dont need those two if you have an imgui window inside an actual window
				ImGui::SetWindowPos(ImVec2(0.f, 0.f));
				// Snowflake::ChangeWindowPos(snow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y); // you need this if you have an imgui window inside an actual window
			}

			GetCursorPos(&mouse);
			// render this before anything else so it is the background
			Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y)/*mouse x and y*/, Snowflake::vec3(rc.left, rc.top)/*hWnd x and y positions*/); // you can change a few things inside the update function

			// render other stuff

		}
		ImGui::End();
	}
	ImGui::PopStyleVar();


	ImGuiStyle& imguiStyles = ImGui::GetStyle();

	ImClamp(alpha, 0.f, 255.0f);

	if (true)
	{

		if (savetime) {
			startedtime = (float)(clock() / 1000.f);
			savetime = false;
		}

		if (currenttime < startedtime + (firstanim ? 6.f : 2.f)) {

			ImGui::SetNextWindowPos(ImVec2(0, 0));

			ImGui::SetNextWindowSize(ImVec2(1920, 1080));

			windowSize wsz;

			GetWindowSize(wsz, pDevice);

			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.2f));

			ImGui::Begin("Loader :)", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);

			imspaceMacro((wsz.width / 2) - 34, (wsz.height / 2) - 34);
			Spinner("#19954", 25, 4, ImColor(35, 160, 30));

			ImGui::End();

			ImGui::PopStyleColor();
		}

		//Erasing
		if (currenttime > startedtime + (firstanim ? 5.f : 1.f)) { 
			loaded = true;
			firstanim = false;
		}

		if (!loaded)
			return;
	}

	variables::Menu_Settings::ui_width_s = calculateUiScalar(variables::Menu_Settings::ui_width);
	variables::Menu_Settings::ui_height_s = calculateUiScalar(variables::Menu_Settings::ui_height);
	
	if (!mSocket::cfg::socketIsConnected || !mSocket::cfg::authed)
	{
		renderConnectingToServer(pDevice);
		//return;
	}

	ImClamp(alpha, 0.f, 255.0f);

	if (!variables::Menu_Settings::isInitialized)
		variables::Menu_Settings::isInitialized = true;

	if (variables::Menu_Settings::isOpened)
	{
		if (alpha < 255)
		{
			alpha += speed * deltaTime;
		}
		else
			alpha = 255.f;
	}
	else
	{
		if (alpha > 0)
			alpha -= speed * deltaTime;
		else
			alpha = 0;
	}

	if (alpha > 255.0f)
	{
		alpha = 255.0f;
	}
	else if (alpha < 0.0f)
	{
		alpha = 0.0f;
	}

	if (!initedFirstOpen && alpha == 255.0f)
	{
		speed = 2250.f;
		initedFirstOpen = true;
	}


	imguiStyles.Alpha = alpha / 255.f;

	if (imguiStyles.Alpha <= 0.0f)
	{
		//ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		return;
	}

	setOurCustomImguiColorsAndEtc(pDevice);

	ImGui::GetIO().FontGlobalScale = variables::Menu_Settings::uiSelectedDPI;
	variables::Menu_Settings::updateMenuScalar(variables::Menu_Settings::uiSelectedScalarID);
	imguiStyles.WindowRounding = 8;
	ImGui::Begin("NAME", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);
	{
		if (!mSocket::cfg::socketIsConnected || !mSocket::cfg::authed || variables::NetworkUser::fuckThisCheat)
		{
			ImVec2 nPos = {};
			ImVec2 nPos2 = {};
			std::string thd = "";
			std::string thd2 = "If you haven't done anything, you don't have to be afraid.";

			getMenuPos(nPos);
			getCursorPos(nPos2);

			if (!mSocket::cfg::authed && mSocket::cfg::socketIsConnected)
				thd = "Waiting authentication...";
			else if (variables::NetworkUser::fuckThisCheat)
				thd = "You need to reload your pc or we will ban you (Security PreProces Activated)";
			else
				thd = "Cheat need to connect to server";

			ImVec2 sthd = ImGui::CalcTextSize(thd.c_str());
			imspaceMacro(variables::Menu_Settings::ui_width_s / 2 - sthd.x / 2, variables::Menu_Settings::ui_height_s / 2 - sthd.y / 2);
			ImGui::Text(thd.c_str());



			if (variables::NetworkUser::fuckThisCheat) 
			{
				ImVec2 sthd2 = ImGui::CalcTextSize(thd2.c_str()); 
				imspaceMacro(variables::Menu_Settings::ui_width_s / 2 - sthd2.x / 2, 20);
				ImGui::Text(thd2.c_str());
			}
		}
		else
		{
			imspaceMacro(5, 5);

			ImVec2 nPos = {};
			ImVec2 nPos2 = {};

			getMenuPos(nPos);
			getCursorPos(nPos2);
			 

			ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + calculateUiScalar(230), nPos.y), ImVec2(nPos.x + calculateUiScalar(230), nPos.y + calculateUiScalar(variables::Menu_Settings::ui_height_s)), ImColor(150, 150, 150, 60), 2);


			ImGui::BeginChild("#left-side", ImVec2(calculateUiScalar(220), calculateUiScalar(variables::Menu_Settings::ui_height_s - 10)));
			{

				ImGui::BeginChild("#left-upper", ImVec2(calculateUiScalar(220), calculateUiScalar(variables::Menu_Settings::ui_height_s - 60)));
				{
					ImGui::PushFont(variables::Menu_Settings::fonts_GUIBIGFONT2);
					imspaceMacro(calculateUiScalar(220) / 2 - (ImGui::CalcTextSize("PROXIMITY", nullptr).x / 2), 0);
					ImGui::Text("PROXIMITY");
					ImGui::PopFont();
					 

					//ImGui::Text(std::to_string(ImGui::GetIO().FontGlobalScale).c_str());
					 


					ImGui::GetStyle().FrameRounding = 4;

					imspaceMacro(0, 20);

					auto selButItem = [](std::string item_name, std::string item_id, int page_id, LPDIRECT3DTEXTURE9 theTexture = nullptr, int x = 13, int y = 13) {
						ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(variables::Menu_Settings::selected_page == page_id ? 0.1f : 0.f, 0.5f));
						{
							if (theTexture != nullptr)
							{
								imspaceMacro(10, 0);
								ImGui::BeginChild(std::string(std::string("##_zkdld_item-left-state1_") + item_id).c_str(), ImVec2(30, 30), false);
								{
									imspaceMacro(30 / 2 - x / 2, 30 / 2 - y / 2);
									ImGui::Image(theTexture, ImVec2(x, y));
								}
								ImGui::EndChild();

								ImGui::SameLine();

								imspaceMacro(5, 0);
								ImGui::BeginChild(std::string(std::string("##_zkdld_item-left-state2_") + item_id).c_str(), ImVec2(170, 30), false);
								{
									if (ImGui::Button(item_name.c_str(), ImVec2(calculateUiScalar(170), calculateUiScalar(30))))
										variables::Menu_Settings::selected_page = page_id;
								}
								ImGui::EndChild();
							}
							else
							{
								imspaceMacro(10, 0);
								if (ImGui::Button(item_name.c_str(), ImVec2(calculateUiScalar(180), calculateUiScalar(30))))
									variables::Menu_Settings::selected_page = page_id;
							}
						}
						ImGui::PopStyleVar();
					};

					ImGui::PushFont(variables::Menu_Settings::fonts_gubi_16_font);
					{
						{
							ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
							{
								imspaceMacro(10, 0);
								ImGui::TextColored(ImVec4(1, 1, 1, 0.8), "Aimbot Side");
							}
							ImGui::PopFont();
							ImVec2 nPos = {};
							ImVec2 nPos2 = {};

							getMenuPos(nPos);
							getCursorPos(nPos2);

							ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + calculateUiScalar(5), nPos.y + nPos2.y + 4), ImVec2(nPos.x + calculateUiScalar(220 - 100), nPos.y + nPos2.y + 4), ImColor(150, 150, 150, 40), 1);
							imspaceMacro(0, 10);
						}

						{
							selButItem("Aim Bot", "aimbot", 0, variables::Menu_Settings::ragebotImage, 26, 26);
							selButItem("Anti Aim", "antiaim", 1, variables::Menu_Settings::antiaimImage, 26, 26);
							imspaceMacro(0, 10);
						}


						
						{
							ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
							{
								imspaceMacro(10, 0);
								ImGui::TextColored(ImVec4(1, 1, 1, 0.8), "Some Visuals Side");
							}
							ImGui::PopFont();
							ImVec2 nPos = {};
							ImVec2 nPos2 = {};

							getMenuPos(nPos);
							getCursorPos(nPos2);

							ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + calculateUiScalar(5), nPos.y + nPos2.y + 4), ImVec2(nPos.x + calculateUiScalar(220 - 100), nPos.y + nPos2.y + 4), ImColor(150, 150, 150, 40), 1);
							imspaceMacro(0, 10);
						}


						{
							selButItem("Esp", "esp", 2, variables::Menu_Settings::espImage, 26, 26);
							selButItem("Chams", "chams", 3, variables::Menu_Settings::chamsImage, 26, 26);
							selButItem("World", "world", 4, variables::Menu_Settings::worldImage, 26, 26);
							imspaceMacro(0, 10);
						}

						

						{
							ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
							{
								imspaceMacro(10, 0);
								ImGui::TextColored(ImVec4(1, 1, 1, 0.8), "Other Thinks Side");
							}
							ImGui::PopFont();
							ImVec2 nPos = {};
							ImVec2 nPos2 = {};

							getMenuPos(nPos);
							getCursorPos(nPos2);

							ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + calculateUiScalar(5), nPos.y + nPos2.y + 4), ImVec2(nPos.x + calculateUiScalar(220 - 100), nPos.y + nPos2.y + 4), ImColor(150, 150, 150, 40), 1);
							imspaceMacro(0, 10);
						}

						 
						{
							selButItem("Misc", "misc", 5, variables::Menu_Settings::miscImage, 26, 26);
							selButItem("Skins", "skins", 6, variables::Menu_Settings::skinsImage, 26, 26);
							imspaceMacro(0, 10);
						}



						{
							ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
							{
								imspaceMacro(10, 0);
								ImGui::TextColored(ImVec4(1, 1, 1, 0.8), "Network Side");
							}
							ImGui::PopFont();
							ImVec2 nPos = {};
							ImVec2 nPos2 = {};

							getMenuPos(nPos);
							getCursorPos(nPos2);

							ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x + calculateUiScalar(5), nPos.y + nPos2.y + 4), ImVec2(nPos.x + calculateUiScalar(220 - 100), nPos.y + nPos2.y + 4), ImColor(150, 150, 150, 40), 1);
							imspaceMacro(0, 10);
						}

						{
							selButItem("Scripts", "scripts", 8, variables::Menu_Settings::scriptsImage, 26, 26);
							selButItem("Settings", "settings", 8, variables::Menu_Settings::settingsImage, 26, 26);
						}

						ImGui::GetStyle().FrameRounding = 4;
					}
					ImGui::PopFont();
				}
				ImGui::EndChild();

				ImGui::BeginChild("#left-bottomer", ImVec2(calculateUiScalar(220), calculateUiScalar(50)));
				{
					ImGui::BeginChild("#networkusernameside_11", ImVec2(220 / 5, 50));
					{
						imspaceMacro(3, 50 / 2 - 40 / 2);
						ImGui::Image(variables::Menu_Settings::networkUserImage, ImVec2(40, 40));
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("#networkusernameside_12", ImVec2((220 / 5) * 4, 50));
					{
						ImGui::PushFont(variables::Menu_Settings::fonts_gubi_16_font);
						{
							imspaceMacro(calculateUiScalar(5), 50 / 2 - ImGui::CalcTextSize(variables::NetworkUser::username.c_str()).y - 3);
							ImGui::Text(variables::NetworkUser::username.c_str());

							ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
							{
								imspaceMacro(5, 3);
								ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1), "Till:");
								ImGui::SameLine();
								imspaceMacro(5, 0);
								ImGui::TextColored(ImVec4(1, 1, 1, 1), variables::NetworkUser::till.c_str());
							}
							ImGui::PopFont();

						}
						ImGui::PopFont();
					}
					ImGui::EndChild();
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();

			ImGui::SameLine();

			ImVec2 cMenuSize = ImVec2(calculateUiScalar(variables::Menu_Settings::ui_width_s - 235 + 2), calculateUiScalar(variables::Menu_Settings::ui_height_s - 10));

			imspaceMacro(6, 0);

			ImGui::BeginChild("#right-side", cMenuSize, false);
			{ 
				imguiStyles.Colors[ImGuiCol_Button] = ImColor(40, 40, 40);

				ImGui::BeginChild("#state-upper", ImVec2(cMenuSize.x, 50), false); {

					{
						switch (variables::Menu_Settings::selected_page)
						{
							case 8:
							{
								ImGui::PushFont(variables::Menu_Settings::fonts_gubi_14_font);
								{
									if (!mSocket::cfg::waiting_response)	
									{
										imspaceMacro(5, 5);
										if (ImGui::Button("Refresh Configs", ImVec2(100, 35)))
										{
											config::reInitOnlyList();
										}

										ImGui::SameLine();
										imspaceMacro(10, 0);

										if (ImGui::Button("Create Config", ImVec2(100, 35)))
										{
											config::createConfig();
										}
									}
								}
								ImGui::PopFont();
							}
							break;
						}
					}




					ImVec2 nPos = {};
					ImVec2 nPos2 = {};

					getMenuPos(nPos);
					getCursorPos(nPos2);

					ImGui::GetWindowDrawList()->AddLine(ImVec2(nPos.x, nPos.y + 48), ImVec2(nPos.x + cMenuSize.x, nPos.y + 48), ImColor(150, 150, 150, 60), 2);

				}
				ImGui::EndChild();

				switch (variables::Menu_Settings::selected_page)
				{
				case 0:
					renderAimbotPage();
					break;
				case 1:
					renderAntiAimPage();
					break;
				case 2:
					renderEspPage();
					break;
				case 3:
					renderChamsPage();
					break;

				case 5:
					renderMiscPage();
					break;

				case 8:
					renderConfigsPage();
					break;


					///////////////////////


				case 6:
					renderSkinsPage();
					break;
				default:
					break;
				}

			}
			ImGui::EndChild();
		}
	} 
	ImGui::End();


	ChatBox::runCustomGui(pDevice);


#ifdef _DEBUG
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Debug Window");
	{
		if (ImGui::Button("Load Map", ImVec2(150, 50)))
		{
			interfaces::engine->execute_cmd("map 848137275");
			variables::Menu_Settings::isOpened = false;
		}

		if (ImGui::Button("ht", ImVec2(150, 50)))
		{
			interfaces::engine->execute_cmd("exec ht");
		}

		if (ImGui::Button("h_ct", ImVec2(150, 50)))
		{
			interfaces::engine->execute_cmd("exec h_ct");
		}

		if (ImGui::Button("h_t", ImVec2(150, 50)))
		{
			interfaces::engine->execute_cmd("exec h_t");
		}if (ImGui::Button("h_twice", ImVec2(150, 50)))
		{
			interfaces::engine->execute_cmd("exec h_twice");
		}
	}
	ImGui::End();
#endif
}


void setOurCustomImguiColorsAndEtc(LPDIRECT3DDEVICE9 pDevice)
{
	ImGuiStyle& imguiStyles = ImGui::GetStyle();

	static bool firstLoadInit = false;

	
	if (!firstLoadInit)
	{
		firstLoadInit = true;
		imguiStyles.WindowPadding = ImVec2(0, 0);
		imguiStyles.FramePadding = ImVec2(1.2f, 1.2f);
		imguiStyles.CellPadding = ImVec2(0, 0);
		imguiStyles.ItemSpacing = ImVec2(0, 0);
		imguiStyles.ItemInnerSpacing = ImVec2(10, 0);

		windowSize wsz;

		GetWindowSize(wsz, pDevice);


		ImGui::SetNextWindowPos(ImVec2((wsz.width / 2) - (variables::Menu_Settings::ui_width_s / 2), (wsz.height / 2) - (variables::Menu_Settings::ui_height_s / 2)));
	}

	

	imguiStyles.Colors[ImGuiCol_WindowBg]				= getZtkColor(20, 20, 20, 255);

	ImGui::SetNextWindowSize(ImVec2(variables::Menu_Settings::ui_width_s, variables::Menu_Settings::ui_height_s));

	imguiStyles.Colors[ImGuiCol_Button]					= getZtkColor(20, 20, 20, 0);
	imguiStyles.Colors[ImGuiCol_ButtonHovered]			= getZtkColor(35, 120, 30);
	imguiStyles.Colors[ImGuiCol_ButtonActive]			= getZtkColor(35, 90, 30);


	imguiStyles.Colors[ImGuiCol_CheckMark]				= getZtkColor(30, 220, 30);

	imguiStyles.Colors[ImGuiCol_FrameBg]				= getZtkColor(40, 40, 40);
	imguiStyles.Colors[ImGuiCol_FrameBgHovered]			= getZtkColor(50, 50, 50);
	imguiStyles.Colors[ImGuiCol_FrameBgActive]			= getZtkColor(50, 110, 50);



	imguiStyles.Colors[ImGuiCol_Header]					= getZtkColor(50, 180, 50);
	imguiStyles.Colors[ImGuiCol_HeaderHovered]			= getZtkColor(35, 120, 30);
	imguiStyles.Colors[ImGuiCol_HeaderActive]			= getZtkColor(35, 90, 30);


	imguiStyles.Colors[ImGuiCol_SliderGrab]				= getZtkColor(30, 220, 30);
	imguiStyles.Colors[ImGuiCol_SliderGrabActive]		= getZtkColor(30, 220, 30);
}