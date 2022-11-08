#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <array>
#include <string>


struct STransform
{
	glm::vec3 Location = glm::vec3(0);
	glm::vec3 Rotation = glm::vec3(0); // Yaw, Pitch, Roll;
};

struct SPosition
{
	int X, Y, Z;

	SPosition operator+(const SPosition Pos) const { return { X + Pos.X, Y + Pos.Y, Z + Pos.Z }; };
	SPosition operator-(const SPosition Pos) const { return { X - Pos.X, Y - Pos.Y, Z - Pos.Z }; };
	bool operator>(const SPosition Pos) const { return X > Pos.X && Y > Pos.Y && Z > Pos.Z; };
	bool operator<(const SPosition Pos) const { return X < Pos.X && Y < Pos.Y && Z < Pos.Z; };
	bool operator>=(const SPosition Pos) const { return X >= Pos.X && Y >= Pos.Y && Z >= Pos.Z; };
	bool operator==(const SPosition Pos) const { return X == Pos.X && Y == Pos.Y && Z == Pos.Z; };
	bool operator<=(const SPosition Pos) const { return X <= Pos.X && Y <= Pos.Y && Z <= Pos.Z; };

	const std::string ToString() const { return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + " Z: " + std::to_string(Z); };
};

constexpr uint32_t VertexDataSize = 9;
constexpr uint32_t Polygon3DataSize = VertexDataSize * 3;
constexpr uint32_t Polygon4DataSize = VertexDataSize * 4;

struct SVertex
{
	glm::vec3 Position = glm::vec3(0);
	glm::vec2 TexCoords = glm::vec2(0);
	glm::vec3 Normals = glm::vec3(0);

	const std::array<float, VertexDataSize> GetVertexData() const
	{
		return { Position.x, Position.y, Position.z, TexCoords.x, TexCoords.y };
	};
};

struct SPolygon3
{
	SVertex Vertex1, Vertex2, Vertex3;
};

struct SPosition2
{
	int X, Y;

	const SPosition2 operator/(const int Value) const { return { X / Value, Y / Value }; };
	SPosition2 operator-(const SPosition2 Pos) const { return { X - Pos.X, Y - Pos.Y }; };
	SPosition2 operator+(const SPosition2 Pos) const { return { X + Pos.X, Y + Pos.Y }; };
	SPosition2 operator*(const SPosition2 Pos) const { return { X * Pos.X, Y * Pos.Y }; };

	const std::string ToString() const { return "X: " + std::to_string(X) + " Y: " + std::to_string(Y); };
};

/* Poligon 4
 (Start)Top Left ----<---- Top Rgiht
				|         |
				|         |
				|         |
	 Bottom Left ---->---- Bottom Right
*/
struct SPolygon4
{
	SVertex Vertex1, Vertex2, Vertex3, Vertex4;

	const std::array<SPolygon3, 2> ToPolygon3() const
	{
		return { SPolygon3{ Vertex1, Vertex2, Vertex4 }, SPolygon3{ Vertex3, Vertex4, Vertex2 } };
	};

	SPolygon4 operator+(const SPosition Pos) 
	{ 
		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(Pos.X, Pos.Y, Pos.Z));

		Vertex1.Position = translate * glm::vec4(Vertex1.Position, 1.f);
		Vertex2.Position = translate * glm::vec4(Vertex2.Position, 1.f);
		Vertex3.Position = translate * glm::vec4(Vertex3.Position, 1.f);
		Vertex4.Position = translate * glm::vec4(Vertex4.Position, 1.f);

		return *this; 
	};
};