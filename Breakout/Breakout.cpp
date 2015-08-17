#include "Breakout.h"


Breakout::Breakout(glm::vec2 resolution) : resolution(resolution)	
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

	sprite = new Sprite(resolution);
	sprite->load("comic_sans.png");
}


Breakout::~Breakout()
{
	glfwTerminate();
	delete font;
	delete sprite;
}

void Breakout::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//font->render("Hello World!", 200, 200, 16.0f, 0.0f, 0.0f, 1.0f);

		sprite->render(glm::vec2(100, 100), 200, 200, glm::vec3(1.0f, 0.0f, 0.0f));

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
