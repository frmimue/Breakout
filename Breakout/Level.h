#pragma once

#include <string>
#include <vector>
#include <glm\glm.hpp>

#include "Block.h"

class Level
{
private:
	glm::vec2 resolution;
public:
	std::vector<Block*> blocks;
	Level(glm::vec2 resolution);
	~Level();
	void render();
	void load(std::string filePath);
};
