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