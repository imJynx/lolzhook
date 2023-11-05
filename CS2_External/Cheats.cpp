﻿#include <string>
#include <thread>
#include <future>
#include <iostream>
#include "Cheats.h"
#include "Components/Valve/Render.hpp"
#include "Components/MenuConfig.hpp"
#include "Features/ESP.h"
#include "GUI.h"
#include "Features/BombTimer.h"

int PreviousTotalHits = 0;

// Does not work and not use it for now
void Cheats::KeyCheckThread()
{
	try
	{
		if ((GetAsyncKeyState(VK_INSERT) & 0x8000))
		{
			MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	// Radar window
	ImGui::SetNextWindowBgAlpha(MenuConfig::RadarBgAlpha);
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });

	if (!MenuConfig::customRadar)
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		MenuConfig::ShowRadarCrossLine = false;
		MenuConfig::Proportion = 3300.f;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::RadarRange = 150.f;
		MenuConfig::RadarBgAlpha = 0.1f;
	}


	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::RenderCrossHair(ImDrawList* drawList) noexcept
{
	if (!CrosshairConfig::ShowCrossHair)
		return;

	if (CrosshairConfig::isAim && CrosshairConfig::showTargeting)
		Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::TargetedColor));
	else
		Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::CrossHairColor));
}

void Cheats::Run()
{
	// Show menu
	static DWORD lastTick = 0;
	DWORD currentTick = GetTickCount();
	if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && currentTick - lastTick >= 150) {
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		lastTick = currentTick;
	}
	//	std::thread keyCheckThread(KeyCheckThread);
	//  std::future<void> Thread_PlayerESP = std::async(ESP::RenderPlayerESP, std::ref(Entity), std::ref(Rect));
	if (MenuConfig::ShowMenu)
	{
			GUI::RenderMenu();
			ESP::PreviewWindow();
	}


	// Update matrix
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	static int LocalPlayerControllerIndex = 1;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress) && !MenuConfig::WorkInSpec)
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		if (!Entity.IsAlive())
			continue;
		//		if (MenuConfig::VisibleCheck && (!Entity.Pawn.bSpottedByMask > 0))
		//			continue;


				// Add entity to radar
		if (MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/
		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;

			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		if (ESPConfig::ESPenbled)
		{
			ImVec4 Rect = ESP::GetBoxRect(Entity, MenuConfig::BoxType);
			ESP::RenderPlayerESP(LocalEntity, Entity, Rect, LocalPlayerControllerIndex, i);


			// Draw HealthBar
			if (ESPConfig::ShowHealthBar)
			{
				ImVec2 HealthBarPos, HealthBarSize;
				switch (MenuConfig::HealthBarType == 0)
				{
				case 0:
					HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
					HealthBarSize = { 70,8 };
					break;
				case 1:
					HealthBarPos = { Rect.x - 10.f,Rect.y };
					HealthBarSize = { 7 ,Rect.w };
					break;
				case 2:
					HealthBarPos = { Rect.x, Rect.y + Rect.w + 2 };
					HealthBarSize = { Rect.z, 4 };
					break;
				}
				Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
			}

			// Draw Distance
			Render::DrawDistance(LocalEntity, Entity, Rect);
		}
		Glow::Run(Entity);
	}

	// Radar render
	if (MenuConfig::ShowRadar)
	{
		Radar.Render();
		ImGui::End();
	}

	// TriggerBot
	if (MenuConfig::TriggerBot && (GetAsyncKeyState(TriggerBot::HotKey) || MenuConfig::TriggerAlways))
		TriggerBot::Run(LocalEntity);

	// HitSound
	HitSound::Run(LocalEntity, PreviousTotalHits);

	// WaterMark
	Watermark::Render();

	// Cheat List
	CheatList::Render();

	// Fov line
	Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// HeadShoot Line
	Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);

	// CrossHair
	TriggerBot::TargetCheck(LocalEntity);
	Bunnyhop::AirCheck(LocalEntity);
	RenderCrossHair(ImGui::GetBackgroundDrawList());

	// Bhop
	Bunnyhop::Run(LocalEntity);

	// No Flash
	NoFlash::Run(LocalEntity);

	bmb::RenderWindow();

	// Aimbot
	if (MenuConfig::AimBot)
	{
		Render::DrawFovCircle(LocalEntity);

		if (MenuConfig::AimAlways)
		{
			if (AimPos != Vec3(0, 0, 0))
			{
				AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
			}
		}
		else
		{
			if (GetAsyncKeyState(AimControl::HotKey))
			{
				if (AimPos != Vec3(0, 0, 0))
				{
					AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
				}
			}
		}

		if (MenuConfig::AimToggleMode && (GetAsyncKeyState(AimControl::HotKey) & 0x8000) && currentTick - lastTick >= 200)
		{
			AimControl::switchToggle();
			lastTick = currentTick;
		}


	}

}