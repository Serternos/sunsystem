#ifndef  _SHADER_
#define _SHADER_

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>

std::string vertexFileName = "res/vertex.shader";
std::string fragmentFileName = "res/fragment.shader";

GLchar* readShaderFile(std::string fileName);

GLuint initShader()
{

	std::cout << "loading shaders\n" << std::endl;
	GLuint shaderProgram;

	GLchar* vShaderCode;
	GLchar* fShaderCode;

	GLuint vertex;
	GLuint fragment;
	GLchar infoLog[512];
	GLint success;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	vShaderCode = readShaderFile(vertexFileName);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	fShaderCode = readShaderFile(fragmentFileName);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	free((void*)vShaderCode);
	free((void*)fShaderCode);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return shaderProgram;
}

GLchar* readShaderFile(std::string fileName) {
	std::ifstream inputStream(fileName.c_str(), std::ifstream::ate);
	int len = inputStream.tellg();
	inputStream.clear();
	inputStream.seekg(0, inputStream.beg);

	std::string* buf = new std::string(std::istreambuf_iterator<char>(inputStream), {});
	buf->push_back('\0');
	std::cout << (buf->c_str()) << std::endl << std::endl;
	return (GLchar*)(buf->c_str());
}

#endif // ! _SHADER_
