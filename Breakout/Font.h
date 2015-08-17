#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <map>
#include <glm\glm.hpp>

#include "Glyph.h"

class Font
{
private:
	std::map<int, Glyph> charMap;
	GLuint texture;
	GLuint VBO, VAO, EBO;
	GLuint shaderProgram;
	float base;
	float xSize;
	float ySize;
	float size;
	glm::vec2 resolution;
public:
	Font(glm::vec2 resolution);
	~Font();
	void loadFNT(std::string filePath);
	void render(std::string text, float x, float y, float scale, float r, float g, float b);

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
		"float distance = texture(ourTexture, TexCoord).a;\n"
		"float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);\n"
		"color = vec4(ourColor.rgb, alpha);\n"
		"}\n\0";
};
