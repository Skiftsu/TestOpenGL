#pragma once
#include <string>
#include <vector>
#include "Core/CoreTypes.h"
#include "Core/GL.h"
#include <glm.hpp>

class MeshShader;

class Mesh
{
	friend MeshShader;

protected:
	GLuint VAO, VBO;

	glm::mat4 Transform = glm::mat4(1);

	std::vector<SPolygon3> Polygons;

	/* Float only*/
	void SetAttributes(const std::vector<GLsizei> Attributes);
		
	MeshShader* pShader;

public:
	Mesh();
	Mesh(MeshShader* Shader);
	virtual ~Mesh();

	void SetPolygons3(const std::vector<SPolygon3> Polygons);
	void SetPolygons4(const std::vector<SPolygon4> Polygons);

	virtual void DrawMesh(uint32_t DrawType = GL_TRIANGLES);
};
