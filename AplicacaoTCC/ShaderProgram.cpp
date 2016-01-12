#include "ShaderProgram.h"
#include "ErrorHandle.h"

#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
	// CRIA��O
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0)
	{
		fatalError("Vertex Shader n�o pode ser criado");
	}
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
	{
		fatalError("Fragment Shader n�o pode ser criado");
	}

	compileShader(vertexShaderFilePath, m_vertexShaderID);
	compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void ShaderProgram::compileShader(const std::string filePath, GLuint id)
{
	m_programID = glCreateProgram();

	// ABERTURA
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Falha ao abrir " + filePath);
	}

	// LEITURA
	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}

	shaderFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	// COMPILA��O
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(id);
		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader " + filePath + " n�o pode ser compilado.");
	}
}

void ShaderProgram::linkShaders()
{
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	glLinkProgram(m_programID);

	GLint success = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shaders n�o puderam ser linkados ao programa");
	}

	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void ShaderProgram::addAttribute(const std::string attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes, attributeName.c_str());
	m_numAttributes++;
}

void ShaderProgram::use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}