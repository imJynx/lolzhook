#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ScriptManager.hpp"
#include "MenuConfig.hpp"
#include "../Features/TriggerBot.h"
#include "../Features/AimBot.hpp"

namespace ScriptMan {
    void LoadScript(const std::string& filename) {
        std::ifstream configFile(MenuConfig::ConfigPath + '\\' + filename);
        if (!configFile.is_open()) {
            std::cerr << "[Script] Couldn't open: " + filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (iss >> key) {
                //CATEGORY: GLOW
                if (key == "lolz.glow.Glow.enable") iss >> MenuConfig::Glow;
                else if (key == "lolz.glow.GlowColor") iss >> MenuConfig::GlowColor.Value.x >> MenuConfig::GlowColor.Value.y >> MenuConfig::GlowColor.Value.z >> MenuConfig::GlowColor.Value.w;
                //CATEGORY: ESP
                else if (key == "lolz.esp.ESP.enable") iss >> ESPConfig::ESPenbled;
                else if (key == "lolz.esp.Box.enable") iss >> ESPConfig::ShowBoxESP;
                else if (key == "lolz.esp.BoxAlpha") iss >> ESPConfig::BoxAlpha;
                else if (key == "lolz.esp.BoxRounding") iss >> ESPConfig::BoxRounding;
                else if (key == "lolz.esp.Bone.enable") iss >> ESPConfig::ShowBoneESP;
                else if (key == "lolz.esp.BoneColor") iss >> ESPConfig::BoneColor.Value.x >> ESPConfig::BoneColor.Value.y >> ESPConfig::BoneColor.Value.z >> ESPConfig::BoneColor.Value.w;
                else if (key == "lolz.esp.Distance.enable") iss >> ESPConfig::ShowDistance;
                else if (key == "lolz.esp.VisibleCheck.enable") iss >> ESPConfig::VisibleCheck;
                else if (key == "lolz.esp.VisibleColor") iss >> ESPConfig::VisibleColor.Value.x >> ESPConfig::VisibleColor.Value.y >> ESPConfig::VisibleColor.Value.z >> ESPConfig::VisibleColor.Value.w;
                else if (key == "lolz.esp.HeadBox.enable") iss >> ESPConfig::ShowHeadBox;
                else if (key == "lolz.esp.HeadBoxStyle") iss >> ESPConfig::HeadBoxStyle;
                else if (key == "lolz.esp.HeadBoxColor") iss >> ESPConfig::HeadBoxColor.Value.x >> ESPConfig::HeadBoxColor.Value.y >> ESPConfig::HeadBoxColor.Value.z >> ESPConfig::HeadBoxColor.Value.w;
                else if (key == "lolz.esp.HealthBar.enable") iss >> ESPConfig::ShowHealthBar;
                else if (key == "lolz.esp.HealthBarStyle") iss >> MenuConfig::HealthBarType;
                else if (key == "lolz.esp.LineToEnemy.enable") iss >> MenuConfig::ShowLineToEnemy;
                else if (key == "lolz.esp.Weapon.enable") iss >> ESPConfig::ShowWeaponESP;
                else if (key == "lolz.esp.EyeRay.enable") iss >> ESPConfig::ShowEyeRay;
                else if (key == "lolz.esp.PlayerName.enable") iss >> ESPConfig::ShowPlayerName;


                //else if (key == "AirJump") iss >> MenuConfig::AirJump;
                //else if (key == "TriggerDelay") iss >> TriggerBot::TriggerDelay;
                //else if (key == "FakeShot") iss >> TriggerBot::FakeShotDelay;
                //else if (key == "TriggerHotKey") { iss >> MenuConfig::TriggerHotKey; TriggerBot::SetHotKey(MenuConfig::TriggerHotKey); }
                //else if (key == "RCSBullet") iss >> AimControl::RCSBullet;
                //else if (key == "AimFov") iss >> AimControl::AimFov;
                //else if (key == "FovLineSize") iss >> MenuConfig::FovLineSize;
                //else if (key == "AimBotHotKey") { iss >> MenuConfig::AimBotHotKey; AimControl::SetHotKey(MenuConfig::AimBotHotKey); }
                //else if (key == "RCSScale.x") iss >> AimControl::RCSScale.x;
                //else if (key == "RCSScale.y") iss >> AimControl::RCSScale.y;
                //else if (key == "Smooth") iss >> AimControl::Smooth;
                //else if (key == "ShowFovLine") iss >> MenuConfig::ShowFovLine;
                //else if (key == "AimBot") iss >> MenuConfig::AimBot;
                //else if (key == "AimAlways") iss >> MenuConfig::AimAlways;
                //else if (key == "AimToggle") iss >> MenuConfig::AimToggleMode;
                //else if (key == "AimPosition") iss >> MenuConfig::AimPosition;
                //else if (key == "AimPositionIndex") iss >> MenuConfig::AimPositionIndex;
                //else if (key == "FovLineColor") iss >> MenuConfig::FovLineColor.Value.x >> MenuConfig::FovLineColor.Value.y >> MenuConfig::FovLineColor.Value.z >> MenuConfig::FovLineColor.Value.w;
                //else if (key == "LineToEnemyColor") iss >> MenuConfig::LineToEnemyColor.Value.x >> MenuConfig::LineToEnemyColor.Value.y >> MenuConfig::LineToEnemyColor.Value.z >> MenuConfig::LineToEnemyColor.Value.w;
                //else if (key == "BoxColor") iss >> ESPConfig::BoxColor.Value.x >> ESPConfig::BoxColor.Value.y >> ESPConfig::BoxColor.Value.z >> ESPConfig::BoxColor.Value.w;
                //else if (key == "EyeRayColor") iss >> ESPConfig::EyeRayColor.Value.x >> ESPConfig::EyeRayColor.Value.y >> ESPConfig::EyeRayColor.Value.z >> ESPConfig::EyeRayColor.Value.w;
                //else if (key == "CrossLineColor") iss >> MenuConfig::RadarCrossLineColor.Value.x >> MenuConfig::RadarCrossLineColor.Value.y >> MenuConfig::RadarCrossLineColor.Value.z >> MenuConfig::RadarCrossLineColor.Value.w;
                //else if (key == "HeadShootLineColor") iss >> MenuConfig::HeadShootLineColor.Value.x >> MenuConfig::HeadShootLineColor.Value.y >> MenuConfig::HeadShootLineColor.Value.z >> MenuConfig::HeadShootLineColor.Value.w;
                //else if (key == "ShowMenu") iss >> MenuConfig::ShowMenu;
                //else if (key == "ShowRadar") iss >> MenuConfig::ShowRadar;
                //else if (key == "RadarRange") iss >> MenuConfig::RadarRange;
                //else if (key == "RadarPointSizeProportion") iss >> MenuConfig::RadarPointSizeProportion;
                //else if (key == "RadarBgAlpha") iss >> MenuConfig::RadarBgAlpha;
                //else if (key == "ShowCrossLine") iss >> MenuConfig::ShowRadarCrossLine;
                //else if (key == "RadarType") iss >> MenuConfig::RadarType;
                //else if (key == "Proportion") iss >> MenuConfig::Proportion;
                //else if (key == "BoxType") iss >> MenuConfig::BoxType;
                //else if (key == "TriggerBot") iss >> MenuConfig::TriggerBot;
                //else if (key == "TriggerAlways") iss >> MenuConfig::TriggerAlways;
                //else if (key == "TeamCheck") iss >> MenuConfig::TeamCheck;
                //else if (key == "BypassOBS") iss >> MenuConfig::BypassOBS;
                //else if (key == "VisibleCheck") iss >> MenuConfig::VisibleCheck;
                //else if (key == "ShowHeadShootLine") iss >> MenuConfig::ShowHeadShootLine;
                //else if (key == "ShowCrossHair") iss >> CrosshairConfig::ShowCrossHair;
                //else if (key == "CrossHairColor") iss >> CrosshairConfig::CrossHairColor.Value.x >> CrosshairConfig::CrossHairColor.Value.y >> CrosshairConfig::CrossHairColor.Value.z >> CrosshairConfig::CrossHairColor.Value.w;
                //else if (key == "CrossHairSize") iss >> CrosshairConfig::CrossHairSize;
                //else if (key == "drawDot") iss >> CrosshairConfig::drawDot;
                //else if (key == "tStyle") iss >> CrosshairConfig::tStyle;
                //else if (key == "HorizontalLength") iss >> CrosshairConfig::HorizontalLength;
                //else if (key == "VerticalLength") iss >> CrosshairConfig::VerticalLength;
                //else if (key == "drawOutLine") iss >> CrosshairConfig::drawOutLine;
                //else if (key == "Gap") iss >> CrosshairConfig::Gap;
                //else if (key == "drawCrossline") iss >> CrosshairConfig::drawCrossline;
                //else if (key == "drawCircle") iss >> CrosshairConfig::drawCircle;
                //else if (key == "showTargeting") iss >> CrosshairConfig::showTargeting;
                //else if (key == "CircleRadius") iss >> CrosshairConfig::CircleRadius;
                //else if (key == "TargetedColor") iss >> CrosshairConfig::TargetedColor.Value.x >> CrosshairConfig::TargetedColor.Value.y >> CrosshairConfig::TargetedColor.Value.z >> CrosshairConfig::TargetedColor.Value.w;
                //else if (key == "DynamicGap") iss >> CrosshairConfig::DynamicGap;
                //else if (key == "DotSize") iss >> CrosshairConfig::DotSize;
                //else if (key == "CrosshairsThickness") iss >> CrosshairConfig::Thickness;
                //else if (key == "CrosshairsTeamCheck") iss >> CrosshairConfig::TeamCheck;

                //else if (key == "BunnyHop") iss >> MenuConfig::BunnyHop;
                //else if (key == "WorkInSpec") iss >> MenuConfig::WorkInSpec;
                //else if (key == "NoFlash") iss >> MenuConfig::NoFlash;
                //else if (key == "WaterMark") iss >> MenuConfig::WaterMark;
                //else if (key == "CheatList") iss >> MenuConfig::CheatList;
                //else if (key == "HitSound") iss >> MenuConfig::HitSound;


                //else if (key == "DrawFov") iss >> ESPConfig::DrawFov;
                //else if (key == "FovColor") iss >> MenuConfig::FovCircleColor.Value.x >> MenuConfig::FovCircleColor.Value.y >> MenuConfig::FovCircleColor.Value.z >> MenuConfig::FovCircleColor.Value.w;
                //else if (key == "SnaplinePos") iss >> MenuConfig::LinePos;
                //else if (key == "CustomRadar") iss >> MenuConfig::customRadar;

            }
        }

        configFile.close();
        std::cout << "[Script] Loaded from " << MenuConfig::ConfigPath + '\\' + filename << std::endl;
    }
}