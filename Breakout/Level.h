#pragma once

#include <string>
#include <vector>
#include <glm\glm.hpp>

#include "Block.h"

class Level
{
private:
	std::vector<Block*> blocks;
	glm::vec2 resolution;
public:
	Level(glm::vec2 resolution);
	~Level();
	void render();
	void load(std::string filePath);
};
