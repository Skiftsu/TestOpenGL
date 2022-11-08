#include "Mesh.h"
#include "Core/Renderer/Shaders/MeshShader.h"
#include <iostream>

using namespace std;
using namespace glm;

Mesh::Mesh()
	: Mesh(new MeshShader("Resources/test.png"))
{
	
}

Mesh::Mesh(MeshShader* Shader)
	: pShader(Shader)
{
	
	glGenVertexArrays(1, &VAO);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::SetAttributes(const vector<GLsizei> Attributes)
{
	GLsizei AttributesLength = 0;
	for (auto i : Attributes)
		AttributesLength += i;

	GLsizei CurrentAttribute = 0;
	for (uint32_t i = 0; i < Attributes.size(); i++)
	{
		// 1.Location in shader, 2.Size (vec3 - 3), 3.Type (Float), 4.Normalize data
		glVertexAttribPointer(i, Attributes.at(i), GL_FLOAT, GL_FALSE, AttributesLength * sizeof(GLfloat), (GLvoid*)(CurrentAttribute * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
		CurrentAttribute += Attributes.at(i);
	}
}

void Mesh::DrawMesh(uint32_t DrawType)
{
	glBindVertexArray(VAO);

	pShader->Use(this);
	glDrawArrays(DrawType, 0, Polygons.size() * 3);

	glBindVertexArray(0);
}

void Mesh::SetPolygons3(const vector<SPolygon3> InPolygons)
{
	if (InPolygons.empty())
		return;
	Polygons = InPolygons;
	glBindVertexArray(VAO); // Start
	glDeleteBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, Polygons.size() * sizeof(SPolygon3), Polygons.data(), GL_STATIC_DRAW);
	SetAttributes({ 3, 2, 3 });

	glBindVertexArray(0); // End
}

void Mesh::SetPolygons4(const vector<SPolygon4> InPolygons)
{
	if (InPolygons.empty())
		return;
	vector<SPolygon3> PolygonsData;
	for (auto i : InPolygons)
	{
		array<SPolygon3, 2> QuadPolygons = i.ToPolygon3();
		PolygonsData.insert(PolygonsData.end(), QuadPolygons.begin(), QuadPolygons.end());
	}

	SetPolygons3(PolygonsData);
}