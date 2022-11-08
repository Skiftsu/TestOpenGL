#pragma once
#include <string>
#include "Core/GL.h"
#include <glm.hpp>

enum class ShaderType
{
	VertexShader,
	FragmentShader
};

class BaseShader
{
	GLuint ShaderProgramId;
	bool LoadShader(const std::string FilePath, const ShaderType shaderType, GLuint& ShaderID);

protected:
	void UniformMatrix(std::string Name, glm::mat4 Matrix);
	void UniformVec3(std::string Name, glm::vec3 Vector);

public:
	BaseShader(std::string VertexFile, std::string FragmentFile);
	BaseShader() = delete;
	virtual ~BaseShader();

	GLuint GetShaderProgramId() { return ShaderProgramId; };

	virtual void Use();
};
