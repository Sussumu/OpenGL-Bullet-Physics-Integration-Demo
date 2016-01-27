#pragma once

#include "ErrorHandler.h"
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <string>

class ShaderProgram
{
public:

	ShaderProgram();
	~ShaderProgram();

	GLuint programID;

	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
	void linkShaders();
	void addAttribute(const std::string attributeName);

	void use();
	void unuse();

private:

	int m_numAttributes{ 0 };
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	void compileShader(const std::string filePath, GLuint id);
};

