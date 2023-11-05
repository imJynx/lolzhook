#pragma once
#include "Components/Valve/Game.h"
#include "Components/Valve/Entity.h"
#include "Features/AimBot.hpp"
#include "Features/Radar.h"
#include "Features/TriggerBot.h"
#include "Features/Bunnyhop.hpp"
#include "Features/NoFlash.h"
#include "Features/Watermark.h"
#include "Features/CheatList.h"
#include "Features/HitSound.h"
#include "Features/Glow.h"

namespace Cheats
{
	void KeyCheckThread();

	void RenderCrossHair(ImDrawList* drawList) noexcept;

	void RadarSetting(Base_Radar& Radar);
	void Run();
}

struct {
	ImFont* normal15px = nullptr;
} fonts;