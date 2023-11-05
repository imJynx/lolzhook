#pragma once
#include "Components/MenuConfig.hpp"
#include "Components/Valve/Render.hpp"
#include "Font\IconsFontAwesome5.h"
#include "Features/AimBot.hpp"
#include "Features/Radar.h"
#include "Features/TriggerBot.h"
#include "Components/ConfigMenu.hpp"
#include "Components/ScriptMenu.hpp"
#include "Components/ConfigSaver.hpp"

namespace GUI
{
	void RenderMenu()
	{
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowRounding = 20.0f;
		Style->Colors[ImGuiCol_WindowBg] = ImColor(17, 18, 54);
		constexpr auto windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
		if (ImGui::Begin("ofmain", NULL, windowFlags))
		{
			static int MenuTab = 0;
			Style->Colors[ImGuiCol_ChildBg] = ImColor(24, 26, 74);
			ImGui::BeginChild("##HEADER", ImVec2{ 650, 75 }, false);
			{
				ImGui::SetCursorPos(ImVec2{ 290, 20 });
				Style->Colors[ImGuiCol_Text] = ImColor(0, 255, 255);
				ImGui::Text("LolzHook");
				Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				ImGui::SetCursorPos(ImVec2{ 280, 40 });
				ImGui::Text("Stable, V1.5.0");
				ImGui::EndChild();
			}

			Style->Colors[ImGuiCol_ChildBg] = ImColor(17, 18, 54);
			ImGui::SetCursorPos(ImVec2{ 7.5, 95 });
			ImGui::BeginChild("##CONTENT", ImVec2{ 650, 490 }, false);
			{
				if (MenuTab == 0)
				{
					ImGui::Checkbox("Enable Aimbot", &MenuConfig::AimBot);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(75.f);
					if (ImGui::Combo("Hotkey", &MenuConfig::AimBotHotKey, "LALT\0LBUTTON\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL")) AimControl::SetHotKey(MenuConfig::AimBotHotKey);
					ImGui::Checkbox("Draw Fov", &ESPConfig::DrawFov);
					ImGui::SameLine();
					ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::FovCircleColor), ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Disable Invisible", &MenuConfig::VisibleCheck);
					ImGui::Checkbox("Disable InAir", &MenuConfig::AirJump);

					float FovMin = 0.1f, FovMax = 89.f;
					float SmoothMin = 0.1f, SmoothMax = 1.f;
					ImGui::SliderFloat("Fov", &AimControl::AimFov, 0.0f, 25.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
					ImGui::SliderFloat("Smooth", &AimControl::Smooth, 0.0f, 1.0f, "%.1f");
					if (ImGui::Combo("Bone", &MenuConfig::AimPosition, "Head\0Neck\0Chest\0Penis"))
					{
						switch (MenuConfig::AimPosition)
						{
						case 0:
							MenuConfig::AimPositionIndex = BONEINDEX::head;
							break;
						case 1:
							MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
							break;
						case 2:
							MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
							break;
						case 3:
							MenuConfig::AimPositionIndex = BONEINDEX::pelvis;
							break;
						default:
							break;
						}
					}
				}
				else if (MenuTab == 1)
				{
					ImGui::Checkbox("Enable Triggerbot", &MenuConfig::TriggerBot);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
					if (ImGui::Combo("Hotkey", &MenuConfig::TriggerHotKey, "LALT\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL")) TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
					ImGui::Checkbox("Always Active", &MenuConfig::TriggerAlways);
					DWORD TriggerDelayMin = 10, TriggerDelayMax = 300;
					ImGui::SliderInt("Delay", &TriggerBot::TriggerDelay, TriggerDelayMin, TriggerDelayMax, "%d ms", ImGuiSliderFlags_None);
					ImGui::SliderInt("Fake Shot", &TriggerBot::FakeShotDelay, 0, 1000, "%d ms", ImGuiSliderFlags_None);
				}
				else if (MenuTab == 2)
				{
					ImGui::Checkbox("Enable Glow(VAC)", &MenuConfig::Glow);
					ImGui::Checkbox("Enable ESP", &ESPConfig::ESPenbled);
					ImGui::Checkbox("Box", &ESPConfig::ShowBoxESP);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&ESPConfig::BoxColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Skeleton", &ESPConfig::ShowBoneESP);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&ESPConfig::BoneColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Head Box", &ESPConfig::ShowHeadBox);
					ImGui::SameLine();
					ImGui::ColorEdit4("##HeadBoxColor", reinterpret_cast<float*>(&ESPConfig::HeadBoxColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Eye Ray", &ESPConfig::ShowEyeRay);
					ImGui::SameLine();
					ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&ESPConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Health Bar", &ESPConfig::ShowHealthBar);
					ImGui::Checkbox("Weapon Name", &ESPConfig::ShowWeaponESP);
					ImGui::Checkbox("Distance", &ESPConfig::ShowDistance);
					ImGui::Checkbox("Player Name", &ESPConfig::ShowPlayerName);

					ImGui::Checkbox("SnapLine", &MenuConfig::ShowLineToEnemy);
					ImGui::SameLine();
					ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Visible Check", &ESPConfig::VisibleCheck);
					ImGui::SameLine();
					ImGui::ColorEdit4("##EspVisCol", reinterpret_cast<float*>(&ESPConfig::VisibleColor), ImGuiColorEditFlags_NoInputs);
					//ImGui::Checkbox("Preview Window", &ESPConfig::ShowPreview); ITS CRASHING MENU
				}
				else if (MenuTab == 3)
				{
					ImGui::Checkbox("Headshot Line", &MenuConfig::ShowHeadShootLine);
					ImGui::Checkbox("Work in Spectator", &MenuConfig::WorkInSpec);
					ImGui::Checkbox("No Flash(VAC)", &MenuConfig::NoFlash);
					ImGui::Checkbox("Watermark", &MenuConfig::WaterMark);
					ImGui::Checkbox("Cheat List", &MenuConfig::CheatList);
					ImGui::Checkbox("Hit Sound", &MenuConfig::HitSound);
					ImGui::Checkbox("Bomb Timer", &MenuConfig::bmbTimer);
					ImGui::Checkbox("Bunny Hop(VAC)", &MenuConfig::BunnyHop);
					ImGui::Checkbox("Team Check", &MenuConfig::TeamCheck);
					ImGui::Checkbox("Bypass OBS(ESP ISSUES)", &MenuConfig::BypassOBS);
					ImGui::Checkbox("Radar(VAC)", &MenuConfig::ShowRadar);
				}
				else if (MenuTab == 4)
				{
					ConfigMenu::RenderConfigMenu();
				}
				else if (MenuTab == 5)
				{
					ScriptMenu::Render();
				}

				ImGui::EndChild();
			}

			Style->Colors[ImGuiCol_ChildBg] = ImColor(24, 26, 74);
			Style->Colors[ImGuiCol_Button] = ImColor(24, 26, 74);
			Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 255, 255);
			Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 255, 255);
			ImGui::SetCursorPos(ImVec2{ 7.5, 600 });
			ImGui::BeginChild("##FOOTER", ImVec2{ 650, 75 }, false);
			{
				ImGui::SetCursorPos(ImVec2{ 115, 0 });
				if (ImGui::Button(ICON_FA_USER_CIRCLE, ImVec2(70, 70))) {
					MenuTab = 0;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Aimbot");
				}
				ImGui::SameLine();

				ImGui::SetCursorPos(ImVec2{ 185, 0 });
				if (ImGui::Button(ICON_FA_HAND_POINTER, ImVec2(70, 70))) {
					MenuTab = 1;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Triggerbot");
				}
				ImGui::SameLine();

				ImGui::SetCursorPos(ImVec2{ 255, 0 });
				if (ImGui::Button(ICON_FA_EYE, ImVec2(70, 70))) {
					MenuTab = 2;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Visual");
				}
				ImGui::SameLine();

				ImGui::SetCursorPos(ImVec2{ 325, 0 });
				if (ImGui::Button(ICON_FA_SUN, ImVec2(70, 70))) {
					MenuTab = 3;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Miscellaneous");
				}
				ImGui::SameLine();

				ImGui::SetCursorPos(ImVec2{ 395, 0 });
				if (ImGui::Button(ICON_FA_FOLDER_OPEN, ImVec2(70, 70))) {
					MenuTab = 4;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Configs");
				}
				ImGui::SameLine();

				ImGui::SetCursorPos(ImVec2{ 465, 0 });
				if (ImGui::Button(ICON_FA_FILE, ImVec2(70, 70))) {
					MenuTab = 5;
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip("Scripts");
				}
				ImGui::SameLine();
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}
}