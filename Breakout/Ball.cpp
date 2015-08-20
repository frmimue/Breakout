#include "Ball.h"

#include "Sprite.h"

Ball::Ball(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution) : position(position), size(size), color(color), resolution(resolution)
{
	sprite = new Sprite(resolution);
	sprite->load("ball.png");
}

Ball::~Ball()
{
	delete sprite;
}

void Ball::render()
{
	sprite->render(position, size, color);
}

void Ball::collide() {
	speed.y *= -1.0f;
}

void Ball::update()
{
	if (position.x < 0 || position.x > resolution.x - size.x)
		speed.x *= -1.0f;
	if (position.y < 0 || position.y > resolution.y - size.y)
		speed.y *= -1.0f;

	position += speed * 0.2f;
}

void Ball::start(glm::vec2 start)
{
	speed = start;
}

glm::vec4 Ball::AABB()
{
	return glm::vec4(position.x, position.y, position.x + size.x, position.y + size.y);
}
