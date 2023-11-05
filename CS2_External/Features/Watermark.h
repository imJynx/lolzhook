#pragma once
#include <time.h>

#include "..\OS-ImGui\imgui\imgui.h"
#include "../Components/MenuConfig.hpp"
#include "../Components/GlobalVars.h"

namespace Watermark
{
	static inline void getCurrentTime(struct tm* ptm) {
		time_t now = time(NULL);
		localtime_s(ptm, &now);
	}

	inline void Render() noexcept
	{
		if (!MenuConfig::WaterMark)
			return;

//		globalvars GV;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("Watermark", nullptr, windowFlags);

		static auto FrameRate = 1.0f;
		struct tm ptm;
//		FrameRate = 0.9f * FrameRate + 0.1f * GV.GetFrameCount();
		FrameRate = ImGui::GetIO().Framerate;
		getCurrentTime(&ptm);

		ImGui::Text("Lolz");
		ImGui::Text("%d fps", FrameRate != 0.0f ? static_cast<int>(FrameRate) : 0);
		ImGui::Text("%d:%d:%d", ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
		ImGui::End();
	}
}