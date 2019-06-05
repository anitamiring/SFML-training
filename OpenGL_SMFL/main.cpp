#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>

unsigned int CreateShaderProgram(const GLchar* vertexShaderText, const GLchar* fragmentShaderText);
std::string LoadFileContent(const std::string filePath);

int main(int argc, char* argv[])
{
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	window.setActive(true);

	glewExperimental = true;
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize: " << glewGetErrorString(result) << std::endl;
	}

	std::string vertexShaderText = LoadFileContent("shader.vert.glsl");
	std::string fragmentShaderText = LoadFileContent("shader.frag.glsl");

	unsigned int shaderProgram = CreateShaderProgram(vertexShaderText.c_str(), fragmentShaderText.c_str());
	glUseProgram(shaderProgram);

	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.display();
	}

	return 0;
}

unsigned int CreateShaderProgram(const GLchar* vertexShaderText, const GLchar* fragmentShaderText)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgram = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
std::string LoadFileContent(const std::string filePath)
{
	std::ifstream file(filePath);
	std::stringstream sstream;

	if (!file.is_open())
	{
		std::cout << "Can't find file" << filePath << std::endl;
	}
	sstream << file.rdbuf();
	return sstream.str();

}