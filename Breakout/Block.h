#pragma once

#include "Sprite.h"

class Block
{
private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
public:
	Block(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution);
	~Block();
	virtual void render();
};