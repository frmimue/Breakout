#include "Level.h"

#include <fstream>
#include <sstream>

Level::Level(glm::vec2 resolution) : resolution(resolution)
{
}

Level::~Level()
{
	for (auto block : blocks)
		delete block;
}

void Level::render()
{
	//sprite->render(glm::vec2(0.0f, 0.0f), glm::vec2(400.0f, 200.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//block.render();

	for (auto block : blocks)
	{
		block->render();
	}
}

void Level::load(std::string filePath)
{

	//sprite = new Sprite(resolution);
	//sprite->load("block.png");

	//block = Block(glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 100.0f), glm::vec3(1.0f, 0.0f, 1.0f), resolution);

	
	std::ifstream file;
	file.open(filePath);

	std::string line;

	std::getline(file, line);
	std::stringstream row(line);
	float sizeX, sizeY;
	row >> sizeX;
	row >> sizeY;

	sizeX = resolution.x / sizeX;
	sizeY = (resolution.y / 2.0f) / sizeY;

	float posX = 0.0f, posY = 0.0f;

	while (std::getline(file, line)) {
		std::stringstream row(line);
		std::string element;
		while (row >> element) {
			if (element == "1")
				blocks.push_back(new Block(glm::vec2(posX, posY), glm::vec2(sizeX, sizeY), glm::vec3(0.0f, 1.0f, 0.0f), resolution));
			posX += sizeX;
		}
		posY += sizeY;
		posX = 0.0f;
	}
	
}
