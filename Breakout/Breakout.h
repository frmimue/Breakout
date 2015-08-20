#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Font.h"
#include "Sprite.h"
#include "Level.h"
#include "Ball.h"
#include "Paddle.h"

class Breakout
{
private:
	GLFWwindow* window = nullptr;
	glm::vec2 resolution;
	Font* font;
	Level level;
	Paddle *paddle;
	Ball* ball;
public:
	Breakout(glm::vec2 resolution);
	~Breakout();
	void run();
private:
	void createWindowContext();
	void setCallbacks();
	void collisionCheck();
	bool collisionAABB(glm::vec4 a, glm::vec4 b);
};

