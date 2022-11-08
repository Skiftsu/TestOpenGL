#include "BaseShader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.hpp>

#include "Core/Renderer/Renderer.h"

using namespace std;
using namespace glm;

bool BaseShader::LoadShader(const string FilePath, const ShaderType shaderType, GLuint& ShaderID)
{
	ifstream File(FilePath.c_str());
	if (!File.is_open())
	{
		cerr << "Failed to open file: " << FilePath << endl;
		return "";
	}
	string ShaderCodeArray({istreambuf_iterator<char>(File), istreambuf_iterator<char>{}});
	const GLchar* ShaderCode = ShaderCodeArray.c_str();

	switch (shaderType)
	{
		case ShaderType::VertexShader:
			ShaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::FragmentShader:
			ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
	}
	
	glShaderSource(ShaderID, 1, &ShaderCode, nullptr);
	glCompileShader(ShaderID);

	GLint Success;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		GLchar InfoLog[512];
		glGetShaderInfoLog(ShaderID, 512, nullptr, InfoLog);
		cout << "ERROR::SHADER::COMPILATION_FAILED" << InfoLog << endl;
		glDeleteShader(ShaderID);
		return false;
	}
	return true;
}

BaseShader::BaseShader(string VertexFile, string FragmentFile)
{
	GLuint VertexShader, FragmentShader;
	if (!LoadShader(VertexFile, ShaderType::VertexShader, VertexShader))
		return;
	if (!LoadShader(FragmentFile, ShaderType::FragmentShader, FragmentShader))
	{
		glDeleteShader(VertexShader);
		return;
	}

// Shader Program
	ShaderProgramId = glCreateProgram();
	glAttachShader(ShaderProgramId, VertexShader);
	glAttachShader(ShaderProgramId, FragmentShader);
	glLinkProgram(ShaderProgramId);
// ==============

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	GLint Success;
	glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		GLchar InfoLog[512];
		glGetProgramInfoLog(ShaderProgramId, 512, nullptr, InfoLog);
		cerr << "SHADER::PROGRAM::Linking failed: " << InfoLog << endl;
		glDeleteProgram(ShaderProgramId);
		return;
	}
}

BaseShader::~BaseShader()
{
	glDeleteProgram(ShaderProgramId);
}

void BaseShader::Use()
{
	glUseProgram(ShaderProgramId);
}

void BaseShader::UniformMatrix(string Name, mat4 Matrix)
{
	GLuint TransformLoc = glGetUniformLocation(ShaderProgramId, Name.c_str());
	glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, value_ptr(Matrix));
}

void BaseShader::UniformVec3(std::string Name, glm::vec3 Vector)
{
	GLuint TransformLoc = glGetUniformLocation(ShaderProgramId, Name.c_str());
	glUniform3f(TransformLoc, Vector.x, Vector.y, Vector.z);
}
