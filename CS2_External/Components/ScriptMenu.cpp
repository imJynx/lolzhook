#include "ScriptMenu.hpp"
#include "MenuConfig.hpp"
#include "ScriptManager.hpp"
#include "../Features/TriggerBot.h"
#include "../Features/AimBot.hpp"
#include <filesystem>
#include <string>
#include "../Font/IconsFontAwesome5.h"

namespace ScriptMenu {
	void Render() {
			static int selectedScript = -1;
			const std::string scriptDir = MenuConfig::ScriptPath;
			static std::vector<std::string> scriptFiles;
			std::vector<const char*> scriptFilesCStr;
			scriptFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(scriptDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".ofs")
				{
					scriptFiles.push_back(entry.path().filename().string());
				}
			}
			for (const auto& file : scriptFiles)
			{
				scriptFilesCStr.push_back(file.c_str());
			}

			ImGui::PushItemWidth(160.0f);
			ImGui::ListBox("##ScrptFiles", &selectedScript, scriptFilesCStr.data(), scriptFilesCStr.size());
			if (ImGui::Button("Execute") && selectedScript >= 0 && selectedScript < scriptFiles.size())
			{
				std::string selectedScriptFile = scriptFiles[selectedScript];
				ScriptMan::LoadScript(selectedScriptFile);
			}
			if (ImGui::Button("Open Script Directory"))
			{
				Gui.OpenWebpage(scriptDir.c_str());
			}
	}
}
