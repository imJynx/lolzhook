#include "Components/Valve/Offsets.h"
#include "Cheats.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <filesystem>
#include <cstdlib>
#include <KnownFolders.h>
#include <ShlObj.h>

namespace fs = std::filesystem;
auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

int main()
{
	std::printf(
	"LolzHook | Straight out of github\n"
	"Counter-Strike: 2\n"
	"Stable, V1.3.0\n"
	"Menu Toggle: [INSERT]\n"
	);

	char documentsPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath) != S_OK) {
		std::cerr << "[Lolz] Failed to get Documents folder!" << std::endl;
		goto END;
	}
	if (!Offset::UpdateOffsets())
	{
		std::cout << "[Lolz] Failed to update offsets." << std::endl;
		goto END;
	}
	if (!gGame.InitAddress())
	{
		std::cout << "[Lolz] Failed to call InitAddress()." << std::endl;
		goto END;
	}
	switch (ProcessStatus) {
	case 1:
		std::cout << "[Lolz] Please launch the game on steam!" << std::endl;
		goto END;
	case 2: 
		std::cout << "[Lolz] Failed to hook process, please run the cheat in administrator." << std::endl; 
		goto END; 
	case 3:
		std::cout << "[Lolz] Failed to get module address, please disable antivirus or whitelist me!" << std::endl; 
		goto END; 
	default: 
		break;
	}

	MenuConfig::ConfigPath = documentsPath;
	MenuConfig::ConfigPath += "\\Lolz";
	if (fs::exists(MenuConfig::ConfigPath)) std::cout << "[Lolz] Finded regular config folder: " << MenuConfig::ConfigPath << std::endl;
	else
	{
		if (fs::create_directory(MenuConfig::ConfigPath))
			std::cout << "[Lolz] Created config folder: " << MenuConfig::ConfigPath << std::endl;
		else
		{
			std::cerr << "[Lolz] Couldn't create config folder!" << std::endl;
			goto END;
		}
	}

	MenuConfig::ConfigPath = documentsPath;
	MenuConfig::ConfigPath += "\\Lolz\\Configs";
	if (fs::exists(MenuConfig::ConfigPath)) std::cout << "[Lolz] Finded regular config folder: " << MenuConfig::ConfigPath << std::endl;
	else
	{
		if (fs::create_directory(MenuConfig::ConfigPath))
			std::cout << "[Lolz] Created config folder: " << MenuConfig::ConfigPath << std::endl;
		else
		{
			std::cerr << "[Lolz] Couldn't create config folder!" << std::endl;
			goto END;
		}
	}

	MenuConfig::ScriptPath = documentsPath;
	MenuConfig::ScriptPath += "\\Lolz\\Scripts";
	if (fs::exists(MenuConfig::ScriptPath)) std::cout << "[Lolz] Finded regular script folder: " << MenuConfig::ScriptPath << std::endl;
	else
	{
		if (fs::create_directory(MenuConfig::ScriptPath))
			std::cout << "[Lolz] Created script folder: " << MenuConfig::ScriptPath << std::endl;
		else
		{
			std::cerr << "[Lolz] Couldn't create script folder!" << std::endl;
			goto END;
		}
	}

	std::cout << std::endl;
	std::cout << "[Lolz] Cheat Running. Good Luck, Have Fun!" << std::endl;
	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		try
		{
			Gui.AttachAnotherWindow("[Lolz] Failed Attach to CS2 Process!", "SDL_app", Cheats::Run);
		}
		catch (OSImGui::OSException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

END:
	std::cout << std::endl;
	system("pause");
	return 0;
}