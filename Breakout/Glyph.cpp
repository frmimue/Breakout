#include "Glyph.h"

Glyph::Glyph(std::map<std::string, int> character)
{
	xPos = (float)character.at("x");
	yPos = (float)character.at("y");
	width = (float)character.at("width");
	height = (float)character.at("height");
	xOffset = (float)character.at("xoffset");
	yOffset = (float)character.at("yoffset");
	xAdvance = (float)character.at("xadvance");
}

Glyph::~Glyph()
{
}
