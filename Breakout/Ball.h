#pragma once

#include "Sprite.h"

class Ball {
private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
	glm::vec2 speed = glm::vec2(0.0f, 0.0f);
	glm::vec2 resolution;
public:
	Ball(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 resolution);
	~Ball();
	void render();
	void update();
	void start(glm::vec2 start);
};