#include "Paddle.h"

#include "Sprite.h"

Paddle::Paddle(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution) : position(position), size(size), color(color), resolution(resolution)
{
	sprite = new Sprite(resolution);
	sprite->load("block.png");
}

Paddle::~Paddle()
{
	delete sprite;
}

void Paddle::render()
{
	sprite->render(position, size, color);
}

void Paddle::update()
{
	position.x = glm::max(position.x, 0.0f);
	position.x = glm::min(position.x, resolution.x - size.x);

	position += speed * 0.4f;
}

void Paddle::move(glm::vec2 move)
{
	speed += move;
}

glm::vec4 Paddle::AABB()
{
	return glm::vec4(position.x, position.y, position.x + size.x, position.y + size.y);
}
