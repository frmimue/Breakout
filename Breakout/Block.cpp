#include "Block.h"

#include "Sprite.h"

Block::Block(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution) : position(position), size(size), color(color)
{
	sprite = new Sprite(resolution);
	sprite->load("block.png");
}

Block::~Block()
{
	delete sprite;
}

void Block::render()
{
	sprite->render(position, size, color);
}

glm::vec4 Block::AABB()
{
	return glm::vec4(position.x, position.y, position.x + size.x, position.y + size.y);
}

void Block::hit() {
	this->color = glm::vec3(1.0f, 0.0f, 0.0f);
}
