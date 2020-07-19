#pragma once
#include "stdafx.h"

float Cheat::GUI::MenuXFloat = 330.f;
float MenuOptionsTextSize = 45.f;
rgba titleRGB = { 255, 255, 255, 255 };
rgba optionRectRGB{ 255, 0, 0, 200 };
rgba optionRGB = { 255, 255, 255, 255 };
rgba scrollerRGB = { 0, 0, 255, 255 };
const char* InformationTextVar;

void drawRect(float x, float y, float w, float h, rgba rgba) {
	int ResolutionX;
	int ResolutionY;
	GRAPHICS::GET_SCREEN_RESOLUTION(&ResolutionX, &ResolutionY);
	x /= ResolutionX; w /= ResolutionX;
	y /= ResolutionY; h /= ResolutionY;

	GRAPHICS::DRAW_RECT(x, y, w, h, rgba.r, rgba.g, rgba.b, rgba.a, 0, 0);
}
void drawText(std::string text, float font_size, float x, float y, rgba rgba, bool centered = false) {
	int ResolutionX;
	int ResolutionY;
	GRAPHICS::GET_SCREEN_RESOLUTION(&ResolutionX, &ResolutionY);
	x /= ResolutionX; y /= ResolutionY;
	font_size /= 100.f;
	HUD::SET_TEXT_SCALE(font_size, font_size);
	HUD::_SET_TEXT_COLOR(rgba.r, rgba.g, rgba.b, rgba.a);
	HUD::SET_TEXT_CENTRE(centered);
	auto str = MISC::_CREATE_VAR_STRING(10, xorstr_("LITERAL_STRING"), text.c_str());
	HUD::_DRAW_TEXT(str, x, y);
}
void Cheat::GUI::Title(const char* title) {
	Cheat::Controls::optioncount = 0;
	drawRect(MenuXFloat, 42.f, 350.f, 40.f, { 0, 0, 255, 255 });
	drawText(title, 73.f, MenuXFloat, 22.f, titleRGB, true);
}
bool Cheat::GUI::Option(const char* option, const char* InformationText) {
	Cheat::Controls::optioncount++;

	bool thisOption = false;
	if (Cheat::Controls::currentoption == Cheat::Controls::optioncount) thisOption = true;

	if (Cheat::Controls::currentoption <= 14 && Cheat::Controls::optioncount <= 14) {
		drawText(option, MenuOptionsTextSize, MenuXFloat - 170.f, ((Cheat::Controls::optioncount * 30.f) + 36.5f), optionRGB);
		if (thisOption) { drawRect(MenuXFloat, ((Cheat::Controls::optioncount * 30.22f) + 46.6f), 350.f, 30.22f, scrollerRGB); }
		else { drawRect(MenuXFloat, ((Cheat::Controls::optioncount * 30.22f) + 46.6f), 350.f, 30.22f, { 0, 0, 0, 150 }); }
	}

	else if ((Cheat::Controls::optioncount > (Cheat::Controls::currentoption - 14)) && Cheat::Controls::optioncount <= Cheat::Controls::currentoption)
	{
		drawText(option, MenuOptionsTextSize, MenuXFloat - 170.f, (((Cheat::Controls::optioncount - (Cheat::Controls::currentoption - 14)) * 30.f) + 36.5f), optionRGB);
		if (thisOption) { drawRect(MenuXFloat, (((Cheat::Controls::optioncount - (Cheat::Controls::currentoption - 14)) * 30.22f) + 46.6f), 350.f, 30.22f, scrollerRGB); }
		else { drawRect(MenuXFloat, (((Cheat::Controls::optioncount - (Cheat::Controls::currentoption - 14)) * 30.22f) + 46.6f), 350.f, 30.22f, { 0, 0, 0, 150 }); }
	}

	if (thisOption) { InformationTextVar = InformationText; }

	if (Cheat::Controls::optionpress && Cheat::Controls::currentoption == Cheat::Controls::optioncount)
	{
		if (Cheat::Controls::optionpress)
		{
			return true;
		}
	}
	else return false;
}
bool Cheat::GUI::MenuOption(const char* option, const char* menu) {
	Option(option, "");

	if (Cheat::Controls::optionpress && Cheat::Controls::currentoption == Cheat::Controls::optioncount) {
		Cheat::Controls::optionpress = false;
		Cheat::Controls::changeMenu(menu);
		return true;
	}
	else return false;
}

bool Cheat::GUI::BoolOption(const char* option, bool* isEnabled, const char* InformationText) {
	Option(option, InformationText);

	if (Cheat::Controls::currentoption <= 14 && Cheat::Controls::optioncount <= 14) {
		drawText(*isEnabled ? xorstr_("~COLOR_GREEN~On") : xorstr_("~COLOR_RED~Off"), MenuOptionsTextSize, MenuXFloat + 135.f, ((Cheat::Controls::optioncount * 30.f) + 36.5f), optionRGB);
	}
	else if ((Cheat::Controls::optioncount > (Cheat::Controls::currentoption - 16)) && Cheat::Controls::optioncount <= Cheat::Controls::currentoption)
	{
		drawText(*isEnabled ? xorstr_("~COLOR_GREEN~On") : xorstr_("~COLOR_RED~Off"), MenuOptionsTextSize, MenuXFloat + 135.f, ((Cheat::Controls::optioncount * 30.f) + 36.5f), optionRGB);
	}

	if (Cheat::Controls::optionpress && Cheat::Controls::currentoption == Cheat::Controls::optioncount) {
		*isEnabled ^= 1;
		return true;
	}
	return false;
}

bool Cheat::GUI::IntOption(const char* option, int* var, int min, int max, int step, const char* InformationText) {
	Option(option, InformationText);

	if (Cheat::Controls::currentoption <= 14 && Cheat::Controls::optioncount <= 14) {
		drawText("<" + std::to_string(*var) + ">", MenuOptionsTextSize, MenuXFloat + 130.f, (Cheat::Controls::optioncount * 30.f) + 36.5f, optionRGB);
	}
	else if ((Cheat::Controls::optioncount > (Cheat::Controls::currentoption - 16)) && Cheat::Controls::optioncount <= Cheat::Controls::currentoption)
	{
		drawText("<" + std::to_string(*var) + ">", MenuOptionsTextSize, MenuXFloat + 130.f, (((Cheat::Controls::optioncount - (Cheat::Controls::currentoption - 14)) * 30.f) + 36.5f), optionRGB);
	}

	if (Cheat::Controls::currentoption == Cheat::Controls::optioncount) {
		if (Cheat::Controls::leftpress) {
			if (*var <= min) *var = max;
			else *var -= step;
			Cheat::Controls::leftpress = false;
			return true;
		}
		if (*var < min) *var = max;
		if (Cheat::Controls::rightpress) {
			if (*var >= max) *var = min;
			else *var += step;
			Cheat::Controls::rightpress = false;
			return true;
		}
		if (*var > max) *var = min;
	}

	if (Cheat::Controls::optionpress && Cheat::Controls::currentoption == Cheat::Controls::optioncount)
	{
		return true;
	}
	else return false;
}

bool Cheat::GUI::FloatOption(const char* option, float* var, float min, float max, float step, const char* InformationText) {
	Option(option, InformationText);

	char buf[100];
	_snprintf_s(buf, sizeof(buf), xorstr_("%.2f"), *var);

	if (Cheat::Controls::currentoption <= 14 && Cheat::Controls::optioncount <= 14) {
		drawText("<" + (std::string)buf + ">", MenuOptionsTextSize, MenuXFloat + 85.f, (Cheat::Controls::optioncount * 30.f) + 37.f, optionRGB);
	}
	else if ((Cheat::Controls::optioncount > (Cheat::Controls::currentoption - 16)) && Cheat::Controls::optioncount <= Cheat::Controls::currentoption)
	{
		drawText("<" + (std::string)buf + ">", MenuOptionsTextSize, MenuXFloat + 85.f, (((Cheat::Controls::optioncount - (Cheat::Controls::currentoption - 14)) * 30.f) + 37.f), optionRGB);
	}


	if (Cheat::Controls::currentoption == Cheat::Controls::optioncount) {
		if (Cheat::Controls::leftpress) {
			if (*var <= min) *var = max;
			else *var -= step;
			Cheat::Controls::leftpress = false;
			return true;
		}
		if (*var < min) *var = max;

		if (Cheat::Controls::rightpress) {
			if (*var >= max) *var = min;
			else *var += step;
			Cheat::Controls::rightpress = false;
			return true;
		}
		if (*var > max) *var = min;
	}

	if (Cheat::Controls::optionpress && Cheat::Controls::currentoption == Cheat::Controls::optioncount)
		return true;
	else return false;
}
void Cheat::GUI::End()
{
	if (Cheat::Controls::optioncount <= 14)
	{
		drawRect(MenuXFloat, 30.22f * Cheat::Controls::optioncount + 62.f, 350.f, 1.f, { 0, 0, 255, 255 });  //Menu bottom line
		drawRect(MenuXFloat, 30.22f * Cheat::Controls::optioncount + 77.5f, 350.f, 30.f, { 0, 0, 0, 255 });  //Menu bottom draw
		drawText(Cheat::CheatFunctions::ReturnCheatBuildAsString(), 40.f, MenuXFloat + 115.f, 30.22f * Cheat::Controls::optioncount + 67.f, { 255, 255, 255, 255 }, false); //Cheat build number draw
		drawText(std::to_string(Cheat::Controls::currentoption) + xorstr_(" / ") + std::to_string(Cheat::Controls::optioncount), 40.f, MenuXFloat - 170.f, 30.22f * Cheat::Controls::optioncount + 67.f, { 255, 255, 255, 255 }, false); //Option count draw at menu bottom
		if (InformationTextVar != "")
		{
			drawRect(MenuXFloat, 30.22f * Cheat::Controls::optioncount + 103.f, 350.f, 25.f, { 0, 0, 0, 255 });
			drawText(InformationTextVar, 40.f, MenuXFloat - 170.f, 30.22f * Cheat::Controls::optioncount + 90.f, { 255, 255, 255, 255 }, false);
		}
	}
	else
	{
		drawRect(MenuXFloat, 30.22f * 14 + 62.f, 350.f, 1.f, { 0, 0, 255, 255 });   //Menu bottom line
		drawRect(MenuXFloat, 30.22f * 14 + 77.5f, 350.f, 30.f, { 0, 0, 0, 255 });   //Menu bottom draw
		drawText(Cheat::CheatFunctions::ReturnCheatBuildAsString(), 40.f, MenuXFloat + 115.f, 30.22f * 14 + 67.f, { 255, 255, 255, 255 }, false); //Cheat build number draw
		drawText(std::to_string(Cheat::Controls::currentoption) + xorstr_(" / ") + std::to_string(Cheat::Controls::optioncount), 40.f, MenuXFloat - 170.f, 30.22f * 14 + 67.f, { 255, 255, 255, 255 }, false); //Option count draw at menu bottom
		if (InformationTextVar != "")
		{
			drawRect(MenuXFloat, 30.22f * 14 + 103.f, 350.f, 25.f, { 0, 0, 0, 255 });
			drawText(InformationTextVar, 40.f, MenuXFloat - 170.f, 30.22f * 14 + 90.f, { 255, 255, 255, 255 }, false);
		}
	}
}