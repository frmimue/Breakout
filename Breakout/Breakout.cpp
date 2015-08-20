#include "Breakout.h"

#include <iostream>

Breakout::Breakout(glm::vec2 resolution) : resolution(resolution), level(resolution)
{
	glfwInit();

	createWindowContext();

	setCallbacks();

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, static_cast<int>(resolution.x), static_cast<int>(resolution.y));

	glfwSwapInterval(0);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	font = new Font(resolution);
	font->loadFNT("comic_sans");

	level.load("level.txt");

	ball = new Ball(glm::vec2(resolution.x / 2.0f, resolution.y - 75.0f), glm::vec2(25.0f, 25.0f), glm::vec3(1.0f, 1.0f, 1.0f), resolution);

	paddle = new Paddle(glm::vec2(resolution.x / 2.0f - 75.0f/2.0f, resolution.y - 50.0f), glm::vec2(100.0f, 25.0f), glm::vec3(0.0f, 1.0f, 1.0f), resolution);
}


Breakout::~Breakout()
{
	glfwTerminate();
	delete font;
	delete ball;
	delete paddle;
}

void Breakout::run()
{
	while (!glfwWindowShouldClose(window))
	{
		paddle->update();
		ball->update();

		collisionCheck();

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		level.render();

		paddle->render();

		ball->render();

		glfwSwapBuffers(window);
	}
}

void Breakout::createWindowContext()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(static_cast<int>(resolution.x), static_cast<int>(resolution.y), "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

void Breakout::setCallbacks() {

	glfwSetWindowUserPointer(window, this);

	GLFWkeyfun key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		Breakout* _this = static_cast<Breakout*>(glfwGetWindowUserPointer(window));

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			_this->ball->start(glm::vec2(1.0f, -1.0f));
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			_this->paddle->move(glm::vec2(-1.0f, 0.0f));
		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
			_this->paddle->move(glm::vec2(1.0f, 0.0f));
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			_this->paddle->move(glm::vec2(1.0f, 0.0f));
		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
			_this->paddle->move(glm::vec2(-1.0f, 0.0f));
	};

	glfwSetKeyCallback(window, key_callback);
}

void Breakout::collisionCheck()
{
	if (collisionAABB(paddle->AABB(), ball->AABB()))
		ball->collide();

	for (auto it = level.blocks.begin(); it != level.blocks.end(); it++) {
		if (collisionAABB((*it)->AABB(), ball->AABB())) {
			it = level.blocks.erase(it);
			ball->collide();
			if (it == level.blocks.end())
				break;
		}
	}
	if (level.blocks.size() == 0)
		std::cout << "WON!!!" << std::endl;
}

bool Breakout::collisionAABB(glm::vec4 a, glm::vec4 b)
{
	bool collisionX = a.z >= b.x &&
       b.z >= a.x;
	bool collisionY = a.w >= b.y &&
		b.w >= a.y;
	return collisionX && collisionY;
}
