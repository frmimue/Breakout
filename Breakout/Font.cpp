#include "Font.h"

#include <lodepng.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Glyph::Glyph(std::map<std::string, int> character)
{
	xPos = (float)character.at("x");
	yPos = (float)character.at("y");
	width = (float)character.at("width");
	height = (float)character.at("height");
	xOffset = (float)character.at("xoffset");
	yOffset = (float)character.at("yoffset");
	xAdvance = (float)character.at("xadvance");
}

Glyph::~Glyph()
{
}

Font::Font(glm::vec2 resolution) : resolution(resolution)
{
	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//-----------------------------------------------------------

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 5 * 4, NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

Font::~Font()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Font::loadFNT(std::string filePath)
{
	std::ifstream file;
	file.open(filePath + ".fnt");

	std::string line;

	while (std::getline(file, line)) {
		if (line.find("info ") == 0) {
			std::stringstream line(line.substr(4));
			std::string keyValue;
			std::map<std::string, int> character;
			while (line >> keyValue) {
				int seperator = keyValue.find('=');
				std::string key = keyValue.substr(0, seperator);
				int value;
				std::stringstream(keyValue.substr(seperator + 1)) >> value;
				character.insert(std::pair<std::string, int>(key, value));
			}
			size = static_cast<float>(character.at("size"));
		}
		if (line.find("common ") == 0) {
			std::stringstream line(line.substr(4));
			std::string keyValue;
			std::map<std::string, int> character;
			while (line >> keyValue) {
				int seperator = keyValue.find('=');
				std::string key = keyValue.substr(0, seperator);
				int value;
				std::stringstream(keyValue.substr(seperator + 1)) >> value;
				character.insert(std::pair<std::string, int>(key, value));
			}
			base = static_cast<float>(character.at("base"));
			xSize = static_cast<float>(character.at("scaleW"));
			ySize = static_cast<float>(character.at("scaleH"));
		}
		if (line.find("char ") == 0) {
			std::cout << line << std::endl;
			std::stringstream line(line.substr(4));
			std::string keyValue;
			std::map<std::string, int> character;
			while (line >> keyValue) {
				int seperator = keyValue.find('=');
				std::string key = keyValue.substr(0, seperator);
				int value;
				std::stringstream(keyValue.substr(seperator + 1)) >> value;
				character.insert(std::pair<std::string, int>(key, value));
			}
			charMap.insert(std::pair<int, Glyph>(character.at("id"), Glyph(character)));
		}
	}



	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

										   // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	unsigned width, height;
	std::vector<unsigned char> image;
	lodepng::decode(image, width, height, filePath + ".png");


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Font::render(std::string text, float x, float y, float scale, float r, float g, float b)
{
	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	scale /= size;

	// Draw our first triangle
	glm::mat4 projection = glm::ortho(0.0f, resolution.x, 0.0f, resolution.y);

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(shaderProgram, "smoothing"), 0.25f / (4.0f * scale));
	glUniform3f(glGetUniformLocation(shaderProgram, "tColor"), r, g, b);

	for (auto c : text) {

		Glyph &g = charMap.at((int)c);

		glBindVertexArray(VAO);

		float width = g.width * scale;
		float height = g.height * scale;

		float xPos = x + (g.xOffset) * scale;
		float yPos = y - ((g.height - base) + g.yOffset) * scale;

		GLfloat vertices[] = {
			// Positions							// Colors           // Texture Coords
			xPos + width, yPos + height, 0.0f,		  (g.xPos + g.width) / xSize,	g.yPos / ySize, // Top Right
			xPos + width, yPos, 0.0f,				  (g.xPos + g.width) / xSize,	(g.yPos + g.height) / ySize, // Bottom Right
			xPos, yPos, 0.0f,						  g.xPos / xSize,				(g.yPos + g.height) / ySize, // Bottom Left
			xPos,  yPos + height, 0.0f,				  g.xPos / xSize,				g.yPos / ySize  // Top Left 
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		x += g.xAdvance * scale;
	}
}
