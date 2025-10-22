#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Drawing.h"
#include <algorithm>
#include <windows.h>
#include"Structures.h"
#include <tchar.h>

#include "font.hpp"
#include "custom.hpp"

ImVec4 clear_color = ImVec4(72 / 255.f, 79 / 255.f, 81 / 255.f, 1.00f);

void MenuWindow() {
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::Begin("menu", 0, ImGuiWindowFlags_NoDecoration);
	{
		ImGui::PopStyleVar();

		ImGuiWindow* window = ImGui::GetCurrentWindow();

		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 p = ImGui::GetWindowPos();

		ImGui::SetWindowSize({ 650, 450 });

		static bool navbar_collapsed = true;
		static float navbar_width = 0.f; navbar_width = ImLerp(navbar_width, navbar_collapsed ? 0.f : 1.f, 0.04f);
		content_anim = ImLerp(content_anim, 1.f, 0.04f);

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !navbar_collapsed);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, content_anim * (navbar_width > 0.005f ? 1 / navbar_width / 2 : 1.f));
		ImGui::SetCursorPos({ 81, 25 });
		ImGui::BeginGroup();
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
		ImGui::Text("rb6.store");
		ImGui::PopFont();

		ImGui::BeginChild("main", { window->Size.x - 81, window->Size.y - window->DC.CursorPos.y + window->Pos.y }, 0, ImGuiWindowFlags_NoBackground);
		{
			switch (tab) {
			case 0: {
				ImGui::BeginChild("subtabs", { ImGui::GetWindowWidth() - 30, 40 }, 1);
				{
					ImGui::SetCursorPos({ 16, 0 });

					if (custom::subtab("Main ##subtab", subtab == 0)) subtab = 0; ImGui::SameLine(0, 20);
					if (custom::subtab("Two ##subtab", subtab == 1)) subtab = 1; ImGui::SameLine(0, 20);
					if (custom::subtab("Three ##subtab", subtab == 2)) subtab = 2;
				}
				ImGui::EndChild();

				ImGui::BeginChild("main_child", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 55 }, 0, ImGuiWindowFlags_NoBackground);
				{
					ImGui::BeginGroup();
					{
						custom::begin_child("Aimbot", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox("Tracking##3", &isTracking);
							ImGui::Combo(u8"AimButton", &SelectedKey, KeyNames, IM_ARRAYSIZE(KeyNames));
							ImGui::Checkbox("Trigger bot##3", &isTriggerBot);
							ImGui::Checkbox(u8"Flick bot", &isFlickBot);
							ImGui::SameLine(); Help(u8"Auto flick");
							ImGui::Checkbox(u8"Instant flick", &isInstantFLick);
							ImGui::SameLine(); Help(u8"Set speed to 22.5*sensitivity Ashe scoped 56%,widow 40% scoped");
							ImGui::Checkbox(u8"Fake Silent", &Silent);
							ImGui::Checkbox("Rage", &RAGE);
							ImGui::Checkbox("Hanzo Assistant", &ishanzonassist);
							if (isFlickBot) {
								isTracking = false;
								isTriggerBot = true;
								isCorrection = false;
							}
							if (isTracking) {
								isFlickBot = false;
								isTriggerBot = false;
								isCorrection = false;
							}
							if (isTriggerBot) {
								isCorrection = false;
							}
							if (isCorrection) {
								isFlickBot = false;
								isTriggerBot = false;
								isTracking = false;
							}
							if (isInstantFLick) {
								isFlickBot = false;
								isTriggerBot = false;
								isTracking = false;
								isCorrection = false;
							}
							if (Silent) {
								isFlickBot = false;
								isTriggerBot = false;
								isTracking = false;
								isCorrection = false;
								isInstantFLick = true;
							}
						}
						custom::end_child();
					}
					ImGui::EndGroup();
					ImGui::SameLine(0, 15);
					ImGui::BeginGroup();
					{
						custom::begin_child("Settings", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"Randomizer", &isRandomizer);
							ImGui::SliderInt(u8"Speed", &MSpeed, 1, 6);
							ImGui::SliderInt(u8"Smooth", &Smoothness, 1, 10);
							//ImGui::Spacing();
							ImGui::SliderInt(u8"Instant flick/fake silent speed", &InstantFlickSpeed, 1, 675);
							//ImGui::Spacing();
							ImGui::Checkbox(u8"Aim position", &isBoneid);
							if (isBoneid) {
								if (Bone == 1) {
									BoneName = u8"Head";
								}
								else if (Bone == 2) {
									BoneName = u8"Neck";
								}
								else {
									BoneName = u8"Chest";
								}
								ImGui::Spacing();
								ImGui::SliderInt(BoneName, &Bone, 1, 3);
							}
							custom::end_child();

						}
						ImGui::EndGroup();
						ImGui::Spacing();
					}
					ImGui::EndChild();
				} break;
			case 1: {
				ImGui::BeginChild("main_child", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 55 }, 0, ImGuiWindowFlags_NoBackground);
				{
					ImGui::BeginGroup();
					{
						custom::begin_child("Visuals", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"Draw Crosshair", &isCrossHairShow);
							if (isCrossHairShow) {
								ImGui::SliderInt(u8"Size", &CrossHairSize, 5, 150);
								ImGui::SliderInt(u8"Thick", &CrossHairThick, 1, 10);
							}
							ImGui::Checkbox(u8"Switch Team", &isChangeTeam);
							ImGui::Checkbox(u8"ESP LINE", &isEspLines);
							if (isEspLines) {
								if (LineType == 1) {
									LineTypeName = u8"Default";
								}
								else if (LineType == 2) {
									LineTypeName = u8"feet-head";
								}
								else if (LineType == 3) {
									LineTypeName = u8"crosshair-head";
								}
								else if (LineType == 4) {
									LineTypeName = u8"top-head";
								}
								else if (LineType == 5) {
									LineTypeName = u8"feet-feet";
								}
								else if (LineType == 6) {
									LineTypeName = u8"Crosshair-feet";
								}
								ImGui::SliderInt(LineTypeName, &LineType, 1, 6);
							}
							ImGui::Checkbox(u8"Box", &isEspBox);
							if (isEspBox) {
								if (BoxType == 1) {
									BoxTypeName = u8"Normal";
								}
								else {
									BoxTypeName = u8"Corner";
								}
								ImGui::SliderInt(BoxTypeName, &BoxType, 1, 2);
							}
						}
						custom::end_child();

						custom::begin_child("Colour", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"RainbowColour", &ShineColour);
							if (ShineColour) colourorno = 1;
							else colourorno = 0;
							ImGui::SliderInt(u8"R", &RR, 0, 255);
							ImGui::SliderInt(u8"G", &GG, 0, 255);
							ImGui::SliderInt(u8"B", &BB, 0, 255);
						}
						custom::end_child();
					}
					ImGui::EndGroup();
					ImGui::SameLine(0, 15);
					ImGui::BeginGroup();
					{
						custom::begin_child("ESP", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"Box", &isEspBox);
							if (isEspBox) {
								if (BoxType == 1) {
									BoxTypeName = u8"Normal";
								}
								else {
									BoxTypeName = u8"Corner";
								}
								ImGui::Spacing();
								ImGui::SliderInt(BoxTypeName, &BoxType, 1, 2);
							}
						}
						custom::end_child();
					}
					ImGui::EndGroup();
					ImGui::Spacing();
				}
				ImGui::EndChild();
			} break;

			case 2: {
				ImGui::BeginChild("main_child", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 55 }, 0, ImGuiWindowFlags_NoBackground);
				{
					ImGui::BeginGroup();
					{
						custom::begin_child("Fixes", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"Always Update", &isKeepUpdated);
							ImGui::SameLine(); Help(u8"Will increase cpu usage a little");
							if (ImGui::Button(u8"Manual update")) {
								Entity = FindPatternsExRegs(Offsets::AOB, Offsets::MASK, Offsets::EntitySize);
								ImGui::SameLine(); Help("When there is a new player join or a new match started,click this.");
								std::fill_n(distant, 100, 100000);
								std::fill_n(distantx, 100, 100000);
								std::fill_n(distanty, 100, 100000);
							}
						}
					}
					custom::end_child();
				}
				ImGui::EndGroup();
				ImGui::Spacing();
			}
				  ImGui::EndChild();
			} break;

			case 3: {
				ImGui::BeginChild("main_child", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 55 }, 0, ImGuiWindowFlags_NoBackground);
				{
					ImGui::BeginGroup();
					{
						custom::begin_child("Misc", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							ImGui::Checkbox(u8"Distantce", &isShowDIs);
							ImGui::Checkbox(u8"Prediction", &isPrediction);
							ImGui::Checkbox(u8"Prediction V2", &gravityPre);
							if (gravityPre) {
								isPrediction = true;
							}
							ImGui::Checkbox(u8"(hanzo)release button to fire", &hanzoleft);
							if (hanzoleft) {
								isFlickBot = true;
								isTriggerBot = true;
								isTracking = false;
								isCorrection = false;
								isInstantFLick = false;
								Silent = false;
							}
							ImGui::Checkbox(u8"No gravity prediction", &isLiner);
							ImGui::Checkbox(u8"Hanzo E reflection", &enableHanzoE);
							if (enableHanzoE) {
								isPrediction = true;
								gravityPre = true;
							}
							ImGui::Checkbox(u8"Genji aim auto switch", &isGenjiauto);
							if (isGenjiauto) {
								isPrediction = true;
							}
							ImGui::SliderInt(u8"Genji switch distance", &genjid, 1, 40);
							ImGui::SliderInt(u8"Genji switch smooth", &genjismooth, 1, 10);
							ImGui::Checkbox(u8"Show prediction point", &isShowPostoPre);
							ImGui::SliderInt(u8"Bullet speed", &travelspeed, 1, 200);
							ImGui::Checkbox(u8"Release Y", &isReleasey);
							ImGui::Checkbox(u8"Fire Right", &isRightflick);
							ImGui::SameLine(); Help(u8"For genji and sojourn");
							//ImGui::Checkbox(u8"ShowIQ", &isShowIQ);

						}
					}
					custom::end_child();
					ImGui::EndGroup();
					ImGui::SameLine(0, 15);
					ImGui::BeginGroup();
					{
						custom::begin_child("ESP", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							//ImGui::Checkbox(u8"IQ BOOST", &isIQBOOST);
							ImGui::Checkbox(u8"Fov circle", &isFov);
							ImGui::Checkbox(u8"Autoscale FOV", &isAutoscaleFOV);
							ImGui::SliderInt(u8"Minus fov", &FovCircle1, 50, 500);
							ImGui::SliderInt(u8"Real fov", &FovCircle, 50, 500);
							ImGui::Checkbox(u8"Auto scale trigger range", &isAutoshootrange);
							ImGui::SliderFloat(u8"Coefficient", &sHootingcoefficient, 0, 1);
							ImGui::SliderInt(u8"Minus range", &Dec1, 10, 100);
							ImGui::SliderInt(u8"Real range", &Dec, 10, 100);
							ImGui::Checkbox(u8"Auto shoot", &isAutoShoot);
							ImGui::SliderInt(u8"Interval", &shoottime, 10, 1500);
						}
						custom::end_child();

					}
					ImGui::EndGroup();
					ImGui::Spacing();

					ImGui::EndChild();
				} break;

			case 4: {
				ImGui::BeginChild("main_child", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 55 }, 0, ImGuiWindowFlags_NoBackground);
				{
					ImGui::BeginGroup();
					{
						custom::begin_child("Config", { (ImGui::GetWindowWidth() - 30) / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 300 });
						{
							if (ImGui::Button(u8"Save1")) {
								_stprintf(buf, _T("%d"), FovCircle);
								WritePrivateProfileString(_T("Section1"), _T("Fov"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Dec);
								WritePrivateProfileString(_T("Section1"), _T("ShootingRange"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), MSpeed);
								WritePrivateProfileString(_T("Section1"), _T("AimSpeed"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Smoothness);
								WritePrivateProfileString(_T("Section1"), _T("Smooth"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Bone);
								WritePrivateProfileString(_T("Section1"), _T("Bone"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), InstantFlickSpeed);
								WritePrivateProfileString(_T("Section1"), _T("SilentSpeed"), buf, _T(".\\config.ini"));
								shootrangeint = int(sHootingcoefficient * 1000);
								_stprintf(buf, _T("%d"), shootrangeint);
								WritePrivateProfileString(_T("Section1"), _T("Trigger Coefficient"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), shoottime);
								WritePrivateProfileString(_T("Section1"), _T("Shooting time"), buf, _T(".\\config.ini"));
							}
							if (ImGui::Button(u8"Load1")) {
								Dec = GetPrivateProfileInt(_T("Section1"), _T("ShootingRange"), 15, _T(".\\config.ini"));
								FovCircle = GetPrivateProfileInt(_T("Section1"), _T("Fov"), 150, _T(".\\config.ini"));
								MSpeed = GetPrivateProfileInt(_T("Section1"), _T("AimSpeed"), 1, _T(".\\config.ini"));
								Smoothness = GetPrivateProfileInt(_T("Section1"), _T("Smooth"), 1, _T(".\\config.ini"));
								Bone = GetPrivateProfileInt(_T("Section1"), _T("Bone"), 2, _T(".\\config.ini"));
								InstantFlickSpeed = GetPrivateProfileInt(_T("Section1"), _T("SilentSpeed"), 50, _T(".\\config.ini"));
								shootrangeint = GetPrivateProfileInt(_T("Section1"), _T("Trigger Coefficient"), 200, _T(".\\config.ini"));
								shoottime = GetPrivateProfileInt(_T("Section1"), _T("Shooting time"), 1000, _T(".\\config.ini"));
								sHootingcoefficient = ((float)shootrangeint) / 1000;
								FovCircle1 = FovCircle;
							}
							ImGui::BulletText(u8"Config2");
							ImGui::Spacing();
							if (ImGui::Button(u8"Save2")) {
								_stprintf(buf, _T("%d"), FovCircle);
								WritePrivateProfileString(_T("Section2"), _T("Fov"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Dec);
								WritePrivateProfileString(_T("Section2"), _T("ShootingRange"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), MSpeed);
								WritePrivateProfileString(_T("Section2"), _T("AimSpeed"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Smoothness);
								WritePrivateProfileString(_T("Section2"), _T("Smooth"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Bone);
								WritePrivateProfileString(_T("Section2"), _T("Bone"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), InstantFlickSpeed);
								WritePrivateProfileString(_T("Section2"), _T("SilentSpeed"), buf, _T(".\\config.ini"));
								shootrangeint = int(sHootingcoefficient * 1000);
								_stprintf(buf, _T("%d"), shootrangeint);
								WritePrivateProfileString(_T("Section2"), _T("Trigger Coefficient"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), shoottime);
								WritePrivateProfileString(_T("Section2"), _T("Shooting time"), buf, _T(".\\config.ini"));
							}
							ImGui::Spacing();
							if (ImGui::Button(u8"Load2")) {
								Dec = GetPrivateProfileInt(_T("Section2"), _T("ShootingRange"), 15, _T(".\\config.ini"));
								FovCircle = GetPrivateProfileInt(_T("Section2"), _T("Fov"), 150, _T(".\\config.ini"));
								MSpeed = GetPrivateProfileInt(_T("Section2"), _T("AimSpeed"), 1, _T(".\\config.ini"));
								Smoothness = GetPrivateProfileInt(_T("Section2"), _T("Smooth"), 1, _T(".\\config.ini"));
								Bone = GetPrivateProfileInt(_T("Section2"), _T("Bone"), 2, _T(".\\config.ini"));
								InstantFlickSpeed = GetPrivateProfileInt(_T("Section2"), _T("SilentSpeed"), 50, _T(".\\config.ini"));
								shootrangeint = GetPrivateProfileInt(_T("Section2"), _T("Trigger Coefficient"), 200, _T(".\\config.ini"));
								shoottime = GetPrivateProfileInt(_T("Section2"), _T("Shooting time"), 1000, _T(".\\config.ini"));
								sHootingcoefficient = ((float)shootrangeint) / 1000;
								FovCircle1 = FovCircle;
							}
							ImGui::BulletText(u8"Config3");
							ImGui::Spacing();
							if (ImGui::Button(u8"Save3")) {
								_stprintf(buf, _T("%d"), FovCircle);
								WritePrivateProfileString(_T("Section3"), _T("Fov"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Dec);
								WritePrivateProfileString(_T("Section3"), _T("ShootingRange"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), MSpeed);
								WritePrivateProfileString(_T("Section3"), _T("AimSpeed"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Smoothness);
								WritePrivateProfileString(_T("Section3"), _T("Smooth"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Bone);
								WritePrivateProfileString(_T("Section3"), _T("Bone"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), InstantFlickSpeed);
								WritePrivateProfileString(_T("Section3"), _T("SilentSpeed"), buf, _T(".\\config.ini"));
								shootrangeint = int(sHootingcoefficient * 1000);
								_stprintf(buf, _T("%d"), shootrangeint);
								WritePrivateProfileString(_T("Section3"), _T("Trigger Coefficient"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), shoottime);
								WritePrivateProfileString(_T("Section3"), _T("Shooting time"), buf, _T(".\\config.ini"));
							}
							ImGui::Spacing();
							if (ImGui::Button(u8"Load3")) {
								Dec = GetPrivateProfileInt(_T("Section3"), _T("ShootingRange"), 15, _T(".\\config.ini"));
								FovCircle = GetPrivateProfileInt(_T("Section3"), _T("Fov"), 150, _T(".\\config.ini"));
								MSpeed = GetPrivateProfileInt(_T("Section3"), _T("AimSpeed"), 1, _T(".\\config.ini"));
								Smoothness = GetPrivateProfileInt(_T("Section3"), _T("Smooth"), 1, _T(".\\config.ini"));
								Bone = GetPrivateProfileInt(_T("Section3"), _T("Bone"), 2, _T(".\\config.ini"));
								InstantFlickSpeed = GetPrivateProfileInt(_T("Section3"), _T("SilentSpeed"), 50, _T(".\\config.ini"));
								shootrangeint = GetPrivateProfileInt(_T("Section3"), _T("Trigger Coefficient"), 200, _T(".\\config.ini"));
								shoottime = GetPrivateProfileInt(_T("Section3"), _T("Shooting time"), 1000, _T(".\\config.ini"));
								sHootingcoefficient = ((float)shootrangeint) / 1000;
								FovCircle1 = FovCircle;
							}
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::BulletText(u8"Config4");
							ImGui::Spacing();
							if (ImGui::Button(u8"Save4")) {
								_stprintf(buf, _T("%d"), FovCircle);
								WritePrivateProfileString(_T("Section4"), _T("Fov"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Dec);
								WritePrivateProfileString(_T("Section4"), _T("ShootingRange"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), MSpeed);
								WritePrivateProfileString(_T("Section4"), _T("AimSpeed"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Smoothness);
								WritePrivateProfileString(_T("Section4"), _T("Smooth"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), Bone);
								WritePrivateProfileString(_T("Section4"), _T("Bone"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), InstantFlickSpeed);
								WritePrivateProfileString(_T("Section4"), _T("SilentSpeed"), buf, _T(".\\config.ini"));
								shootrangeint = int(sHootingcoefficient * 1000);
								_stprintf(buf, _T("%d"), shootrangeint);
								WritePrivateProfileString(_T("Section4"), _T("Trigger Coefficient"), buf, _T(".\\config.ini"));
								_stprintf(buf, _T("%d"), shoottime);
								WritePrivateProfileString(_T("Section4"), _T("Shooting time"), buf, _T(".\\config.ini"));
							}
							ImGui::Spacing();
							if (ImGui::Button(u8"Load4")) {
								Dec = GetPrivateProfileInt(_T("Section4"), _T("ShootingRange"), 15, _T(".\\config.ini"));
								FovCircle = GetPrivateProfileInt(_T("Section4"), _T("Fov"), 150, _T(".\\config.ini"));
								MSpeed = GetPrivateProfileInt(_T("Section4"), _T("AimSpeed"), 1, _T(".\\config.ini"));
								Smoothness = GetPrivateProfileInt(_T("Section4"), _T("Smooth"), 1, _T(".\\config.ini"));
								Bone = GetPrivateProfileInt(_T("Section4"), _T("Bone"), 2, _T(".\\config.ini"));
								InstantFlickSpeed = GetPrivateProfileInt(_T("Section4"), _T("SilentSpeed"), 50, _T(".\\config.ini"));
								shootrangeint = GetPrivateProfileInt(_T("Section4"), _T("Trigger Coefficient"), 200, _T(".\\config.ini"));
								shoottime = GetPrivateProfileInt(_T("Section4"), _T("Shooting time"), 1000, _T(".\\config.ini"));
								sHootingcoefficient = ((float)shootrangeint) / 1000;
								FovCircle1 = FovCircle;
							}

						}
					}
					custom::end_child();
				}
				ImGui::EndGroup();
				ImGui::Spacing();
				ImGui::EndChild();
			} break;
			}
			}
		}
		ImGui::EndChild();

		ImGui::EndGroup();
		ImGui::PopStyleVar();
		ImGui::PopItemFlag();

		ImGui::SetCursorPos({ 0, 0 });

		ImGui::BeginChild("navbar", { 50 + 100 * navbar_width, window->Size.y }, 0, ImGuiWindowFlags_NoBackground);
		{
			ImGui::GetWindowDrawList()->AddRectFilled(p, p + ImGui::GetWindowSize(), ImGui::GetColorU32(ImGuiCol_ChildBg), ImGui::GetStyle().WindowRounding, ImDrawFlags_RoundCornersLeft);
			ImGui::GetWindowDrawList()->AddRectFilled({ p.x + ImGui::GetWindowWidth() - 1, p.y }, p + ImGui::GetWindowSize(), ImGui::GetColorU32(ImGuiCol_Border));

			ImGui::SetCursorPosY(87);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 16 });
			if (custom::tab("A", "Aimbot", tab == 0)) tab = 0;
			if (custom::tab("B", "Visuals", tab == 1)) tab = 1;
			if (custom::tab("C", "Fixes", tab == 2)) tab = 2;
			if (custom::tab("D", "Misc", tab == 3)) tab = 3;
			if (custom::tab("E", "Config", tab == 4)) tab = 4;
			ImGui::PopStyleVar();
		}
		ImGui::EndChild();

		ImGui::SetCursorPos({ 41.5f + 100 * navbar_width, 47 });
		if (custom::collapse_button(navbar_collapsed)) navbar_collapsed = !navbar_collapsed;
	}
	ImGui::End();
}




void HackRender() {
	Vector2 IQpos;
	if (isShowIQ) {
		IQpos.x = Process.WindowWidth - 100; IQpos.y = Process.WindowHeight / 2;
		DrawHealthBar(IQpos, -300, IQ, 300);
		DrawString(IQpos, Color(RR, GG, BB), u8"Today IQ");
		std::string Info1;
		Info1 += std::to_string(IQ);
		IQpos.y += 20;
		DrawString(IQpos, Color(RR, GG, BB), Info1.c_str());
	}
	Vector2 HLpos;
	HLpos.x = Process.WindowWidth - 100; HLpos.y = Process.WindowHeight / 2;
	std::string Info2;
	string hl;
	if (cap == 0) {
		hl = u8"AIMPOS:HIGH";
	}
	else if (cap == 1) {
		hl = u8"AIMPOS:LOW";
	}
	Info2 += hl;
	HLpos.y += 40;
	DrawString(HLpos, Color(RR, GG, BB), Info2.c_str());


	if (GetAsyncKeyState(VK_END) & 1) {
		CloseHandle(ProcessHandle);
		exit(0);
	}

	if (isCrossHairShow) {
		//DrawCrosshair(Vector2(Process.WindowWidth, Process.WindowHeight), CrossHairSize, Color(255, 0, 0), CrossHairThick);
		DrawCrosshair(Vector2(Process.WindowWidth, Process.WindowHeight), CrossHairSize, Color(RR, GG, BB), CrossHairThick);
	}

	if (isAimbot && isFov) {
		//DrawCircle(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 2), FovCircle, Color(255, 0, 0));
		DrawCircle(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 2), FovCircle, Color(RR, GG, BB));
	}

	Matrix ViewMatrix = Read<Matrix>(Read<uintptr_t>(ModuleBase + Offsets::ViewMatrix) + Offsets::ViewMatrix_Ptr);

	for (int i = 0; i < Entity.size(); i++) {
		if (ShowMenu) continue;
		if (GetAsyncKeyState(KeyCodes(0x0d))) {
			re = 1;
		}
		if (!GetAsyncKeyState(KeyCodes(0x0d)) && re == 1) {
			if (cap == 0) cap = 1;
			else if (cap == 1) cap = 0;
			re = 0;
		}
		if (enableHanzoE) {
			if (GetAsyncKeyState(0x45)) {
				reeee = 1;
			}
			if (!GetAsyncKeyState(0x45) && reeee == 1) {
				if (hanzouEpre == false) hanzouEpre = true;
				else if (hanzouEpre == true) hanzouEpre = false;
				reeee = 0;
			}
		}
		if (!enableHanzoE) {
			hanzouEpre = false;
		}


		Vector3 Origin = Read<Vector3>(Entity[i] - Offsets::Origin);
		Origin.y -= 0.5;//0.5
		//Origin.x -=1;

		Vector3 Head = Read<Vector3>(Entity[i] - Offsets::Head); Head.x -= 0.55; Head.y -= 0.4; Head.z -= 0.55;//Head.x -= 0.5; Head.y -= 0.4 0.5;//0.8 0.2
		/*if (ownhead == -1 && i != Entity.size() - 1) {
			headtofeet[i] = abs(Head.y - Origin.y);
		}
		else if (i == Entity.size() - 1&&ownhead==-1) {
			ownhead= min_element(headtofeet, headtofeet + 100) - headtofeet;
		}*/
		//Vector3 OwnHead = Read<Vector3>(Entity[ownhead] - Offsets::Head); OwnHead.x -= 0.5; OwnHead.y -= 0.4; OwnHead.z -= 0.5;



		bool isAive = Read<BYTE>(Entity[i] - Offsets::Alive) == Offsets::Alive_Ret;
		if (!isChangeTeam) {
			isTeam = Read<BYTE>(Entity[i] - Offsets::Team) != Offsets::OwnTeam;
		}
		else {
			isTeam = Read<BYTE>(Entity[i] - Offsets::Team) != Offsets::EnemyTeam;
		}
		if (isAive == false) {
			distant[i] = 100000;
			distantx[i] = 100000;
			distanty[i] = 100000;

			if (!isTeam && isAive == false) IQ -= 0.1;
			if (isTeam && isAive == false) IQ += 0.1;
			continue;
		}



		if (!isTeam) continue;

		Vector2 OriginPos = WorldToScreen(Origin, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
		Vector2 HeadPos = WorldToScreen(Head, ViewMatrix, Process.WindowWidth, Process.WindowHeight);


		thest[i] = GetTickCount();
		int timediff = thest[i] - lasst[i];
		if (timediff > 0) {
			velox[i] = (Head.x - xold[i]) * 1000 / timediff;
			velox[i] = round(velox[i] * 10) / 10;
			veloy[i] = (Head.y - yold[i]) * 1000 / timediff;
			veloy[i] = round(veloy[i] * 10) / 10;
			veloz[i] = (Head.z - zold[i]) * 1000 / timediff;
			veloz[i] = round(veloz[i] * 10) / 10;
			xold[i] = Head.x;
			yold[i] = Head.y;
			zold[i] = Head.z;
			std::string Infovx;
			//Infovx += std::to_string(velox[i]);
			lasst[i] = thest[i];
			//DrawString(OriginPos, Color(255, 255, 255), Infovx.c_str());
		}
		Vector3 cool;
		float M[4][4];
		for (int kkk = 0; kkk < 4; kkk++) {
			for (int zzz = 0; zzz < 4; zzz++) {
				M[kkk][zzz] = ViewMatrix.M[kkk][zzz];
			}
		}
		float	A = M[1][1] * M[2][2] - M[2][1] * M[1][2],
			B = M[2][1] * M[0][2] - M[0][1] * M[2][2],
			C = M[0][1] * M[1][2] - M[1][1] * M[0][2],
			Z = M[0][0] * A + M[1][0] * B + M[2][0] * C;

		if (abs(Z) < 0.0001) cool = Vector3(0, 0, 0);

		float	D = M[2][0] * M[1][2] - M[1][0] * M[2][2],
			E = M[0][0] * M[2][2] - M[2][0] * M[0][2],
			F = M[1][0] * M[0][2] - M[0][0] * M[1][2],
			G = M[1][0] * M[2][1] - M[2][0] * M[1][1],
			H = M[2][0] * M[0][1] - M[0][0] * M[2][1],
			K = M[0][0] * M[1][1] - M[1][0] * M[0][1];

		cool = Vector3(-(A * M[3][0] + D * M[3][1] + G * M[3][2]) / Z, -(B * M[3][0] + E * M[3][1] + H * M[3][2]) / Z, -(C * M[3][0] + F * M[3][1] + K * M[3][2]) / Z);
		Vector3 Ownhead;
		int sqrtdis = sqrt(((cool.x - Head.x) * (cool.x - Head.x)) + ((cool.z - Head.z) * (cool.z - Head.z)) + ((cool.y - Head.y) * (cool.y - Head.y)));
		int distancess = -sqrtdis + 16384;
		Ownhead.y = -(Head.y - cool.y) * distancess / sqrtdis + Head.y;
		Ownhead.x = -(Head.x - cool.x) * distancess / sqrtdis + Head.x;
		Ownhead.z = -(Head.z - cool.z) * distancess / sqrtdis + Head.z;

		if (isShowDIs) {
			std::string Infod;
			Infod += std::to_string(distancess);
			DrawString(OriginPos, Color(255, 255, 255), Infod.c_str());
		}


		//if (isdistance) {
			//Vector3 OwnHead = Read<Vector3>(Entity[ownhead] - Offsets::Head); OwnHead.x -= 0.5; OwnHead.y -= 0.4; OwnHead.z -= 0.5;
			//realDistance[i] = Vector3::Distance(OwnHead, Head);
			//std::string Info;
			//Info += std::to_string(realDistance[i]);
			//DrawString(OriginPos, Color(255, 255, 255), Info.c_str());
		//}

		//if (OutsideBorder(OriginPos, Vector2(Process.WindowWidth, Process.WindowHeight)) != 0) continue;
		int out = OutsideBorder(OriginPos, Vector2(Process.WindowWidth, Process.WindowHeight));

		float BoxHeight = abs(HeadPos.y - OriginPos.y);
		float BoxWidth = BoxHeight * 0.6f;
		Rect PlayerRect(HeadPos.x - (BoxWidth / 2), HeadPos.y, BoxWidth, BoxHeight);

		/*std::string Info;
		Info += std::to_string(BoxHeight);
		DrawString(OriginPos, Color(255, 255, 255), Info.c_str());
		*/


		if (isEspLines && out == 0) {
			if (LineType == 1) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 12), HeadPos, Color(RR, GG, BB), 2);
			}
			else if (LineType == 2) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight - 2), HeadPos, Color(RR, GG, BB), 2);
			}
			else if (LineType == 3) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 2), HeadPos, Color(RR, GG, BB), 2);
			}
			else if (LineType == 4) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 12), Vector2(OriginPos.x + (BoxWidth / 2), OriginPos.y), Color(RR, GG, BB), 2);
			}
			else if (LineType == 5) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight - 2), Vector2(OriginPos.x + (BoxWidth / 2), OriginPos.y), Color(RR, GG, BB), 2);
			}
			else if (LineType == 6) {
				DrawLine(Vector2(Process.WindowWidth / 2, Process.WindowHeight / 2), Vector2(OriginPos.x + (BoxWidth / 2), OriginPos.y), Color(RR, GG, BB), 2);
			}
		}
		if (colourorno == 1) {
			if (colourfreq == 0) {
				if (redpn == 0)RR--;
				else RR++;
				if (colourpn == 0) {
					GG -= 1; BB += 1;
				}
				else {
					GG += 1; BB -= 1;
				}
				colourfreq = 10;
			}
			colourfreq--;
			if (RR == 255) redpn = 0;
			if (RR == 0) redpn = 1;
			if (GG == 0) colourpn = 1;
			if (BB == 255) colourpn = 1;
			if (GG == 255) colourpn = 0;
			if (BB == 0) colourpn = 0;
		}
		if (isEspBox && out == 0) {
			if (BoxType == 1) {
				DrawBox(PlayerRect, Color(RR, GG, BB), 2);
			}
			else {
				DrawCornerBox(PlayerRect, Color(0, 0, 0), Color(RR, GG, BB), 2);
			}
		}


		/*uintptr_t EntityAdmin = Read<uintptr_t>(ModuleBase + 0x3A5F7E0);
		for (int z = 0; z < 65535; z++) {
			uintptr_t Base = Read<uintptr_t>(EntityAdmin + (z * 0x10));
			if (Base) {
				float Health = Read<float>(DecryptComponent(Base, 0x3a));
				cout << Health << endl;
				std::string healthInfo;
				healthInfo += std::to_string(Health);
				DrawString(OriginPos, Color(255, 255, 255), healthInfo.c_str());
			}
		}*/
		/*uint64_t cur_entity = Entity[i];
		health_compo_t health_compo{};
		health_compo  = Read<health_compo_t>(DecryptComponent(Entity[i], 0x3a));
		cout << health_compo.health<<endl;
		std::string healthInfo;
		healthInfo += std::to_string(health_compo.health_max + health_compo.armor_max + health_compo.barrier_max);
		DrawString(OriginPos, Color(255, 255, 255), healthInfo.c_str());
		*/

		if (isAimbot) {
			Vector2 AimTarget;

			Vector3 AimPos = Head; //AimPos.x -= 0.55; AimPos.y -= 0.4; AimPos.z -= 0.55;//��׼λ��

			if (isPrediction) {
				if (gravityPre) {
					Vector3 Predict;
					double G = 9.81f;
					double A = Ownhead.x;
					double B = Ownhead.y;
					double C = Ownhead.z;
					double M = AimPos.x;
					double N = AimPos.y;
					double O = AimPos.z;
					double P = velox[i];
					double Q = veloy[i];
					double R = veloz[i];
					double S = travelspeed;
					double H = M - A;
					double J = O - C;
					double K = N - B;
					double L = -.5f * G;
					double c4 = L * L;
					double c3 = -2 * Q * L;
					double c2 = (Q * Q) - (2 * K * L) - (S * S) + (P * P) + (R * R);
					double c1 = (2 * K * Q) + (2 * H * P) + (2 * J * R);
					double c0 = (K * K) + (H * H) + (J * J);

					std::complex<float> pOutRoots[4];
					const std::complex<float> pInCoeffs[5] = { c0, c1, c2, c3, c4 };
					SolveQuartic(pInCoeffs, pOutRoots);
					float fBestRoot = FLT_MAX;
					for (int i = 0; i < 4; i++) {
						if (pOutRoots[i].real() > 0.f && std::abs(pOutRoots[i].imag()) < 0.0001f && pOutRoots[i].real() < fBestRoot) {
							fBestRoot = pOutRoots[i].real();
						}
					}
					double tempaim;
					//AimPos.x = AimPos.x + (velox[i] * fBestRoot);
					//tempaim = AimPos.y;
					//AimPos.y = AimPos.y + (veloy[i] * fBestRoot);
					//AimPos.z = AimPos.z + (veloz[i] * fBestRoot);
					AimPos.x = Ownhead.x + (H + P * fBestRoot);
					if (!isLiner) {
						AimPos.y = Ownhead.y + (K + Q * fBestRoot - L * fBestRoot * fBestRoot);
					}
					else if (isLiner) {
						AimPos.y += veloy[i] * fBestRoot;
					}
					AimPos.z = Ownhead.z + (J + R * fBestRoot);
					std::string Info123;
				}
				else if (!gravityPre) {
					AimPos.x += velox[i] * distancess / travelspeed;
					AimPos.y += veloy[i] * distancess / travelspeed;
					if (isLiner) {
						AimPos.y += 0.5 * 9.81 * (distancess / travelspeed) * (distancess / travelspeed);
					}
					AimPos.z += veloz[i] * distancess / travelspeed;
				}
				if (hanzouEpre) {
					AimPos.y = Origin.y - abs(AimPos.y - Origin.y);
				}
				if (isShowPostoPre) {
					std::string Info123;
					Info123 += std::to_string(0);
					Vector2 prepos = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
					DrawString(prepos, Color(RR, GG, BB), Info123.c_str());
				}
			}



			if (cap == 1) {
				AimPos.y -= 0.3;
			}
			if (isBoneid) {
				if (Bone == 1) {
					AimPos.y -= 0.1;//0.2
					AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
				}
				else if (Bone == 2) {
					AimPos.y -= 0.5f;//0.5f
					AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
				}
				else {
					AimPos.y -= 0.8f;//0.8f
					AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
				}
			}
			else {
				AimPos.y -= 0.5f;
				AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
			}


			//if (isFlickBot && isTriggerBot) { Dec = 15; }
			//if (!isFlickBot && isTriggerBot) { Dec = 40; }
			//bool Zoomin = isInsideFov(AimTarget.x, AimTarget.y, Process.WindowWidth, Process.WindowHeight, Dec);//TRIGERBOT
			//bool isInside = isInsideFov(AimTarget.x, AimTarget.y, Process.WindowWidth, Process.WindowHeight, FovCircle);

			//if (RAGE) isInside = true;

			//if (isInside) {
			distantx[i] = abs(AimTarget.x - Process.WindowWidth / 2);
			distanty[i] = abs(AimTarget.y - Process.WindowHeight / 2);
			distant[i] = sqrt(distantx[i] * distantx[i] + distanty[i] * distanty[i]);
			if (out != 0) distant[i] = 100000;
			//}
			//if (!isInside) {
			//	distant[i] = 100000;
			//	continue;
			//}

			int m;
			m = min_element(distant, distant + 100) - distant;
			//if (ishanzonassist) {
			//	AimTarget.y -= float(realDistance[i])*45.0f/100.0f;
			//}
			if (distant[m] == 100000) continue;
			if (m != i && !isPrediction) {
				AimPos = Read<Vector3>(Entity[m] - Offsets::Head); AimPos.x -= 0.55; AimPos.y -= 0.4; AimPos.z -= 0.55;
				/*if (isPrediction) {
					AimPos.x += velox[m] * distancess/ travelspeed;
					AimPos.y += veloy[m] * distancess/ travelspeed;
					AimPos.z += veloz[m] * distancess/ travelspeed;
					std::string Info;
					Info += std::to_string(0);
					Vector2 prepos = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
					DrawString(prepos, Color(255, 255, 255), Info.c_str());

				}*/
				Head = AimPos;
				if (cap == 1) {
					AimPos.y -= 0.3;
				}
				if (isBoneid) {
					if (Bone == 1) {
						AimPos.y -= 0.1;//0.2
						AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
					}
					else if (Bone == 2) {
						AimPos.y -= 0.5f;//0.5f
						AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
					}
					else {
						AimPos.y -= 0.8f;//0.8f
						AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
					}
				}
				else {
					AimPos.y -= 0.5f;
					AimTarget = WorldToScreen(AimPos, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
				}

				Origin = Read<Vector3>(Entity[m] - Offsets::Origin);
				Origin.y -= 0.5;//0.5
				//Origin.x -=1;

				OriginPos = WorldToScreen(Origin, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
				HeadPos = WorldToScreen(Head, ViewMatrix, Process.WindowWidth, Process.WindowHeight);
			}

			if (!isPrediction || m == i && isPrediction) {
				float BoxHeightm = abs(HeadPos.y - OriginPos.y);

				if (isGenjiauto) {
					if (distancess >= genjid) {
						isTracking = true;
						isFlickBot = false;
						isTriggerBot = false;
						isRightflick = false;
					}
					else if (distancess < genjid) {
						isTracking = false;
						isFlickBot = true;
						isTriggerBot = true;
						isRightflick = true;
					}
				}

				if (isAutoscaleFOV && distant[m] != 100000) {
					FovCircle = BoxHeightm * 2;
					if (FovCircle > 500) FovCircle = 500;
					else if (FovCircle < FovCircle1) FovCircle = FovCircle1;
				}
				else FovCircle = FovCircle1;

				bool isInside = isInsideFov(AimTarget.x, AimTarget.y, Process.WindowWidth, Process.WindowHeight, FovCircle);
				if (!isInside) FovCircle = FovCircle1;

				float BoxWidthm = BoxHeightm * 0.6f;
				if (isAutoshootrange) {
					Dec = BoxWidthm * sHootingcoefficient;
					if (Dec > Dec1) {}
					else if (Dec < Dec1) Dec = Dec1;
				}


				if (isReleasey) AimTarget.y = Process.WindowHeight / 2;
				if (GetAsyncKeyState(KeyCodes(SelectedKey)) && isInside && !hanzoleft) {
					if (isTracking) {
						AimBot(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
						ifthefirst = 1;
						if (isGenjiauto) {
							mouse_click();
						}
					}
					if (isFlickBot && k == 0) {
						if (isGenjiauto) {
							tempsmooth = Smoothness;
							Smoothness = genjismooth;
						}
						FlickBot(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
						if (isReleasey && abs(AimTarget.x - (Process.WindowWidth / 2)) <= Dec) {
							if (!isRightflick) {
								mouse_click();
							}
							else if (isRightflick) {
								mouse_right_click();
							}
							k = 1;
						}
						if (isGenjiauto) {
							Smoothness = tempsmooth;
						}
						ifthefirst = 1;
					}
					if (isFlickBot && k == 1 && isAutoShoot) {
						int rectime = GetTickCount();
						if (lasttime == 0) lasttime = rectime;
						else {
							int mtime = rectime - lasttime;
							if (mtime >= shoottime) {
								lasttime = 0;
								k = 0;
								if (ifthefirst == 1) {
									std::fill_n(distant, 100, 100000);
									ifthefirst = 0;
								}
							}
						}
					}
					//if (isCorrection && k == 0) {
					//	Correct(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
					//	k = 1;
					//	ifthefirst = 1;
					//}
					if (isInstantFLick && k == 0) {
						instantflick(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), InstantFlickSpeed, Silent);
						k = 1;
						ifthefirst = 1;
					}
					if (isInstantFLick && k == 1 && isAutoShoot) {
						int rectime = GetTickCount();
						if (lasttime == 0) lasttime = rectime;
						else {
							int mtime = rectime - lasttime;
							if (mtime >= shoottime) {
								lasttime = 0;
								k = 0;
								if (ifthefirst == 1) {
									std::fill_n(distant, 100, 100000);
									ifthefirst = 0;
								}
							}
						}
					}
					bool Zoomin = isInsideFov(AimTarget.x, AimTarget.y, Process.WindowWidth, Process.WindowHeight, Dec);
					if (isTriggerBot && Zoomin == true && GetAsyncKeyState(KeyCodes(SelectedKey)) && k == 0) {
						if (!isRightflick) {
							mouse_click();
						}
						else if (isRightflick) {
							mouse_right_click();
						}
						if (isFlickBot)k = 1;
					}
				}
				else if (hanzoleft) {
					if (GetAsyncKeyState(KeyCodes(SelectedKey)) && hleftdec == 0) {
						mouse_left_down();
						hleftdec = 1;
					}
					if (!GetAsyncKeyState(KeyCodes(SelectedKey)) && hleftdec == 1) {
						FlickBot(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
					}
					bool Zoomin = isInsideFov(AimTarget.x, AimTarget.y, Process.WindowWidth, Process.WindowHeight, Dec);
					if (Zoomin && hleftdec == 1 && !GetAsyncKeyState(KeyCodes(SelectedKey))) {
						hleftdec = 0;
						mouse_click();
					}

				}


				/*
				if (GetAsyncKeyState(KeyCodes(SelectedKey))) {

					if (isTracking && m == i) {
						AimBot(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
						ifthefirst = 1;
					}
					if (isFlickBot && k == 0 && m == i) {
						FlickBot(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
						ifthefirst = 1;
					}
					if (isCorrection && k == 0 && m == i) {
						Correct(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), AimSpeed, Smoothness);
						k = 1;
						ifthefirst = 1;
					}
					if (isInstantFLick && k == 0 && m == i) {
						instantflick(Process.WindowWidth, Process.WindowHeight, (float)round(AimTarget.x), (float)round(AimTarget.y), InstantFlickSpeed,Silent);
						k = 1;
						ifthefirst = 1;
					}
				}
				*/
				if (!GetAsyncKeyState(KeyCodes(SelectedKey))) {
					k = 0;
					if (ifthefirst == 1) {
						std::fill_n(distant, 100, 100000);
						ifthefirst = 0;
					}
				}
			}
		}
	}
}