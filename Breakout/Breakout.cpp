#include "Breakout.h"


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

	sprite[0] = new Sprite(resolution);
	sprite[0]->load("block.png");

	sprite[1] = new Sprite(resolution);
	sprite[1]->load("block.png");

	sprite[2] = new Sprite(resolution);
	sprite[2]->load("block.png");

	sprite[3] = new Sprite(resolution);
	sprite[3]->load("block.png");

	level.load("level.txt");
}


Breakout::~Breakout()
{
	glfwTerminate();
	delete font;
	delete sprite[0];
	delete sprite[1];
	delete sprite[2];
	delete sprite[3];
}

void Breakout::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//sprite[0]->render(glm::vec2(0, 0), glm::vec2(400, 200), glm::vec3(1.0f, 0.0f, 0.0f));
		//sprite[1]->render(glm::vec2(400, 0), glm::vec2(400, 200), glm::vec3(0.0f, 1.0f, 0.0f));
		//sprite[2]->render(glm::vec2(0, 200), glm::vec2(400, 200), glm::vec3(1.0f, 0.0f, 1.0f));
		//sprite[3]->render(glm::vec2(400, 200), glm::vec2(400, 200), glm::vec3(0.0f, 1.0f, 1.0f));

		level.render();

		font->render("Hello World!", 200, 200, 16.0f, 0.0f, 0.0f, 1.0f);

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

	auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	};

	glfwSetKeyCallback(window, key_callback);
}
