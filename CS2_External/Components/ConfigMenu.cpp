#include "ConfigMenu.hpp"
#include "MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../Features/TriggerBot.h"
#include "../Features/AimBot.hpp"
#include <filesystem>
#include <string>
#include "../Font/IconsFontAwesome5.h"

namespace ConfigMenu {
	void RenderConfigMenu() {
		static char configNameBuffer[128] = "NewConfig";
		static int selectedConfig = -1;
		const std::string configDir = MenuConfig::ConfigPath;
		static std::vector<std::string> configFiles;
		std::vector<const char*> configFilesCStr;
		configFiles.clear();
		for (const auto& entry : std::filesystem::directory_iterator(configDir))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".ofc")
			{
				configFiles.push_back(entry.path().filename().string());
			}
		}
		for (const auto& file : configFiles)
		{
			configFilesCStr.push_back(file.c_str());
		}

		ImGui::PushItemWidth(160.0f);
		ImGui::ListBox("##ConfigFiles", &selectedConfig, configFilesCStr.data(), configFilesCStr.size());
		ImGui::SameLine();
		ImGui::InputText(" ", configNameBuffer, sizeof(configNameBuffer));
		ImGui::SameLine();
		if (ImGui::Button("Create"))
		{
			std::string configFileName = std::string(configNameBuffer) + ".ofc";
			MyConfigSaver::SaveConfig(configFileName);
		}
		if (ImGui::Button("Load") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::LoadConfig(selectedConfigFile);
		}
		ImGui::SameLine();
		if (ImGui::Button("Save") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::SaveConfig(selectedConfigFile);
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete") && selectedConfig >= 0 && selectedConfig < configFiles.size()) ImGui::OpenPopup("##reallyDelete");
			if (ImGui::BeginPopup("##reallyDelete"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					// Delete
					std::string selectedConfigFile = configFiles[selectedConfig];
					std::string fullPath = configDir + "\\" + selectedConfigFile;
					if (std::remove(fullPath.c_str()) == 0)
					{
						configFiles.erase(configFiles.begin() + selectedConfig);
						selectedConfig = -1;
					}
					else
					{
					}
					ImGui::CloseCurrentPopup();
				}
			ImGui::EndPopup();
			}
		ImGui::SameLine();
		if (ImGui::Button("Reset")) ImGui::OpenPopup("##reallyReset");
			if (ImGui::BeginPopup("##reallyReset"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					ConfigMenu::ResetToDefault();
					ImGui::CloseCurrentPopup();
				}	
				ImGui::EndPopup();
			}
		if (ImGui::Button("Open Config Directory"))
		{
			Gui.OpenWebpage(configDir.c_str());
		}
	}
	void ResetToDefault() {
		ESPConfig::VisibleColor = ImColor(255, 196, 0, 255);
		ESPConfig::VisibleCheck = false;
		MenuConfig::GlowColor = ImColor(255, 0, 0, 100);;
		MenuConfig::Glow = false;
		MenuConfig::AirJump = false;
		ESPConfig::BoxAlpha = 0.0f;
		ESPConfig::ShowPreview = false;
		ESPConfig::ShowHeadBox = false;
		ESPConfig::HeadBoxStyle = 0;
		ESPConfig::HeadBoxColor = ImColor(255, 255, 255, 255);
		ESPConfig::ShowDistance = false;
		ESPConfig::ShowBoneESP = true;
		ESPConfig::ShowBoxESP = true;
		ESPConfig::ShowHealthBar = true;
		ESPConfig::ShowWeaponESP = false;
		ESPConfig::ShowEyeRay = false;
		ESPConfig::ShowPlayerName = true;
		ESPConfig::BoxRounding = 0.0f;
		MenuConfig::AimBot = false;
		MenuConfig::AimAlways = false;
		MenuConfig::AimToggleMode = false;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		ESPConfig::BoneColor = ImColor(0, 255, 255, 255);
		ESPConfig::BoxColor = ImColor(255, 80, 0, 255);
		ESPConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowRadar = false;
		MenuConfig::RadarRange = 150;
		MenuConfig::ShowRadarCrossLine = true;
		MenuConfig::RadarCrossLineColor = ImColor(220, 220, 220, 255);
		MenuConfig::RadarType = 2;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::RadarBgAlpha = 0.1f;
		MenuConfig::Proportion = 3300;
		MenuConfig::TriggerBot = false;
		MenuConfig::TriggerAlways = false;
		MenuConfig::TeamCheck = true;
		MenuConfig::BypassOBS = false;
		MenuConfig::VisibleCheck = true;
		MenuConfig::ShowHeadShootLine = false;
		MenuConfig::HeadShootLineColor = ImColor(255, 255, 255, 200);
		MenuConfig::AimBotHotKey = 0;
		AimControl::SetHotKey(MenuConfig::AimBotHotKey);
		MenuConfig::ShowLineToEnemy = false;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		TriggerBot::FakeShotDelay = 500;
		AimControl::RCSBullet = 1;
		MenuConfig::TriggerHotKey = 0;
		TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
		CrosshairConfig::ShowCrossHair = false;
		CrosshairConfig::CrossHairColor = ImColor(0, 255, 0, 255);
		CrosshairConfig::CrossHairSize = 75;
		CrosshairConfig::drawDot = true;
		CrosshairConfig::tStyle = false;
		CrosshairConfig::HorizontalLength = 6;
		CrosshairConfig::VerticalLength = 6;
		CrosshairConfig::drawOutLine = true;
		CrosshairConfig::Gap = 8;
		CrosshairConfig::drawCrossline = true;
		CrosshairConfig::drawCircle = false;
		CrosshairConfig::showTargeting = false;
		CrosshairConfig::TargetedColor = ImColor(255, 0, 0, 255);
		CrosshairConfig::CircleRadius = 3.f;
		CrosshairConfig::DynamicGap = false;
		CrosshairConfig::DotSize = 1.0f;
		CrosshairConfig::Thickness = 1;
		CrosshairConfig::TeamCheck = true;
		MenuConfig::BunnyHop = false;
		MenuConfig::WorkInSpec = true;
		MenuConfig::NoFlash = false;
		MenuConfig::WaterMark = false;
		MenuConfig::CheatList = false;
		MenuConfig::HitSound = false;

		ESPConfig::ESPenbled = false;

		ESPConfig::DrawFov = false;
		MenuConfig::FovCircleColor = ImColor(255, 255, 255, 255);
	}
}