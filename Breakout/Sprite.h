#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <map>
#include <glm\glm.hpp>

class Sprite
{
private:
	GLuint texture;
	GLuint VBO, VAO, EBO;
	GLuint shaderProgram;
	glm::vec2 resolution;
public:
	Sprite(glm::vec2 resolution);
	~Sprite();
	void load(std::string filePath);
	void render(glm::vec2 position, float sizeX, float sizeY, glm::vec3 color);

private:
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec2 texCoord;\n"
		"uniform mat4 projection;\n"
		"uniform vec3 tColor;"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * vec4(position, 1.0);\n"
		"ourColor = tColor;\n"
		"TexCoord = texCoord;\n"
		"}\0";

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture;\n"
		"uniform float smoothing;\n"
		"void main()\n"
		"{\n"
		"color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);\n"
		"}\n\0";
};
