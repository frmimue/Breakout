#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Font.h"
#include "Sprite.h"

class Breakout
{
private:
	GLFWwindow* window = nullptr;
	glm::vec2 resolution;
	Font* font;
	Sprite* sprite;
public:
	Breakout(glm::vec2 resolution);
	~Breakout();
	void run();
private:
	void createWindowContext();
	void setCallbacks();
};

