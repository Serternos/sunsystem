#ifndef  _SHADER_
#define _SHADER_

#include <GL/glew.h>
#include <iostream>
#include <fstream>

std::string vertexFileName = "vertex.shader";
std::string fragmentFileName = "fragment.shader";

GLchar* readShaderFile(std::string fileName);

GLuint initShader()
{
	GLuint shaderProgram;

	GLchar* vShaderCode;
	GLchar* fShaderCode;

	GLuint vertex;
	GLuint fragment;
	GLchar infoLog[512];
	GLint success;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	vShaderCode = readShaderFile(vertexFileName);
	std::cout << vShaderCode << std::endl;
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
	std::ifstream shaderStream(fileName.c_str(), std::ifstream::ate);
	int len = shaderStream.tellg();
	GLchar* shaderSource = new GLchar[len + 1];
	shaderStream.clear();
	shaderStream.seekg(0, shaderStream.beg);
	for (int i = 0; i<len; i++) { shaderStream.get(shaderSource[i]); }
	shaderSource[len] = '\0';

	return shaderSource;
}

#endif // ! _SHADER_
