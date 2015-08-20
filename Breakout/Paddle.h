#pragma once

#pragma once

#include "Sprite.h"

class Paddle {
private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
	glm::vec2 speed = glm::vec2(0.0f, 0.0f);
	glm::vec2 resolution;
public:
	Paddle(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution);
	~Paddle();
	void render();
	void update();
	void move(glm::vec2 move);
	glm::vec4 AABB();
};