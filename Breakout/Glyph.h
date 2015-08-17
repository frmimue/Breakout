#pragma once

#include <map>
#include <string>

class Glyph
{
public:
	float id, xPos, yPos, width, height, xOffset, yOffset, xAdvance;
public:
	Glyph(std::map<std::string, int> character);
	~Glyph();
};